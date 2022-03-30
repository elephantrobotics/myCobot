#include "MainControl.h"


typedef struct {
    int joint_angle[6];
} joint_angles_enc;

int data_len_max = 1000;
Angles jae[1000];

int girrep_data[1000];

byte control_pin = 26;   // PIN 26 high -> loop play data from Flash

int rec_data_len = 0;
byte mycobot_mode = 0;

int error_display_time = 3000;
static int EXIT = false;


void MainControl::run(MyCobotBasic &myCobot)
{

    // initialize flash only need init once
    if (!board->InitFlash()) {
        Serial.println("SDCARD Mount Failed");
    }
    distep.y_pos = pos_y;
    distep.rect_pos1 = rect1;
    distep.rect_pos2 = rect2;
    bool flag{false};

    pinMode(control_pin, INPUT);
    myCobot.setLEDRGB(0, 255, 0);
    board->SetRotation(3);
    MainControl::updateMode(myCobot, mycobot_mode);
    MainControl::displayInfo(myCobot, 0);
    distep.MenuChoice();
    while (1) {
        board->BtnUpdate();
        byte btn_pressed = 0;
        if (board->IsBtnClicked(0)) {
            distep.state += 1;
            distep.MenuChoice();
        }
        if (board->IsBtnClicked(1)) {
            distep.state -= 1;
            distep.MenuChoice();
        }
        if (board->IsBtnClicked(2)) {
            Serial.print("distep state = ");
            Serial.println(distep.state);
            Serial.print("mycobot_mode = ");
            Serial.println(mycobot_mode);
            switch (distep.state) {
                case 0: {
                    btn_pressed = 1;
                    MainControl::updateMode(myCobot, btn_pressed);
                }
                break;
                case 1: {
                    btn_pressed = 2;
                    MainControl::updateMode(myCobot, btn_pressed);
                }
                break;
                case 2: {
                    flag = true;
                }
                break;
            defalut:
                break;
            }
            Serial.print("btn_pressed = ");
            Serial.println(btn_pressed);
        }
        if (board->IsBtnClicked(3) || flag) {
            flag = false;
            btn_pressed = 3;
            MainControl::updateMode(myCobot, btn_pressed);
            //distep.MenuChoice();
        }
        if (EXIT || flag) {
            flag = false;
            EXIT = false;
            break;
        }
        MainControl::IO(myCobot);
        delay(200);
    }
}

void MainControl::updateMode(MyCobotBasic &myCobot, byte btn_pressed)
{
    if (mycobot_mode == 0) {
        switch (btn_pressed) {
            case 1:
                mycobot_mode = 1;
                MainControl::displayInfo(myCobot, mycobot_mode);
                break;
            case 2:
                mycobot_mode = 2;
                MainControl::displayInfo(myCobot, mycobot_mode);
                break;
            case 3:
                myCobot.setFreeMove();
                delay(20);
                myCobot.releaseServo(7);
                EXIT = true;
                break;
        }

    } else if (mycobot_mode == 1) {
        switch (btn_pressed) {
            case 1:
                mycobot_mode = 11;
                MainControl::displayInfo(myCobot, mycobot_mode);
                MainControl::play(myCobot); // play loop from ram

                break;
            case 2:
                mycobot_mode = 12;
                MainControl::playFromFlash(myCobot); // play loop from flash

                break;
            case 3:
                mycobot_mode = 0;   // get back
                MainControl::displayInfo(myCobot, mycobot_mode);
                break;
        }

    }

    else if (mycobot_mode == 2) {

        switch (btn_pressed) {
            case 1:
                mycobot_mode = 21;
                MainControl::displayInfo(myCobot, mycobot_mode);
                MainControl::record(myCobot);

                // finish record
                MainControl::displayInfo(myCobot, 33);
                delay(2000);

                // recover to original
                mycobot_mode = 0;
                MainControl::displayInfo(myCobot, mycobot_mode);
                break;

            case 2:
                mycobot_mode = 22;  // record into ram as well
                MainControl::displayInfo(myCobot, mycobot_mode);
                MainControl::recordIntoFlash(myCobot);
                break;
            case 3:
                mycobot_mode = 0;
                MainControl::displayInfo(myCobot, mycobot_mode);
                break;
        }

    }

    else if ((mycobot_mode == 11) || (mycobot_mode == 12)) {
        switch (btn_pressed) {
            case 1:
                Serial.println("Continue Play");

                break;
            case 2:
                Serial.println("Pause");

                break;
            case 3:
                Serial.println("Stop");
                mycobot_mode = 0;
                break;
        }
    }

    else if ((mycobot_mode == 21) || (mycobot_mode == 22)) {
        switch (btn_pressed) {
            case 2:
                Serial.println("Save and Stop");
                break;
            case 3:
                Serial.println("stop record");
                break;

        }

        mycobot_mode = 0;
        MainControl::displayInfo(myCobot, mycobot_mode);
    }

}

