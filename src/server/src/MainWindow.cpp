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
#include <QDebug>

#include "MainWindow.h"

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
		isTrayExit = true;
	} else {
		systemTrayIcon->hide();
		event->accept();
	}
}

void MainWindow::createMainWeiget()
{
	setWindowIcon(QIcon(":/res/ico/main.ico"));
	setWindowTitle(tr("Wiidroid -- Alpha 1"));
	resize(400, 300);
	isServerStart = false;
	isTrayExit = false;
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
	
	settingAction = new QAction(tr("设置"), this);
	settingAction->setIcon(QIcon(":/res/images/setting.png"));
	settingAction->setStatusTip(tr("设置 Wiidroid"));
	connect(settingAction, SIGNAL(triggered()), this, SLOT(setting()));
	
	aboutAction = new QAction(tr("关于"), this);
	aboutAction->setIcon(QIcon(":/res/ico/main.ico"));
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

void MainWindow::start()
{
	if (!isServerStart) {
		startAction->setEnabled(false);
		stopAction->setEnabled(true);
		isServerStart = true;
		QMessageBox::information(this, tr("Wiidroid"), tr("服务启动成功"), QMessageBox::Yes);
	}
}

void MainWindow::stop()
{
	if (isServerStart) {
		startAction->setEnabled(true);
		stopAction->setEnabled(false);
		isServerStart = false;
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
	trayMenu->addAction(exitAction);

	systemTrayIcon = new QSystemTrayIcon(this);
	systemTrayIcon->setIcon(QIcon(":/res/ico/main.ico"));
	systemTrayIcon->setToolTip(tr("Wiidroid"));
	systemTrayIcon->setContextMenu(trayMenu);
	systemTrayIcon->show();
	connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
				this, SLOT(showWindow(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::showWindow(QSystemTrayIcon::ActivationReason type)
{
	// 仅在托盘图标单击时候显示主界面，右击显示菜单
	if (type == QSystemTrayIcon::Trigger || type == QSystemTrayIcon::DoubleClick) {
		this->showNormal();
		isTrayExit = true;
	}
}

void MainWindow::showTrayInfo(QString strInfo, unsigned int msec)
{
	if (systemTrayIcon != NULL) {
		systemTrayIcon->showMessage(tr("Wiidroid"),
			strInfo, QSystemTrayIcon::Information, msec);
	}
}
