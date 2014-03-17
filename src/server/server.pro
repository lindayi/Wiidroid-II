# =====================================================================================
# 
#       Filename:  server.pro
#
#    Description:  server 项目文件
#
#        Created:  2014年03月13日 19时22分01秒
#
#         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
#        Company:  Class 1107 of Computer Science and Technology
#
# =====================================================================================

QT += network

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# debug control
#DEFINES+= QT_NO_DEBUG_OUTPUT

# Input
HEADERS += src/MainWindow.h \
    		src/ProtocolXml.h \
    		src/ProtocolType.h
SOURCES += src/Main.cpp src/MainWindow.cpp \
    		src/ProtocolXml.cpp

RESOURCES += server.qrc
RC_FILE = logo.rc