void MainControl::displayInfo(MyCobotBasic &myCobot, byte mc_mode)
{
    board->ClearScreen(TFT_BLACK);//黑色填充屏幕
    delay(50);
    board->SetTextSize(2);
    int buttom_y = 190;
    int buttom_1y = 210;
    int buttom_2y = 210;
    distep.DisplayPos(0);

    switch (mc_mode) {
        case 0: {
            Serial.println("main-===");
            board->ClearScreen(0);
            if (lan == 2) {
                string menu[2] = {"播放", "录制"};
                int num[2] = {0, 1};
                distep.MenuInit(num, menu, 2);
                board->DrawString("  MyCobot-拖动示教", 20, 40, 1);
//          board->DrawString("播放", 60, buttom_y, 1);
//          board->DrawString("录制", 160, buttom_y, 1);
//          board->DrawString("退出", 260, buttom_y, 1);
                board->BtnUpdate();
            } else if (lan == 1) {
                board->ClearScreen(TFT_BLACK);//黑色填充屏幕
                board->SetTextColor(TFT_BLACK);
                board->SetTextColor(TFT_RED);
                board->SetTextSize(3);
                board->SetCursor(10, 10);
                board->Printf(TYPE);
                board->SetCursor(10, 40);
                board->DrawFastHLine(0, 70, 320, GREY);
                board->SetTextSize(2);
                board->Println("MainControl Menu");
                string menu[3] = {"Play", "Record", "Exit"};
                int num[3] = {0, 1, 2};
                distep.MenuInit(num, menu, 3);
                board->BtnUpdate();
            }
            distep.Start();
            break;
        }

        case 1: {
            board->ClearScreen(0);
            if (lan == 2) {
                string menu[2] = {"缓存", "储存卡"};
                board->DrawString(" 请选择示教路径的播放位置", 10, 40, 1);
                int num[2] = {0, 1};
                distep.MenuInit(num, menu, 2);
//          board->DrawString("缓存", 60, buttom_y, 1);
//          board->DrawString("储存卡", 160, buttom_y, 1);
//          board->DrawString("返回", 260, buttom_y, 1);
            } else if (lan == 1) {
                board->SetCursor(20, 40);
                board->SetTextColor(TFT_RED);
                board->Print("Playing for Ram/Flash?");
                string menu[3] = {"Ram", "Flash", "Exit"};
                int num[3] = {0, 1, 2};
                distep.MenuInit(num, menu, 3);
//          board->SetCursor(40, buttom_1y);
//          board->Print("Ram");
//          board->SetCursor(136, buttom_1y);
//          board->Print("Flash");
//          board->SetCursor(240, buttom_1y);
//          board->Print("Back");
            }
            distep.Start();
            break;
        }
        case 2: {
            board->ClearScreen(0);
            if (lan == 2) {
                string menu[2] = {"缓存", "储存卡"};
                board->DrawString(" 请选择示教视频储存路径", 20, 40, 1);
                int num[2] = {0, 1};
                distep.MenuInit(num, menu, 2);
//          board->DrawString("缓存", 60, buttom_y, 1);
//          board->DrawString("储存卡", 160, buttom_y, 1);
//          board->DrawString("返回", 260, buttom_y, 1);
            } else if (lan == 1) {
                board->SetCursor(20, 40);
                board->Print("Recording to Ram/Flash?");
                string menu[3] = {"Ram", "Flash", "Exit"};
                int num[3] = {0, 1, 2};
                distep.MenuInit(num, menu, 3);
//          board->SetCursor(40, buttom_1y);
//          board->Print("Ram");
//          board->SetCursor(136, buttom_1y);
//          board->Print("Flash");
//          board->SetCursor(240, buttom_1y);
//          board->Print("Back");
            }
            distep.Start();
            break;
        }
        case 11: {
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString(" 正在执行缓存中的路径", 20, 40, 1);
                board->DrawString(" 播放中...", 20, 70, 1);
//          board->DrawString("开始", 60, buttom_y, 1);
                board->DrawString("暂停", 260/*160*/, buttom_y, 1);
//          board->DrawString("结束", 260, buttom_y, 1);
            } else if (lan == 1) {
                board->SetCursor(20, 40);
                board->SetTextColor(TFT_RED);
                board->Print("Play from Ram\n  Playing...");
//          board->SetCursor(40, buttom_2y);
//          board->Print("Play");
                board->SetCursor(230/*130*/, buttom_2y);
                board->SetTextColor(TFT_WHITE);
                board->Print("Pause");
                board->DrawMainControlPlayStop();
//          board->SetCursor(40/*230*/, buttom_2y);
//          board->Print("Stop");
            }
            break;
        }
        case 12: {
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString(" 正在执行储存卡中的路径", 20, 40, 1);
                board->DrawString(" 播放中...", 20, 70, 1);
//          board->DrawString("开始", 60, buttom_y, 1);
                board->DrawString("暂停", 260, buttom_y, 1);
//          board->DrawString("结束", 260, buttom_y, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->SetTextColor(TFT_RED);
                board->Print(" Play from Flash/nPlaying");
//          board->SetCursor(40, buttom_2y);
//          board->Print("Play");
                board->SetCursor(230, buttom_2y);
                board->SetTextColor(TFT_WHITE);
                board->Print("Pause");
                board->DrawMainControlPlayStop();
//          board->SetCursor(230, buttom_2y);
//          board->Print("Stop");
            }
            break;
        }

        case 21: {
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString(" 录制并存入缓存", 20, 40, 1);
                board->DrawString(" 录制中...", 20, 70, 1);
                board->DrawString(" 停止录制并保存", 5, buttom_y, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("Record into Ram\nRecording...");
                board->SetCursor(5, buttom_1y);
                board->Print("Stop Recording and Save");
            }
            break;
        }
        case 22: {
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString(" 录制并存入储存卡", 20, 40, 1);
                board->DrawString(" 录制中...", 20, 70, 1);
                board->DrawString(" 停止录制并保存", 5, buttom_y, 1);
            }
            if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("Record into Flash\nRecording...");
                board->SetCursor(5, buttom_y);
                board->Print("Stop Recording and Save");
            }

            break;
        }

        case 32: { // Stop recording
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString(" 暂停中", 20, 40, 1);
                board->DrawString("开始", 260, buttom_y, 1);
//        board->DrawString("暂停", 160, buttom_y, 1);
//        board->DrawString("结束", 260, buttom_y, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->SetTextColor(TFT_RED);
                board->Print(" Puase Now");
                board->SetCursor(230, buttom_2y);
                board->SetTextColor(TFT_WHITE);
                board->Print("Play");
                board->DrawMainControlPlayStop();
//        board->SetCursor(130,buttom_2y);
//        board->Print("Pause");
//        board->SetCursor(230,buttom_2y);
//        board->Print("Stop");
            }
            break;
        }

        case 33: { // Stop recording
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString(" 保存录制", 20, 40, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("  Saved Recording");
            }
            break;
        }

        case 41: { // Play from Flash
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString("从储存卡中获取数据", 20, 40, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("Getting data from Flash");
            }
            break;
        }

        case 42: { // Record from Flash
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString("将数据保存到储存卡", 20, 40, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("Saving Data into Flash");
            }
            break;
        }

        case 51: { // loop play from sram
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString("IO口状态", 20, 40, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("IO Pin Active!");
            }
            break;
        }

        case 52: { // loop play from sram
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString("数据不足，无法播放", 20, 40, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("Data too short, not playing");
            }
            break;
        }

        case 53: { // loop play from sram
            board->ClearScreen(0);
            if (lan == 2) {
                board->DrawString("无数据", 20, 40, 1);
            } else if (lan == 1) {
                board->SetCursor(0, 40);
                board->Print("Empty data!");
            }
            break;
        }
        default:
            ;
            break;
    }
}

