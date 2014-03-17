// =====================================================================================
//
//       Filename:  MainWindow.h
//
//    Description:  主窗口的头文件
//
//        Version:  1.0
//        Created:  2014年03月13日 19时16分49秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
//
// =====================================================================================

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QString>
#include <QMap>

class QLabel;
class QMenu;
class QAction;
class QPushButton;
class QToolBar;
class QSystemTrayIcon;

class QHBoxLayout;
class QVBoxLayout;

class QTcpServer;
class QTcpSocket;
class QUdpSocket;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showTrayInfo(QString strInfo, unsigned int msec = 2000);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void start();
    void stop();
    void setting();
    void about();
    void trayExit();
    void broadcastUdpServerInfo();
    void newClientLink();
    void clientDataReceived();
    void showWindow(QSystemTrayIcon::ActivationReason type);

private:
    void createMainWeiget();	// 创建主窗口
    void createActions();		// 创建动作
    void createMenus();		// 创建主菜单
    void createToolBars();		// 创建工具栏
    void createStatusBar();		// 创建状态栏
    void createSystemTrayIcon();	// 创建系统托盘图标
    void initSocketLink();          // 初始化套接字连接
    void abortSocketLink();       // 关闭服务器连接
    void parseProtoPackage(QByteArray &recvPacket); // 解析接收的数据包
    QString getHostIP();            // 获取本机IP

    QSystemTrayIcon *systemTrayIcon; // 系统托盘图标

    QMenu *fileMenu; 		// 文件菜单
    QMenu *setMenu; 		// 设置菜单
    QMenu *helpMenu; 		// 帮助菜单
    QMenu *trayMenu; 		// 托盘菜单

    QToolBar *mainToolBar;		// 工具栏

    QAction *startAction; 		// 启动服务
    QAction *stopAction; 		// 停止服务
    QAction *settingAction; 	// 设置
    QAction *aboutAction; 		// 关于
    QAction *exitAction; 		// 退出
    QAction *trayExitAction;    // 托盘退出

    QLabel *statusLabel; 		// 状态栏

    bool isServerStart; 		// 服务器是否启动
    bool isTrayExit; 		// 是否是托盘退出

    QUdpSocket	*udpServerSocket;          // 服端端接收命令UDP套接字
    QTcpServer  *tcpServerSocket;           // 服务端接收命令TCP套接字

    QUdpSocket	*broadcastServerSocket;     // 服务端广播信息套接字
    QTimer      *broadcastTimer;            // 广播服务器信息定时器
    QString     strServerIP;                // 服务器自身IP
    QString     strServerPort;              // 服务器自身端口
    QByteArray  udpSendMsg;                  // UDP广播的服务器信息
    QTcpSocket  *clientSocket;               // 客户端套接字（单用户）
    QByteArray  recvBuffer;                 // 客户端接收缓冲区
};

#endif 	// MAINWINDOW_H_
