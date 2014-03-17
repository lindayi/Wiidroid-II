// =====================================================================================
//
//       Filename:  ProtocolXml.h
//
//    Description:  Xml格式解析
//
//        Version:  1.0
//        Created:  2014年03月17日 9时16分23秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
//
// =====================================================================================

#ifndef PROTOCOLXML_H_
#define PROTOCOLXML_H_

#include <QString>
#include <QByteArray>

#include "ProtocolType.h"

class ProtocolXml
{
public:
    // 创建服务器广播信息XML结构
    static QByteArray CreateBroadcastInfoXml(QString ip, QString port);

    // 从XML包中解析出协议Type
    static int getXmlInfoType(QByteArray &recvPacket);

    // 解析客户端控制（键盘消息）
    static void parseKeyInfo(QByteArray &recvPacket, KeyPressInfo &keyPressInfo);

    // 解析客户端控制（加速度传感器）
    static void parseASpeedInfo(QByteArray &recvPacket, ASpeedInfo &aSpeedInfo);

    // 解析客户端控制（陀螺仪）
    static void parseGyroscopeInfo(QByteArray &recvPacket, GyroscopeInfo &gyroscopeInfo);
};

#endif // PROTOCOLXML_H_