void MainControl::record(MyCobotBasic &myCobot)  // is stop
{
    myCobot.setLEDRGB(255, 255, 0);
    // record mode : 1- record to ram;  2- record to flash
    rec_data_len = 0;
    Angles _data;
    int _encoder = myCobot.getEncoder(7);
    delay(35);
    for (int data_index = 0; data_index < data_len_max ; data_index ++) {
        board->BtnUpdate();
        for (int i = 0; i < 6; i++) {
            jae[data_index][i] = myCobot.getEncoder(i + 1);
            delay(REC_TIME_DELAY - SEND_DATA_GAP);
//      Serial.print(String(jae[data_index][i]) + ", ");
        }
        if (_encoder > 0) {
            girrep_data[data_index] = myCobot.getEncoder(7);
            delay(REC_TIME_DELAY - SEND_DATA_GAP);
        } else {
            girrep_data[data_index] = 2048;
            delay(20);
        }

        Serial.println(" ");
        rec_data_len++;
        if (board->IsBtnClicked(0) || board->IsBtnClicked(1) || board->IsBtnClicked(2)
                || board->IsBtnClicked(3)) break;
    }

}


void MainControl::play(MyCobotBasic &myCobot)  // is stop  is pause
{
    myCobot.setLEDRGB(0, 255, 0);

    bool is_stop = 0;
    bool is_pause = 0;

    while (1) {
        // Serial.print("123");
        // play once
        for (int index = 0 ; index < rec_data_len; index++) {
            board->BtnUpdate();
            myCobot.setEncoder(7, girrep_data[index]);
            delay(20);
            myCobot.setEncoders(jae[index], 100);
            // check pause button
            if (board->IsBtnClicked(2)) {
                MainControl::displayInfo(myCobot, 32);
                while (1) {
                    board->BtnUpdate();
                    if (board->IsBtnClicked(2)) {
                        MainControl::displayInfo(myCobot, 11);
                        break;
                    }
                    if (board->MainControlBtnStop()) {
                        is_stop = 1;
                        break;
                    }
                }
            }

            // check stop button
            if (board->MainControlBtnStop()) {
                board->BtnUpdate();
                is_stop = 1;
                break;
            }

            // check stop button
            if (is_stop == 1) break;
            delay(WRITE_TIME_GAP * 6);
        }

        // stop button will also end loop
        if (is_stop == 1) {
            break;
        }

        // data too short
        if (rec_data_len < 10) break;

        // quick loop
        if (board->IsBtnClicked(3))break;
    }

    // recover to play page
    board->BtnUpdate();
    mycobot_mode = 1;
    MainControl::displayInfo(myCobot, mycobot_mode);
}

