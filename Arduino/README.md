# myCobot: Arduino

Please review [root-level README](../) first!

# M5 Stack Basic

以上程序只适用于myCobot底座上的M5 Basic控制器进行使用
This robot only deals with M5 Basic Board only!

M5Stack Basic 的基本应用与烧录可以参考以下链接
Please refer to the following link for the basic application and programming of
M5Stack:

- <https://docs.m5stack.com/#/zh_CN/core/basic> (Chinese)
- <https://docs.m5stack.com/#/en/core/basic> (English)

# Library & Example 

To start, please see `MycobotBasic.h` and `MycobotBasic.cpp`

## Update

- Can only be used with AtomMain3.1 in myStudio2.2
https://github.com/elephantrobotics/myStudio/releases

- 本次更新修复了大多数角度控制函数的处理方式


# FAQ

如果您使用我们的库，并且需要运行历程,但是编译器提示mycobot_24px.h文件报错，那请您先修改语言配置  
* windows  
> 打开：" C:\Users\Admin\Documents\Arduino\libraries\M5Stack\src\utility/ln_eSPI_Setup.h "  
> 取消最后一句代码的注释,如图：

![font](font.png)
