// =====================================================================================
//
//       Filename:  Protocoltype.h
//
//    Description:  协议类型定义
//
//        Version:  1.0
//        Created:  2014年03月17日 9时59分21秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
//
// =====================================================================================

#ifndef PROTOCOLTYPE_H_
#define PROTOCOLTYPE_H_

// UDP广播服务器信息
#define PROTO_SERVERINFO        (0)

// 客户端控制（键盘消息）
#define PROTO_CONTROL_KEY       (10)

// 客户端控制（加速度传感器）
#define PROTO_CONTROL_ASPEED    (11)

// 客户端控制（陀螺仪）
#define PROTO_CONTROL_GYROSCOPE (12)

// 键盘消息
struct KeyPressInfo {
    int key;
    bool isPress;
};

// 加速度传感器消息
struct ASpeedInfo {
    double x;
    double y;
    double z;
};

// 陀螺仪消息
struct GyroscopeInfo {
    double x;
    double y;
    double z;
};

#endif // PROTOCOLTYPE_H_
