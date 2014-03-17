// =====================================================================================
// 
//       Filename:  Main.cpp
//
//    Description:  入口函数
//
//        Version:  1.0
//        Created:  2014年03月13日 19时13分25秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <QtGui>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	// 处理中文乱码问题
	QTextCodec *codec = QTextCodec::codecForName("system");

	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);

	QApplication app(argc, argv);

	// 添加启动logo
//	QSplashScreen *splash = new QSplashScreen;
//	splash->setPixmap(QPixmap(":/res/images/logo.png"));
//	splash->show();

	MainWindow *mainwindow = new MainWindow();

    mainwindow->move((QApplication::desktop()->width() - mainwindow->width()) >> 1,
                (QApplication::desktop()->height() - mainwindow->height() - 40) >> 1);

	mainwindow->show();

//	splash->finish(mainwindow);
//	delete splash;

	return app.exec();
}

