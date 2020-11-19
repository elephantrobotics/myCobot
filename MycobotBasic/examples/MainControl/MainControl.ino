#include <MycobotBasic.h>

MycobotBasic myCobot;

typedef struct{
  int joint_angle[6];
} joint_angles_enc;

int data_len_max = 1000;
joint_angles_enc jae[1000];

byte control_pin = 1;   // PIN 1 high -> loop play data from Flash

int rec_data_len = 0;
byte mycobot_mode = 0; 

int error_display_time = 3000;

void setup() {
  myCobot.setup();
  M5.Lcd.setTextSize(3);
  Serial.begin(9600);

  pinMode(control_pin, INPUT);

  updateMode(mycobot_mode);
}

void loop() {
   M5.update(); 
   byte btn_pressed = 0;

   myCobot.setRGB(0,255,0);

   if (M5.BtnA.wasPressed()) {
        btn_pressed = 1;
        updateMode(btn_pressed);
      } 
   if(M5.BtnB.wasPressed()){
      btn_pressed = 2;
      updateMode(btn_pressed);
     }
   if (M5.BtnC.wasPressed()) {
        btn_pressed = 3;
        updateMode(btn_pressed);
      }
   checkIO();
   
}


void updateMode(byte btn_pressed)
{
  if (mycobot_mode == 0)
  {
    switch (btn_pressed)
    {
      case 1:
        mycobot_mode = 1;
        break;
      case 2:
        myCobot.releaseAllServos();
        mycobot_mode = 0;
        break;
      case 3:
        mycobot_mode = 2;
        break;
    }
    displayInfo(mycobot_mode);
  }
  else if(mycobot_mode == 1)
  {
    
    
     switch (btn_pressed)
    {
      case 1:
        mycobot_mode = 11;
        displayInfo(mycobot_mode);
        play(); // play loop from ram
        break;
      case 2:
        mycobot_mode = 12;
        play(); // play loop from flash
        break;
      case 3:
        mycobot_mode = 0;   // get back
        displayInfo(mycobot_mode);
        break;
    }
    
  }

  else if(mycobot_mode == 2)
  {
    
    switch (btn_pressed)
    {
      case 1:
        mycobot_mode = 21;
        displayInfo(mycobot_mode);
        record();
        break;
      case 2:
        mycobot_mode = 22;
        displayInfo(mycobot_mode);
        record();
        break;
      case 3:
        mycobot_mode = 0;
        displayInfo(mycobot_mode);
        break;
    }
    
  }

  else if((mycobot_mode == 11)||(mycobot_mode == 12))
  {
     switch (btn_pressed)
    {
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

  else if((mycobot_mode == 21)||(mycobot_mode == 22))
  {
    switch (btn_pressed)
    {
      case 2:
        Serial.println("Save and Stop");
        break;
      case 3:
        Serial.println("stop record");
        break;
      
    }
     
    mycobot_mode = 0;
    displayInfo(mycobot_mode);
  }
  
}

void displayInfo(byte mc_mode)
{
  M5.Lcd.clear(BLACK);
  delay(50);

  int buttom_2y = 190;
  int buttom_y = 210;

  switch (mc_mode){
    case 0:
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(20,40);
      M5.Lcd.print("MyCobot - Menu");   
      
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(40,buttom_y);
      M5.Lcd.print("Play");

      M5.Lcd.setCursor(130,buttom_y);
      M5.Lcd.print("Relase");

      M5.Lcd.setCursor(232,buttom_y);
      M5.Lcd.print("Record");
      break;
    }
    
    case 1:
    {

       M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(20,40);
      M5.Lcd.print("Infinite Playing Mode");   
      
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(30,buttom_2y);
      M5.Lcd.print("Play");
      M5.Lcd.setCursor(30,buttom_y);
      M5.Lcd.print("Ram");

      M5.Lcd.setCursor(136,buttom_2y);
      M5.Lcd.print("Play");
      M5.Lcd.setCursor(136,buttom_y);
      M5.Lcd.print("Flash");

      M5.Lcd.setCursor(232,buttom_y);
      M5.Lcd.print("Back");

      break;
    
    }
    case 2:
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(20,40);
      M5.Lcd.print("Recording Mode"); 
      
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(30,buttom_2y);
      M5.Lcd.print("Record");
      M5.Lcd.setCursor(30,buttom_y);
      M5.Lcd.print("Ram");

      M5.Lcd.setCursor(136,buttom_2y);
      M5.Lcd.print("Record");
      M5.Lcd.setCursor(136,buttom_y);
      M5.Lcd.print("Flash");

      M5.Lcd.setCursor(240,buttom_y);
      M5.Lcd.print("Back");
      break;
    }
   
    case 11:
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Play from Ram\nPlaying...");

      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(40,buttom_y);
      M5.Lcd.print("Play");

      M5.Lcd.setCursor(130,buttom_y);
      M5.Lcd.print("Pause");

      M5.Lcd.setCursor(230,buttom_y);
      M5.Lcd.print("Stop");
      break;
    }
    case 12:
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Play from Flash/nPlaying"); 
      
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(40,buttom_y);
      M5.Lcd.print("Play");

      M5.Lcd.setCursor(130,buttom_y);
      M5.Lcd.print("Pause");

      M5.Lcd.setCursor(230,buttom_y);
      M5.Lcd.print("Stop");
      break;
    }
    
    case 21:
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Record into Ram\nRecording..."); 

      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(5,buttom_y);
      M5.Lcd.print("Stop Recording and Save");

      break;
    }
    case 22:
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Record into Flash\nRecording..."); 

      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(5,buttom_y);
      M5.Lcd.print("Stop Recording and Save");

      break;
    }
    
    case 32: // Stop recording
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Puase Now"); 

      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(40,buttom_y);
      M5.Lcd.print("Play");

      M5.Lcd.setCursor(130,buttom_y);
      M5.Lcd.print("Pause");

      M5.Lcd.setCursor(230,buttom_y);
      M5.Lcd.print("Stop");

      break;
    }

    case 33: // Stop recording
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Saved Recording"); 
      break;
    }

    case 41: // Play from Flash
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Getting data from Flash"); 
      break;
    }

    case 42: // Record from Flash
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Saving Data into Flash"); 
      break;
    }

    case 51: // loop play from sram
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("IO Pin Active!");
      break; 
    }

    case 52: // loop play from sram
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Data too short, not playing");
      break; 
    }

    case 53: // loop play from sram
    {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0,40);
      M5.Lcd.print("Empty data!");
      break; 
    }

  }
  
}

