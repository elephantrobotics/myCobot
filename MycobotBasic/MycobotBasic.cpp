#include "MycobotBasic.h"

MycobotBasic::MycobotBasic()
{

}    

void MycobotBasic::setup()
{
    delay(500);
    M5.begin(true, false, true);
    M5.Power.begin();

    dacWrite(25,0);   // disable mic 

    Serial2.begin(BAUD_RATE);
    delay(500);
}




bool MycobotBasic::checkHeader()
{
  byte bDat;
  byte bBuf[2] = {0,0};
  byte Cnt = 0;

  while(1){
    if(!readSerial(&bDat, 1))
    {
      return 0;      
      }
    bBuf[1] = bBuf[0];
    bBuf[0] = bDat;

    //Serial.println(bBuf[1] );

    if(bBuf[0]==header && bBuf[1]==header){
      break;
    }
    Cnt++;
    if(Cnt>30)
    {
      return 0;
    }
  }
   return 1;
}


int MycobotBasic::readSerial(unsigned char *nDat, int nLen)
{
  int Size = 0;
  int rec_data;
  unsigned long t_begin = millis();
  unsigned long t_use;

  while(1){
    rec_data = Serial2.read();
    // check data validation
    if (rec_data != IORecWrong){ 
      if(nDat){
        nDat[Size] = rec_data;
      }
      Size ++;
      t_begin = millis();
    }
    // check len
    if(Size>=nLen){ 
      break;
    }
    // check time out
    t_use = millis() - t_begin;
    if (t_use > IOTimeOut){ 
      break;
    }
  }
  return Size;
  
}

void MycobotBasic::setAngle(byte servo_no, int angle , int sp)
{
    if (angle >180) angle = 180;
    if (angle < -180) angle = - 180;
    int servo_encoder_value = int(angle*angle_to_encoder) + encoder_cal_point;
    setServoEncoder(servo_no, servo_encoder_value , sp);
}


void MycobotBasic::setServoEncoder(byte servo_no, int servo_encoder, int servo_sp)
{
    byte angle_low = lowByte(servo_encoder);
    byte angle_high = highByte(servo_encoder);

    byte speed_low = lowByte(servo_sp);
    byte speed_high = highByte(servo_sp);
    
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x07);
    Serial2.write(SET_SERVO_ANGLE);

    Serial2.write(servo_no);        // data1
    Serial2.write(angle_low);       // data2
    Serial2.write(angle_high);      // data3
    Serial2.write(speed_low);       // data4
    Serial2.write(speed_high);      // data5

    Serial2.write(footer);
    delay(WRITE_TIME_GAP);
}




void MycobotBasic::setServoData(byte servo_no,byte servo_state, byte servo_data)
{
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x05);    // data len
    Serial2.write(SET_SERVO_DATA);      // 40 enable torque
    
    Serial2.write(servo_no);
    Serial2.write(servo_state);
    Serial2.write(servo_data);
    Serial2.write(footer);
}


void MycobotBasic::calibrateServo(byte servo_no)
{
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x03);
    Serial2.write(SET_CALIBRATAION);
    Serial2.write(servo_no);
    Serial2.write(footer);
}



int MycobotBasic::getAngleEncoder(byte joint_no)
{
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x03);
    Serial2.write(GET_ANGLE_ENCODER);
    Serial2.write(joint_no);
    Serial2.write(footer);

    rFlushSerial();

    if(!checkHeader())
    {
        return -1;
    }
    else
      {
        byte data_len[3];
        readSerial(data_len, 3);
        if(data_len[2]!= footer) {
            return -1;
        }
        int encoder_data = data_len[0] + data_len[1]*256;
        return encoder_data;
      }
      return -1;
}


double MycobotBasic::getAngle(byte joint_no)
{
    int encode_data = getAngleEncoder(joint_no);
    itr_time = 0;

    while(encode_data == -1)
    {
        encode_data = getAngleEncoder(joint_no);
        itr_time ++;
        delay(6);
        if (itr_time> ITR_TIMES_MAX) break;
    } 

    if (encode_data == -1) return error_angle;

    double angle = (encode_data - encoder_cal_point) / angle_to_encoder;


    return angle;
}


void MycobotBasic::setRGB(byte R, byte G, byte B)
{
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x05);
    Serial2.write(SET_RGB);
    Serial2.write(R);
    Serial2.write(G);
    Serial2.write(B);
    Serial2.write(footer);
}


void MycobotBasic::setColor(byte color)
{
    switch (color)
    {
        case 0: // red
            setRGB(255,0,0);
            break;
        case 1: // green
            setRGB(0,255,0);
            break;
        case 2: // blue
            setRGB(0,0,255);
            break;
        case 3: // yellow
            setRGB(255,255,0);
            break;
        case 4: // grey
            setRGB(128,128,128);
            break;

    }

}

void MycobotBasic::releaseAllServos()
{
  for (int i = 1; i < 7; i ++)
  {
    // relase all servos
    setServoData(i, 40 , 0);
    delay(10);
  }
}

void MycobotBasic::setAtomPinMode(byte pin, byte mode)
{
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x04);
    Serial2.write(SET_ATOM_PIN_MODE);
    Serial2.write(pin);
    Serial2.write(mode);
    Serial2.write(footer);
}


void MycobotBasic::setAtomDigitalWrite(byte pin, byte data)
{
    Serial2.write(header);
    Serial2.write(header);
    Serial2.write(0x04);
    Serial2.write(SET_ATOM_DIGITAL);
    Serial2.write(pin);
    Serial2.write(data);
    Serial2.write(footer);

}


void MycobotBasic::rFlushSerial(){
    while( Serial2.read() !=-1);
}