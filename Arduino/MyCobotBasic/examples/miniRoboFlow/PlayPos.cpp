 #include "PlayPos.h"

using PAngles = std::array<float, 6>;

int mycobot_point_mode = 0;

byte point_num = 1;

typedef struct PointInfo{
    PAngles joint_angles;
    int pump_state;
    int gripper_state;
};
PointInfo pointinfo[100];


static int EXIT_point = false;

int count_btn_A = 0;
int pN = 0;                 //被选中的点位
int setting_mode = 0;
int info_mode = 0;
int play_mode = 0;
int pump_mode = 0;
int gripper_mode = 0;
int pin_no = 5;
bool pin_data = 0;
bool is_stop = 0;
bool flag = 1;      //用于标志舵机是否上电

int y[5] = { 70, 95, 120, 145, 165 };  // y_pos

void PlayPos::run(MyCobotBasic& myCobot) {
    //pinMode(control_pin_point, INPUT);
    myCobot.setLEDRGB(255, 0, 255);
    PlayPos::update(myCobot, mycobot_point_mode);
    PlayPos::displayPointInfo(myCobot, 0, 0);
    
    while (1) {
        M5.update();
        byte btn_pressed = 0;
        if (M5.BtnA.wasReleased()) {
            btn_pressed = 1;

            PlayPos::update(myCobot, btn_pressed);
        }
        if (M5.BtnB.wasReleased()) {
           
            count_btn_A = 0;
            
            btn_pressed = 2;
            PlayPos::update(myCobot, btn_pressed);
            setting_mode = 0;
            
        }
        if (M5.BtnC.wasReleased()) {
            count_btn_A = 0;
            setting_mode = 0;
            btn_pressed = 3;
            PlayPos::update(myCobot, btn_pressed);
            
        }
        if (EXIT_point) {
            EXIT_point = false;
            break;
        }
        //PlayPos::getIO(myCobot);
    }
}