void MainControl::playFromFlash(MyCobotBasic &myCobot)
{
    board->BtnUpdate();
    MainControl::displayInfo(myCobot, 41);

    // initialization first
    /*while(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)){
       Serial.println("SDCARD Mount Failed");
       return;
    }*/

    Serial.printf("Reading file: %s\r\n", FILENAME);
    File file = SD.open(FILENAME, FILE_READ);
    if (!file || file.isDirectory()) {
        Serial.println("- failed to open file for reading");
        return;
    }
    String this_line = "";
    int index = 0;

    int t1 = millis();

    while (file.available()) {
        char this_char = char(file.read());
        this_line += this_char;
        if (this_char == '\n') {
            MyCobotSaver::saver_angles_enc sae_this;
            sae_this = myCobot.saver.processStringIntoInts(this_line);

            for (int jn = 0; jn < 6; jn++) {
                jae[index][jn] = sae_this.joint_angle[jn];
            }
            girrep_data[index] = sae_this.joint_angle[6];
            index ++;
            this_line = "";
        }
        if (index > data_len_max) break;
    }

    // update the len
    rec_data_len = index - 1;
    file.close();//per open file,need close

    // play from flash
    board->BtnUpdate();
    MainControl::displayInfo(myCobot, mycobot_mode);
    MainControl::play(myCobot);
}

void MainControl::recordIntoFlash(MyCobotBasic &myCobot)
{
    // recording data
    MainControl::record(myCobot);
    board->BtnUpdate();
    // show saving to recording
    MainControl::displayInfo(myCobot, 33);

    // initialize flash
    /*while(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)){
       Serial.println("SDCARD Mount Failed");
       return;
    }*/

    // list exisiting files
    myCobot.saver.listDir(SD, "/", 0);

    // clean exsiting file
    myCobot.saver.writeFile(SD, FILENAME, " ");

    // check time
    File file = SD.open(FILENAME, FILE_APPEND);

    for (int data_index = 0; data_index < rec_data_len; data_index ++) {
        String data_output = "";
        for (int l = 0; l < 6 ; l ++) {
            data_output +=  jae[data_index][l];
            data_output += ",";
            Serial.print("data ==");
            Serial.println(data_output);
        }
        data_output += girrep_data[data_index];
        data_output += "\n";
        file.print(data_output);
        Serial.print("data222 =====    ");
        Serial.println(data_output);
    }
    file.close();//per open file,need close
    // recover to original
    mycobot_mode = 0;
    MainControl::displayInfo(myCobot, mycobot_mode);
}

void MainControl::IO(MyCobotBasic &myCobot)
{
    int pin_data = digitalRead(control_pin);

    return;
    if (pin_data == 1) {
        MainControl::displayInfo(myCobot, 51);
        delay(error_display_time);

        mycobot_mode = 12;
        MainControl::play(myCobot);
    }

}



/*
bool MainControl::checkDataLen(MyCobotBasic &myCobot)
{

  if (rec_data_len == 0){
    MainControl::displayInfo(myCobot, 53);
    delay(error_display_time);
    return 0;
  }

  if (rec_data_len < 10){
    MainControl::displayInfo(myCobot, 52);
    delay(error_display_time);
    return 0;
  }
  return 1;
}
*/
