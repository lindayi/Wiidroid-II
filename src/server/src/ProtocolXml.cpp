// =====================================================================================
//
//       Filename:  ProtocolXml.cpp
//
//    Description:  Xml格式解析
//
//        Version:  1.0
//        Created:  2014年03月17日 9时18分23秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
//
// =====================================================================================

#include <QtGui>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "ProtocolXml.h"
#include "ProtocolType.h"

/*
<?xml version="1.0" encoding="utf-8" ?>
    <wiidroid type="0">              // 消息类型 0
        <ip>xxx.xxx.xxx.xxx</ip>    // 服务器端IP
        <port>x</port>              // 服务器端TCP端口
    </wiidroid>
</xml>
*/
QByteArray ProtocolXml::CreateBroadcastInfoXml(QString ip, QString port)
{
    QByteArray strXml;
    QXmlStreamWriter stream(&strXml);

    stream.setAutoFormatting(true);

    stream.writeStartDocument();
    stream.writeStartElement("wiidroid");
    stream.writeAttribute("type", QString::number(PROTO_SERVERINFO));

    stream.writeTextElement("ip", ip);
    stream.writeTextElement("port", port);

    stream.writeEndElement();
    stream.writeEndDocument();

    return strXml;
}

int ProtocolXml::getXmlInfoType(QByteArray &recvPacket)
{
    QXmlStreamReader reader(recvPacket);

    while (!reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();

        if (type == QXmlStreamReader::StartElement) {
            if (reader.name() == "wiidroid" && reader.attributes().hasAttribute("type")) {
                return reader.attributes().value("type").toString().toInt();
            }
        }
    }

    if (reader.hasError()) {
        qDebug() << "XML Format Error:" << reader.errorString() << "\r\n";
    }

    return -1;
}

/*
<?xml version="1.0" encoding="utf-8" ?>
    <wiidroid type="10">            // 消息类型 10
        <key>x</key>                // 键盘按下的键的编码
        <status>0</status>          // 状态 按下为 1，松开为 0
    </wiidroid>
 */
void ProtocolXml::parseKeyInfo(QByteArray &recvPacket, KeyPressInfo &keyPressInfo)
{
    QXmlStreamReader reader(recvPacket);

    while (!reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();

        if (type == QXmlStreamReader::StartElement) {
            if (reader.name() == "key") {
                keyPressInfo.key = reader.readElementText(QXmlStreamReader::SkipChildElements).toInt();
            } else if (reader.name() == "status") {
                keyPressInfo.isPress = (bool)reader.readElementText(QXmlStreamReader::SkipChildElements).toInt();
            }
        }
    }

    if (reader.hasError()) {
        qDebug() << "XML Format Error:" << reader.errorString() << "\r\n";
    }
}

/*
<?xml version="1.0" encoding="utf-8" ?>
    <wiidroid type="11">           // 消息类型 11
        <coord-x>x</coord-x>       // x, y, z 三轴数据
        <coord-y>y</coord-y>
        <coord-z>z</coord-z>
     </wiidroid>
 */
void ProtocolXml::parseASpeedInfo(QByteArray &recvPacket, ASpeedInfo &aSpeedInfo)
{
    QXmlStreamReader reader(recvPacket);

    while (!reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();

        if (type == QXmlStreamReader::StartElement) {
            if (reader.name() == "coord-x") {
                aSpeedInfo.x = reader.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
            } else if (reader.name() == "coord-y") {
                aSpeedInfo.y = reader.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
            } else if (reader.name() == "coord-z") {
                aSpeedInfo.z = reader.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
            }
        }
    }

    if (reader.hasError()) {
        qDebug() << "XML Format Error:" << reader.errorString() << "\r\n";
    }
}

/*
<?xml version="1.0" encoding="utf-8" ?>
    <wiidroid type="12">           // 消息类型 12
        <coord-x>x</coord-x>       // x, y, z 三轴数据
        <coord-y>y</coord-y>
        <coord-z>z</coord-z>
    </wiidroid>
*/
void ProtocolXml::parseGyroscopeInfo(QByteArray &recvPacket, GyroscopeInfo &gyroscopeInfo)
{
    QXmlStreamReader reader(recvPacket);

    while (!reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();

        if (type == QXmlStreamReader::StartElement) {
            if (reader.name() == "coord-x") {
                gyroscopeInfo.x = reader.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
            } else if (reader.name() == "coord-y") {
                gyroscopeInfo.y = reader.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
            } else if (reader.name() == "coord-z") {
                gyroscopeInfo.z = reader.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
            }
        }
    }

    if (reader.hasError()) {
        qDebug() << "XML Format Error:" << reader.errorString() << "\r\n";
    }
}
