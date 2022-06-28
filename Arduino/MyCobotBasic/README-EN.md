# 10.3 Arduino 库的使用

支持机械臂类型：**myCobot280-Arduino**<br>

使用案例：打开**C:\Users\User\Documents\Arduino\libraries\MyCobotBasic\examples\ControlRobot\ControlRobot.ino**，此案例需要先对开发板进行烧录，再与机械臂连接，否则会出现上传失败的情况。<br>

使用底部basic库您可以在Arduino下自由开发，控制我们公司的机械臂。<br>

## 10.3.1 编译前的修改

导入库文件，如果您的机械臂是myCobot280-Arduino，请检查开发板是否为Mega2560或者Uno，如果是：<br>

1.请将**avr-libstdcpp**放到**C:\Users\User\Documents\Arduino\libraries**下:<br>

![pic](../resourse/10-ArduinoEnv/10.3/1.png)<br>

![pic](../resourse/10-ArduinoEnv/10.3/2.png)<br>

2.请修改avr官方库里面串口缓冲区的大小，修改**C:\Users\User\AppData\Local\arduino15\packages\arduino\hardware\avr\1.8.5\cores\arduino\HardwareSerial.h**,按下图修改即可：<br>

![pic](../resourse/10-ArduinoEnv/10.3/3.png)<br>

![pic](../resourse/10-ArduinoEnv/10.3/4.png)<br>

如果您使用的是myCobot280-Arduino，请查看开发板是否为mega2560，如果不是，**请打开ParameterList.h,将第5行加上注释，**同时**取消相应开发板的注释：**

![pic](../resourse/10-ArduinoEnv/10.3/5.png)<br>

如果使用的是myCobot280-M5，需要取消**m5的注释：**

![pic](../resourse/10-ArduinoEnv/10.3/6.png)<br>

## 10.3.2 编译前开发板的选择

1.开发板为Uno、Mega2560,工具--》开发板--》Arduino AVR Boards-->Arduino Uno（或者Arduino MEAG or Mega2560)，具体可看下图：

![pic](../resourse/10-ArduinoEnv/10.3/7.png)<br>

2.开发板为mkr wifi1010<br>
开发板管理器搜索samd，如果没有安装，就安装，首先工具--》开发板--》开发板管理器，然后搜索samd，具体可看下图：

![pic](../resourse/10-ArduinoEnv/10.3/8.png)<br>

![pic](../resourse/10-ArduinoEnv/10.3/9.png)<br>

开发板选择mkr wifi1010，工具--》开发板--》Arduino SAMD--》Arduino MKR WiFi1010

![pic](../resourse/10-ArduinoEnv/10.3/10.png)<br>
