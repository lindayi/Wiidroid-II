// =====================================================================================
//
//       Filename:  MainWindow.cpp
//
//    Description:  主窗口的实现
//
//        Version:  1.0
//        Created:  2014年03月13日 19时16分23秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
//
// =====================================================================================

#include <QtGui>
#include <QtNetwork>
#include <QDebug>

#include "MainWindow.h"
#include "ProtocolXml.h"
#include "ProtocolType.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createMainWeiget();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createSystemTrayIcon();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isTrayExit) {
        event->accept();
        return;
    }

    int result = QMessageBox::question(this, tr("Wiidroid"),
        tr("<H3>您点击了关闭按钮。</H3>要最小化到托盘吗？"), QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        event->ignore();
        this->hide();
        showTrayInfo(tr("Wiidroid 最小化到这里了，点击图标显示主界面。"));
    } else {
        systemTrayIcon->hide();
        event->accept();
    }
}

void MainWindow::createMainWeiget()
{
    resize(400, 300);
    isServerStart = false;
    isTrayExit = false;
    setWindowIcon(QIcon(":/res/ico/main.ico"));
    setWindowTitle(tr("Wiidroid -- Alpha 1"));

    tcpServerSocket = new QTcpServer(this);
    connect(tcpServerSocket, SIGNAL(newConnection()), this, SLOT(newClientLink()));

    udpServerSocket = new QUdpSocket(this);

    broadcastServerSocket = new QUdpSocket(this);
    broadcastTimer = new QTimer(this);
    connect(broadcastTimer, SIGNAL(timeout()), this, SLOT(broadcastUdpServerInfo()));
}

void MainWindow::createActions()
{
    startAction = new QAction(tr("启动服务"), this);
    startAction->setIcon(QIcon(":/res/images/start.png"));
    startAction->setStatusTip(tr("启动 Wiidroid 的服务"));
    connect(startAction, SIGNAL(triggered()), this, SLOT(start()));

    stopAction = new QAction(tr("停止服务"), this);
    stopAction->setIcon(QIcon(":/res/images/stop.png"));
    stopAction->setStatusTip(tr("停止 Wiidroid 的服务"));
    stopAction->setEnabled(false);
    connect(stopAction, SIGNAL(triggered()), this, SLOT(stop()));

    exitAction = new QAction(tr("退出"), this);
    exitAction->setIcon(QIcon(":/res/images/exit.png"));
    exitAction->setStatusTip(tr("退出 Wiidroid"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    trayExitAction = new QAction(tr("退出"), this);
    trayExitAction->setIcon(QIcon(":/res/images/exit.png"));
    trayExitAction->setStatusTip(tr("退出 Wiidroid"));
    connect(trayExitAction, SIGNAL(triggered()), this, SLOT(trayExit()));

    settingAction = new QAction(tr("设置"), this);
    settingAction->setIcon(QIcon(":/res/images/setting.png"));
    settingAction->setStatusTip(tr("设置 Wiidroid"));
    connect(settingAction, SIGNAL(triggered()), this, SLOT(setting()));

    aboutAction = new QAction(tr("关于"), this);
    aboutAction->setIcon(QIcon(":/res/images/about.png"));
    aboutAction->setStatusTip(tr("关于 Wiidroid"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = this->menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(startAction);
    fileMenu->addAction(stopAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    setMenu = this->menuBar()->addMenu(tr("设置"));
    setMenu->addAction(settingAction);

    helpMenu = this->menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(aboutAction);

    trayMenu = new QMenu(this);
    trayMenu->addAction(settingAction);
    trayMenu->addAction(exitAction);
}

void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(tr("工具栏"));
    mainToolBar->addAction(startAction);
    mainToolBar->addAction(stopAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(settingAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(aboutAction);
    mainToolBar->setMovable(false);
}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel(tr("Wiidroid"));
    statusLabel->setAlignment(Qt::AlignHCenter);
    statusLabel->setMinimumSize(statusLabel->sizeHint());

    this->statusBar()->addWidget(statusLabel);
}

void MainWindow::initSocketLink()
{
    tcpServerSocket->listen(QHostAddress::Any, 8086);

    strServerIP = getHostIP();
    strServerPort = QString::number(tcpServerSocket->serverPort());
    udpSendMsg = ProtocolXml::CreateBroadcastInfoXml(strServerIP, strServerPort);

    udpServerSocket->bind(QHostAddress::LocalHost, 9527,
               QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    broadcastTimer->start(3000);
}

void MainWindow::abortSocketLink()
{
    broadcastTimer->stop();
    tcpServerSocket->close();
    udpServerSocket->close();
}

void MainWindow::start()
{
    if (!isServerStart) {
        startAction->setEnabled(false);
        stopAction->setEnabled(true);
        isServerStart = true;
        initSocketLink();
        QMessageBox::information(this, tr("Wiidroid"), tr("服务启动成功"), QMessageBox::Yes);
    }
}

void MainWindow::stop()
{
    if (isServerStart) {
        startAction->setEnabled(true);
        stopAction->setEnabled(false);
        isServerStart = false;
        abortSocketLink();
        QMessageBox::information(this, tr("Wiidroid"), tr("服务停止成功"), QMessageBox::Yes);
    }
}

void MainWindow::setting()
{
    QMessageBox::information(this, tr("Wiidroid"), tr("设置菜单尚未添加"), QMessageBox::Yes);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("关于"),
            tr("<h2>Wiidroid-II</h2>"
            "<p><h3>基于智能手机传感器的跨平台体感终端之PC端。</h3>"
               "<p>Copyright (C) 2013 "));
}

void MainWindow::trayExit()
{
        isTrayExit = true;
        this->close();
}

void MainWindow::createSystemTrayIcon()
{
    // 检测系统是否支持托盘图标
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        systemTrayIcon = NULL;
        return;
    }

    trayMenu = new QMenu();
    trayMenu->addAction(startAction);
    trayMenu->addAction(stopAction);
    trayMenu->addSeparator();
    trayMenu->addAction(trayExitAction);

    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setIcon(QIcon(":/res/ico/main.ico"));
    systemTrayIcon->setToolTip(tr("Wiidroid"));
    systemTrayIcon->setContextMenu(trayMenu);
    systemTrayIcon->show();
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(showWindow(QSystemTrayIcon::ActivationReason)));
}

QString MainWindow::getHostIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    foreach (QHostAddress address, list) {
        // 只获取 IPv4 协议地址
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address.toString() != QString("127.0.0.1")) {
            return address.toString();
        }
    }

    return 0;
}

void MainWindow::showWindow(QSystemTrayIcon::ActivationReason type)
{
    // 仅在托盘图标单击时候显示主界面，右击显示菜单
    if (type == QSystemTrayIcon::Trigger || type == QSystemTrayIcon::DoubleClick) {
        this->showNormal();
    }
}

void MainWindow::broadcastUdpServerInfo()
{
    broadcastServerSocket->writeDatagram(udpSendMsg, QHostAddress::Broadcast, 8086);
}

void MainWindow::showTrayInfo(QString strInfo, unsigned int msec)
{
    if (systemTrayIcon != NULL) {
        systemTrayIcon->showMessage(tr("Wiidroid"),
            strInfo, QSystemTrayIcon::Information, msec);
    }
}

void MainWindow::newClientLink()
{
    clientSocket = tcpServerSocket->nextPendingConnection();
    qDebug() << "New Client Linked, IP:" << clientSocket->peerAddress().toString()
             << " Port: " << clientSocket->peerPort() << "\n";
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(clientDataReceived()));
}