void record()  // is stop
{
  myCobot.setRGB(255,255,0);

  // record mode : 1- record to ram;  2- record to flash
  rec_data_len = 0;

  for (int data_index = 0; data_index <data_len_max ; data_index ++)
  {
    M5.update(); 

    for (int i = 0 ; i < 6; i ++)
    {
      jae[data_index].joint_angle[i] = myCobot.getAngleEncoder(i+1);
    }

    delay(REC_TIME_DELAY - SEND_DATA_GAP);

    rec_data_len++;

    if (M5.BtnA.wasPressed()||M5.BtnB.wasPressed()||M5.BtnC.wasPressed()) break;
  }

   if (mycobot_mode == 22)  // record into flash
  {
    M5.update(); 
    displayInfo(42);
  }
  
  displayInfo(33);
  delay(1000);
  
  mycobot_mode = 0;
  displayInfo(mycobot_mode);
}

void play()  // is stop  is pause
{
  myCobot.setRGB(0,255,0);
 
  bool is_stop = 0;
  bool is_pause = 0;

  if (mycobot_mode == 12)
  {
    M5.update(); 
    displayInfo(41);
    loadFromFlash();
    
    M5.update(); 
    displayInfo(mycobot_mode);
  }
  
  while(1)
  {
    if(checkDataLen()) break;

    // play once
    for (int index = 0 ; index < rec_data_len; index++)
    {
      M5.update(); 

      // set data from jae
      for (int i = 0 ; i < 6; i ++)
      {
        int sp = 4000;
        int a_data = jae[index].joint_angle[i];
  
        if (a_data != -1)
        {
          myCobot.setServoEncoder(i+1,a_data , sp );
        }
      }

      // check pause button
      if (M5.BtnB.wasPressed())
      {
        displayInfo(32);
        while(1)
        {
          M5.update(); 
          if (M5.BtnA.wasPressed())
          {
            displayInfo(11);
            break;
          }
          if (M5.BtnC.wasPressed()) 
          {
            is_stop = 1;
            break;
          }
        }
      }

      // check stop button
      if (M5.BtnC.wasPressed())
      {
        M5.update(); 
        is_stop = 1;
        break;
      }

      // check stop button
      if(is_stop == 1) break;
      delay(WRITE_TIME_GAP); 
    }

    // stop button will also end loop
    if(is_stop == 1){
      break;
    }
  }

  mycobot_mode = 1;
  displayInfo(mycobot_mode);
}


void loadFromFlash()
{
    Serial.printf("Reading file: %s\r\n", FILENAME);
    File file = SPIFFS.open(FILENAME);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    String this_line = "";
    int index = 0;

    int t1= millis();
    
    while(file.available()){
      char this_char = char(file.read());
      this_line += this_char;
      if (this_char == '\n')
      {
        MycobotSaver::saver_angles_enc sae_this;
        sae_this = myCobot.saver.processStringIntoInts(this_line);

        for(int jn = 0; jn<6; jn++)
        {
          jae[index].joint_angle[jn] = sae_this.joint_angle[jn];
        }
        index ++;
        this_line = "";
      }
    }
    
    // update the 
    rec_data_len = index - 1;

    Serial.print("Load data spend ");
    Serial.print(millis()- t1);
    Serial.println(" ms");

    
  
}

void recordIntoFlash()
{
    // rec_data_len

    Serial.println("Start to save data into Flash");
    
    // clean exsiting file
    myCobot.saver.writeFile(SPIFFS, FILENAME, "");

    // check time
    int t1= millis();
    File file = SPIFFS.open(FILENAME, FILE_APPEND);
    for (int data_index = 0; data_index < rec_data_len; data_index ++)
    {
      String data_output = "";
      for (int l = 0; l < 6; l ++)
      {
        data_output +=  jae[data_index].joint_angle[l];
        data_output += ",";
      }
      data_output += "\n";
      file.print(data_output);
    }
    
    Serial.print("Save data spend ");
    Serial.print(millis()- t1);
    Serial.println(" ms");

}

void checkIO()
{
  bool pin_data = digitalRead(control_pin);
  
  displayInfo(51);
  delay(error_display_time);
   
  if (pin_data)
  {
    mycobot_mode = 12;
    play();
  }
  
}

bool checkDataLen()
{
  if (rec_data_len == 0){
    displayInfo(53);
    delay(error_display_time);
    return 0;
  }
  
  if (rec_data_len < 10){
    displayInfo(52);
    delay(error_display_time);
    return 0;
  }
  return 1;
}