void PlayPos::update(MyCobotBasic& myCobot, byte btn_pressed) 
{
    if(mycobot_point_mode == 0)
    {
        switch (btn_pressed)
        {
          case 1:
            mycobot_point_mode = 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
          case 2:
            mycobot_point_mode = 2;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
          case 3:
              myCobot.releaseServo(7);
              EXIT_point = true;
              break;
        }
    }
    else if (mycobot_point_mode == 1)
    {

        switch (btn_pressed)
        {
        case 1:                                  //choose point
            mycobot_point_mode = 1;
            count_btn_A = count_btn_A + 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, count_btn_A);
            pN = count_btn_A % point_num;         // pN = point_1/2/3
            break;
        case 2:                                  //Point operate
            mycobot_point_mode = 12;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;

        case 3:
            mycobot_point_mode = 0; //get back
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            pN = 0;
            break;
        }
    }

    else if (mycobot_point_mode == 2)
    {

        switch (btn_pressed)
        {
        case 1:
            mycobot_point_mode = 2;
            count_btn_A = count_btn_A + 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, count_btn_A);
            play_mode = count_btn_A % 3;   //play_mode = play for once/loop/delete
            break;
        case 2:
            if (play_mode == 0) mycobot_point_mode = 20;
            else if (play_mode == 1) mycobot_point_mode = 21;
            else mycobot_point_mode = 22;
            delay(3);
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
            // confirm operate point
            break;

        case 3:
            mycobot_point_mode = 0; //get back
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }
    }

    else if (mycobot_point_mode == 12)
    {
        switch (btn_pressed)
        {
        case 1:
            mycobot_point_mode = 12;
            count_btn_A = count_btn_A + 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, count_btn_A);
            setting_mode = count_btn_A % 3;      // setting mode = add/modify/delete
            Serial.println(setting_mode);
            break;
        case 2:
            Serial.println(setting_mode);
            mycobot_point_mode = PlayPos::setPoint(myCobot, 122, setting_mode);
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        case 3:
            mycobot_point_mode = 1; //get back
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }
    }

    else if (mycobot_point_mode == 122)
    {

        switch (btn_pressed)
        {
        case 1:
            mycobot_point_mode = 122;
            count_btn_A = count_btn_A + 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, count_btn_A);
            info_mode = count_btn_A % 3; 
            break;
        case 2:
            if (info_mode == 0) mycobot_point_mode = 1220;
            else if (info_mode == 1) mycobot_point_mode = 1221;
            else mycobot_point_mode = 1222;
            delay(3);
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;

        case 3:
            mycobot_point_mode = 12; //get back
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }
    }

    else if (mycobot_point_mode == 1220)
    {

        switch (btn_pressed)
        { 
        case 1:                           // power on/off
            // Serial.println("flag");
            // Serial.println(flag);
            if (flag) 
            {
                for (int i = 1; i <=6; i++) {
                    myCobot.releaseServo(i);
                    flag = 0;
                    delay(200);
                }
            }
            else 
            {
                myCobot.powerOn();
                delay(20);
                flag = 1;
            }
            
            while (1)
            {
                M5.update();
                if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(200))
                {
                    myCobot.powerOn();
                    delay(20);
                    flag = 1;
                    break;
                }
                pointinfo[pN].joint_angles = myCobot.getAngles();
                delay(200);
                M5.Lcd.fillRect(10, 40, 150, 150, BLACK);  //清空矩形区域
                for (int i = 0; i < 6; i++)
                {
                    M5.Lcd.setCursor(20, 40 + 25 * i);
                    M5.Lcd.print(pointinfo[pN].joint_angles[i]);
                    delay(20);
                }
            } 
            
            break;

        case 2:                          // getangles
            pointinfo[pN].joint_angles = myCobot.getAngles();
            mycobot_point_mode = 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, pN);
            break;
        
        case 3:                         // exit
            mycobot_point_mode = 122;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }
    }

    else if (mycobot_point_mode == 1221) 
    {
        
        switch (btn_pressed)
        {
        case 1:                     // choose pump 1；open/close
            mycobot_point_mode = 1221;
            count_btn_A = count_btn_A + 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, count_btn_A);
            pump_mode = count_btn_A % 2;
            break;
        case 2:
            pinMode(pin_no, OUTPUT);
            digitalWrite(pin_no, pump_mode);
            mycobot_point_mode = 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, pN);
            break;
        case 3:
            mycobot_point_mode = 122;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }
    
    }

    else if (mycobot_point_mode == 1222)
    {
        switch (btn_pressed)
        {
        case 1:                   // choose gripper mode
            mycobot_point_mode = 1222;
            count_btn_A = count_btn_A + 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, count_btn_A);
            gripper_mode = count_btn_A % 2;
            break;
        case 2:                   //save
            if (gripper_mode == 0)
            {
                pointinfo[pN].gripper_state = 0;
                myCobot.setGripperState(pointinfo[pN].gripper_state, 5);
            }
            else
            {
                pointinfo[pN].gripper_state = 1;
                myCobot.setGripperState(pointinfo[pN].gripper_state, 5);
            }
            mycobot_point_mode = 1;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, pN);
            break;
        case 3:
            mycobot_point_mode = 122;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }

    }

    else if (mycobot_point_mode == 20) 
    {
        switch (btn_pressed)
        {
        case 1:
            for (int i = 0; i < point_num; i++)
            {
                myCobot.writeAngles(pointinfo[pN].joint_angles, 5);
                delay(3);
            }
            M5.Lcd.setCursor(20, 90);
            M5.Lcd.printf("Running");
            break;
        case 2:
            if (!is_stop) {
                myCobot.pause();
                is_stop = 1;
            }
            M5.Lcd.setCursor(20, 90);
            M5.Lcd.printf("Running");
            break;
        case 3:
            mycobot_point_mode = 2;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }

    }

    else if (mycobot_point_mode == 21)
    {
        switch (btn_pressed)
        {
        case 1:
            while (1)
            {
                for (int i = 0; i < point_num; i++)
                {
                    myCobot.writeAngles(pointinfo[pN].joint_angles, 5);
                    delay(3);
                }
            }
            break;
        case 2:
            if (!is_stop) {
                myCobot.pause();
                is_stop = 1;
            }
            break;
        case 3:
            mycobot_point_mode = 2;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }
    }

    else if (mycobot_point_mode == 22)
    {
        switch (btn_pressed)
        {
        case 1:
            point_num = point_num - 1;
            mycobot_point_mode = 2;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        case 2:
            mycobot_point_mode = 2;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        case 3:
            mycobot_point_mode = 2;
            PlayPos::displayPointInfo(myCobot, mycobot_point_mode, 0);
            break;
        }

    }


}

