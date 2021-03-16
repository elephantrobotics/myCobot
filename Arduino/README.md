
# myCobot
myCobot is the worlds smallest collaborative robot arm.   
以上程序只适用于myCobot底座上的M5 Basic控制器进行使用  
This is for M5 Basic Board to use only !

如果您使用我们的库，并且需要运行历程,但是编译器提示mycobot_24px.h文件报错，那请您先修改语言配置  
* windows  
> 打开：" C:\Users\Admin\Documents\Arduino\libraries\M5Stack\src\utility/ln_eSPI_Setup.h "  
> 取消最后一句代码的注释,如图：

![](font.png)

# M5 Stack Basic
M5Stack Basic 的基本应用与烧录可以参考以下链接
https://docs.m5stack.com/#/zh_CN/core/basic

# Library & Example 
Should directly read MycobotBasic.h and MycobotBasic.cpp

# Update on 4th Feb
Can only be used with AtomMain2.5 in myStudio0.05
https://github.com/elephantrobotics/myStudio/releases

setGripperValue() 	// the gripper encoder number(from 0 to 4096) get gripper value before use

setGripperIni() 	// set gripper encode initial center point(to be 2048)

getGripperValue() 	// return gripper encdoer value (from 0 to 4096)

setGripperState 	// only used for adaptive gripper, 0 or 1 for open and close

setDigitalOutput 	// set pinmode before use: 0 input; 1 output; 2 pull_up_input

getDitialInput 	// get input

setPWMMode(pin_no, channel) // channel can be set from 0 to 128

setPWMOutput(channel, output) // channel should be initialized before use, output is frequency, should be 0 to 256;  128 means 50% pwm

