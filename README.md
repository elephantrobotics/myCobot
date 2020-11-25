# myCobot
myCobot is the worlds smallest collaborative robot arm. 
以上程序只适用于myCobot底座上的M5 Basic控制器进行使用
This is for M5 Basic Board to use only !

# M5 Stack Basic
M5Stack Basic 的基本应用与烧录可以参考以下链接
https://docs.m5stack.com/#/zh_CN/core/basic

# Library & Example 
如果您在使用案例，请先测试 SimpleTest.ino 文件验证通讯，该程序应烧录到底层Basic中

# API
## setServoEncoder (byte servo_no, int servo_encoder, int servo_sp);
控制指定关节，以指定速度转动至指定电位值：
关节序号 = servo_no，取值范围 1-6；
指定电位值 = servo_encoder，取值范围0-4096；
指定速度 = servo_sp，取值范围0-4000,；

## setAngle (byte servo_no, int angle, int sp);
控制指定关节，以指定速度旋转到对应角度：
关节序号 = servo_no，取值范围 1-6；
指定角度 = angle，取值范围 -170°— + 170°；
指定速度 = sp，取值范围0-4000,；

## setServosEncoder (int servo_encoder_1, int servo_encoder_2, int servo_encoder_3, int servo_encoder_4, int servo_encoder_5, int servo_encoder_6, int servo_sp);
指定六个关节舵机以指定速度转动至指定电位值：
1号舵机电位值 = servo_encoder_1，取值范围 0 – 4096；
2号舵机电位值 = servo_encoder_2，取值范围 0 – 4096；
3号舵机电位值 = servo_encoder_3，取值范围 0 – 4096；
4号舵机电位值 = servo_encoder_4，取值范围 0 – 4096；
5号舵机电位值 = servo_encoder_5，取值范围 0 – 4096；
6号舵机电位值 = servo_encoder_6，取值范围 0 – 4096；
指定速度 = servo_sp，取值范围 0 - 4000；

## calibrateServo (byte servo_no);
设定当前电位值为舵机角度零点：
关节舵机编号 = servo_no；

## setServoData (byte servo_no, byte servo_state, byte servo_data);
设定关节舵机的相关参数，可修改参数包括：PID、舵机指示灯、最小启动力：
指定关节舵机序号 = servo_no，取值范围 1 – 6；
可修改参数地址 = servo_state，如表1-1；
可修改参数值 = servo_data，如表 1-1；



## releaseAllServos ();

控制舵机扭力输出为0，使机械臂处于卸力状态；

## getAngleEncoder (byte joint_no);

读取关节舵机当前的电位值：
关节舵机序号 = joint_no；

## getAngle (byte joint_no);

获取当前舵机的角度值：
关节舵机序号 = joint_no；

## setRGB (byte R, byte G, byte B);

设定atom屏幕的RGB灯的颜色：
红色光对应参数值 = R，取值范围 0x00 – 0xFF；
绿色光对应参数值 = G，取值范围 0x00 – 0xFF；
蓝色光对应参数值 = B，取值范围 0x00 – 0xFF；

## setColor(byte color);
设定atom屏幕的RGB灯的颜色：
状态值取值 = color，取值范围如下表：

## setAtomPinMode (byte pin, byte mode);
设置atom指定引脚的输入输出状态：
指定引脚序号 = pin；
指定状态值 = mode，取值1位输出、0为输入；

## setAtomDigitalWrite (byte pin, byte data);
设置atmo指定引脚输出的状态值：
指定引脚序号 = pin；
指定状态值 = data；

