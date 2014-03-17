应用层通信协议定义
========================

## 简介
本项目客户端和服务端采用各自平台的socket接口进行通信，应用层消息采用标准的XML格式进行传递。本文档定义了客户端和服务端在进行消息交互时所使用的具体XML格式。

## 消息分类

**目前消息分为两类：**

### 一 服务端广播的自身IP和Port信息；

服务器广播的目标端口：UDP 9527

消息格式：
```
<?xml version="1.0" encoding="utf-8" ?>
    <type>0</type>              // 消息类型 0
    <ip>xxx.xxx.xxx.xxx</ip>    // 服务器端IP
    <port>x</port>              // 服务器端TCP端口
</xml>
```

### 二 服务端接收的客户端控制或传感器信息；

- 键盘消息
```
<?xml version="1.0" encoding="utf-8" ?>
    <type>10</type>     // 消息类型 10
    <key>x</key>        // 键盘按下的键的编码
    <status>0</status>  // 状态 按下为 1，松开为 0
</xml>
```

- 加速度传感器数据
```
<?xml version="1.0" encoding="utf-8" ?>
    <type>11</type>         // 消息类型 11
    <coord-x>x</coord-x>    // x, y, z 三轴数据
    <coord-y>y</coord-y>
    <coord-z>z</coord-z>
</xml>
```

- 陀螺仪数据
```
<?xml version="1.0" encoding="utf-8" ?>
    <type>12</type>         // 消息类型 12
    <coord-x>x</coord-x>    // x, y, z 三轴数据
    <coord-y>y</coord-y>
    <coord-z>z</coord-z>
</xml>
```