int PlayPos::setPoint(MyCobotBasic& myCobot, int mode, byte pSetmode)
{
        switch (pSetmode)
        {
        case 0:   //add
            point_num = point_num + 1;
            return mode;
            break;
        case 1:
            //todo
            return mode;
            break;
        case 2:   //delete
            point_num = point_num - 1;
            mode = 1;
            return mode;
            break;
        }
}

    
void PlayPos:: point_play(MyCobotBasic& myCobot)
{
    //todo
}


void PlayPos::displayPointInfo(MyCobotBasic& myCobot, int mode, byte n)
{
    M5.Lcd.clear(BLACK);
    delay(50);
    M5.Lcd.setTextSize(2);
    int buttom_y = 190;  //use for CN
    int buttom_1y = 210;  //use for EN
    //int buttom_2y = 210;

    switch (mode)
    {
        case 0:
        {
            M5.Lcd.fillScreen(0);
            if (lan == 2)
            { 
                M5.Lcd.drawString(" 路点控制", 20, 40, 1);
                M5.Lcd.drawString("设置", 60, buttom_y, 1);
                M5.Lcd.drawString("播放", 160, buttom_y, 1);
                M5.Lcd.drawString("退出", 260, buttom_y, 1);
                M5.update();
            }
            else if (lan == 1)
            {
                M5.Lcd.clear(BLACK);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setCursor(0, 10);
                M5.Lcd.printf("myCobot");
                M5.Lcd.setCursor(0, 40);
                M5.Lcd.drawFastHLine(0, 70, 320, GREY);
                M5.Lcd.setTextSize(3);
                M5.Lcd.println("PlayPos Menu");
                M5.Lcd.setTextSize(2);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setCursor(30, 210);
                M5.Lcd.print("Set");
                M5.Lcd.setCursor(120, 210);
                M5.Lcd.print("Play");
                M5.Lcd.setCursor(230, 210);
                M5.Lcd.print("Exit");
                M5.update();
            }
            break;
        }

        case 1:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            
            if (lan == 2)
            {
                M5.Lcd.drawString(" 预览", 20, 40, 1);
                for (int i = 0; i < point_num; i++) {
                    M5.Lcd.drawString(" 点位", 30, y[i], 1);
                    M5.Lcd.setCursor(100, y[i]);
                    M5.Lcd.print(i+1);
                }
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%point_num]);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("向下");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("确认");
                M5.Lcd.drawString("返回", 260, buttom_y, 1);
            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.println("Preview");
                M5.Lcd.setTextColor(WHITE);
                //Serial.println("point_num");
                //Serial.println(point_num);
                for (int i = 0; i < point_num; i++) {
                    M5.Lcd.setCursor(30, y[i]);
                    M5.Lcd.setTextSize(2);
                    M5.Lcd.print("point");
                    M5.Lcd.setCursor(100, y[i]);
                    M5.Lcd.print(i+1);
                }
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%point_num]);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("down");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("ok");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 2:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 请选择路点播放模式", 20, 40, 1);
                M5.Lcd.drawString("单次播放", 30, 70, 1);
                M5.Lcd.drawString("循环播放", 30, 95, 1);
                M5.Lcd.drawString("删除路径", 30, 120, 1);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%3]);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("向下");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("确认");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");
                
            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("Play mode");
                M5.Lcd.setCursor(30, 70);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("Play_once");
                M5.Lcd.setCursor(30, 95);
                M5.Lcd.print("Play_loop");
                M5.Lcd.setCursor(30, 120);
                M5.Lcd.print("Delete_point");
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%3]);
               
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("down");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("ok");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 12:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 点位操作", 20, 40, 1);
                M5.Lcd.drawString("新增", 30, 70, 1);
                M5.Lcd.drawString("修改", 30, 95, 1);
                M5.Lcd.drawString("删除", 30, 120, 1);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%3]);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("向下");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("确认");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");
            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("PointSetting_Menu");
                M5.Lcd.setCursor(30, 70);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("Add");
                M5.Lcd.setCursor(30, 95);
                M5.Lcd.print("Modify");
                M5.Lcd.setCursor(30, 120);
                M5.Lcd.print("Delete");
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%3]);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("down");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("ok");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }
        
        case 122:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 点位信息", 20, 40, 1);
                M5.Lcd.drawString("记录点位", 30, 70, 1);
                M5.Lcd.drawString("记录吸泵", 30, 95, 1);
                M5.Lcd.drawString("记录夹爪状态", 30, 120, 1);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%3]);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("向下");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("确认");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");
            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("PointInformation");
                M5.Lcd.setCursor(30, 70);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("joint_Angles");
                M5.Lcd.setCursor(30, 95);
                M5.Lcd.print("pump_state");
                M5.Lcd.setCursor(30, 120);
                M5.Lcd.print("gripper_state");
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n%3]);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("down");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("ok");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 1220:
        {
            M5.Lcd.clear(BLACK);
            myCobot.powerOn();
            

            if (lan == 2)
            {
                M5.Lcd.drawString(" 记录点位", 100, 10, 1);
                Serial.print("joint_angles");
                    pointinfo[pN].joint_angles = myCobot.getAngles();
                    for (int i = 0; i < 6; i++)
                    {

                        M5.Lcd.setCursor(20, 50 + 25 * i);
                        M5.Lcd.print(pointinfo[pN].joint_angles[i]);
                        Serial.println(pN);
                        Serial.println(pointinfo[pN].joint_angles[i]);
                    }
                
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("力矩开关");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("存储");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");
            }
            if (lan == 1)
            {
                M5.Lcd.setTextColor(RED);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(150, 10);
                M5.Lcd.printf("current_angles");
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("power");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("save");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
                pointinfo[pN].joint_angles = myCobot.getAngles();
                delay(200);
                for (int i = 0; i < 6; i++)
                {
                    M5.Lcd.setCursor(20, 40 + 25 * i);
                    M5.Lcd.print(pointinfo[pN].joint_angles[i]);
                    delay(20);
                    Serial.println(pN);
                    Serial.println(pointinfo[pN].joint_angles[i]);
                }

            }
            break;
        }

        case 1221:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 吸泵状态", 20, 40, 1);
                M5.Lcd.drawString("打开", 30, 70, 1);
                M5.Lcd.drawString("关闭", 30, 95, 1);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n % 2]);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("向下");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("存储");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");
            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("Pump_State");
                M5.Lcd.setCursor(30, 70);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("open");
                M5.Lcd.setCursor(30, 95);
                M5.Lcd.print("close");
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n % 2]);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("down");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("save");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 1222: 
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 夹爪状态", 20, 40, 1);
                M5.Lcd.drawString("打开", 30, 70, 1);
                M5.Lcd.drawString("关闭", 30, 95, 1);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n % 2]);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("向下");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("存储");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");
            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("Gripper_State");
                M5.Lcd.setCursor(30, 70);
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.print("open");
                M5.Lcd.setCursor(30, 95);
                M5.Lcd.print("close");
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(0, y[n % 2]);
                M5.Lcd.print(" >");
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("down");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("save");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 20: 
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if(lan == 2)
            {
                M5.Lcd.drawString(" 单次播放", 20, 40, 1);
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("播放");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("暂停");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");

            }
            else if(lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("Play_once");
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("play");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("pause");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 21:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 循环播放", 20, 40, 1);
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("播放");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("暂停");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");

            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("Play_loop");
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("play");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("pause");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

        case 22:
        {
            M5.Lcd.fillScreen(0);
            M5.Lcd.clear(BLACK);
            if (lan == 2)
            {
                M5.Lcd.drawString(" 删除路径", 20, 40, 1);
                M5.Lcd.setCursor(60, buttom_y);
                M5.Lcd.print("删除");
                M5.Lcd.setCursor(160, buttom_y);
                M5.Lcd.print("放弃");
                M5.Lcd.setCursor(260, buttom_y);
                M5.Lcd.print("返回");

            }
            else if (lan == 1)
            {
                M5.Lcd.setCursor(0, 30);
                M5.Lcd.setTextSize(3);
                M5.Lcd.setTextColor(RED);
                M5.Lcd.print("Delete_point");
                M5.Lcd.setTextColor(WHITE);
                M5.Lcd.setTextSize(2);
                M5.Lcd.setCursor(40, buttom_1y);
                M5.Lcd.print("delete");
                M5.Lcd.setCursor(130, buttom_1y);
                M5.Lcd.print("cancel");
                M5.Lcd.setCursor(240, buttom_1y);
                M5.Lcd.print("Back");
            }
            break;
        }

    }

}
    

 