void MainWindow::clientDataReceived()
{
    while (clientSocket->bytesAvailable()) {
        QByteArray recvMsg = clientSocket->readAll();
        recvBuffer.append(recvMsg);
        QString strProtoTag("</wiidroid>");
        int tagLen = strProtoTag.size();
        int pos = recvBuffer.indexOf(strProtoTag);
        while ((pos = recvBuffer.indexOf(strProtoTag)) != -1) {
            QByteArray recvPacket(recvBuffer.data(), pos+tagLen);
            recvBuffer.remove(0, recvPacket.size());
            if (recvBuffer.at(0) == '\n') {
                recvBuffer.remove(0, 1);
            } else if (recvBuffer.at(0) == '\r' && recvBuffer.at(1) == '\n') {
                recvBuffer.remove(0, 2);
            }
            parseProtoPackage(recvPacket);
        }
    }
}

void MainWindow::parseProtoPackage(QByteArray &recvPacket)
{
    KeyPressInfo keyPressInfo;
    ASpeedInfo aSpeedInfo;
    GyroscopeInfo gyroscopeInfo;

    switch (ProtocolXml::getXmlInfoType(recvPacket)) {
    // 客户端控制（键盘消息）
    case PROTO_CONTROL_KEY:
        ProtocolXml::parseKeyInfo(recvPacket, keyPressInfo);
        qDebug() << "客户端控制（键盘消息）: \n Key: " << keyPressInfo.key
                 << " isPress: " << keyPressInfo.isPress << "\n";
        break;
    // 客户端控制（加速度传感器）
    case PROTO_CONTROL_ASPEED:
        ProtocolXml::parseASpeedInfo(recvPacket, aSpeedInfo);
        qDebug() << "客户端控制（加速度传感器）\n x: " << aSpeedInfo.x
                 << " y: " << aSpeedInfo.y << " z: " << aSpeedInfo.z << "\n";
        break;
    // 客户端控制（陀螺仪）
    case PROTO_CONTROL_GYROSCOPE:
        ProtocolXml::parseGyroscopeInfo(recvPacket, gyroscopeInfo);
        qDebug() << "客户端控制（陀螺仪）\n x: " << gyroscopeInfo.x
                 << " y: " << gyroscopeInfo.y << " z: " << gyroscopeInfo.z << "\n";
        break;
    case -1:
        qDebug() << "Error Package Format!\n";
    }
}
