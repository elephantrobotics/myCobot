#ifndef _MyPalletizerBASIC_H_
#define _MyPalletizerBASIC_H_

#include <Arduino.h>
#include <MyPalletizerCommunicateDefine.h>
//#include <string>
#include <MyCobotSaver.h>

//set
#define BAUD_RATE             1000000      //mycobot use
//#define BAUD_RATE             115200      //mycobot-pro use
#define IORecWrong            -1
#define    header                0xfe
#define footer                0xfa
#define IO_TimeOut            120
#define ITR_TIMES_MAX        4

#define SEND_DATA_GAP         4
#define WRITE_SERVO_GAP        20
#define WRITE_TIME_GAP        20        // every 8 ms to play one data
#define WRITE_SIGLE_SERVO_GAP 50
#define REC_TIME_DELAY        20        // every 20 ms to store one dat

#define error_angle         -1000

#define angle_to_encoder    11.3777777
#define encoder_cal_point     2048

using namespace myCobotDefine;
using namespace roboticMessages;

class MyPalletizerBasic
{
public:
#if defined MyCobot_M5
    MyCobotSaver saver;
#endif
    //MyPalletizerBasic(){}
    MyPalletizerBasic(/*HardwareSerial *hw_serial*/);
    void setup();

    // Overall Status
    void powerOn();
    void powerOff();
    bool isPoweredOn();
    int getAtomVersion();


    // MDI mode and operation
    MyPalletizerAngles getAngles();
    void writeAngle(int joint, float value, int speed);
    void writeAngles(MyPalletizerAngles angles, int speed);
    MyPalletizerCoords getCoords();
    void writeCoord(MyPalletizerAxis axis, float value, int speed);
    void writeCoords(MyPalletizerCoords coords, int speed);
    int isInPosition(MyPalletizerCoords coord, bool is_linear);
    bool checkRunning();
    void moveCCoords(MyPalletizerCoords center_coord, int direction, int speed);
    void moveCCoords(MyPalletizerCoords end_coord, int radius, int direction,
                     int speed);
    void moveLCoords(MyPalletizerCoords end_coord, int speed);



    // JOG mode and operation
    void jogAngle(int joint, int direction, int speed);
    void jogCoord(MyPalletizerAxis axis, int direction, int speed);
    void jogStop();

    //Encoder mode and operation
    void setEncoder(int joint, int encoder);
    int getEncoder(int joint);
    void setEncoders(MyPalletizerEncoders angleEncoders, int speed);
    MyPalletizerAngles getEncoders();



    // Running Status and Settings
    int getSpeed();
    void setSpeed(int percentage);
    float getFeedOverride();
    void sendFeedOverride(float feed_override);
    float getAcceleration();
    void setAcceleration(float acceleration);
    float getJointMin(int joint);
    float getJointMax(int joint);
    void setJointMin(int joint, float angle);
    void setJointMax(int joint, float angle);



    // Servo Control
    bool isServoEnabled(int joint);
    bool isAllServoEnabled();

    byte getServoData(int joint, byte data_id);
    void setServoCalibration(int joint);
    void jointBrake(int joint);



    // Atom IO
    void setPinMode(byte pin_no, byte pin_mode);
    void setDigitalOutput(byte pin_no, byte pin_state);
    int getDigitalInput(byte pin_no);

    //void setPWMMode(int freq, byte pin_no, byte channel);
    void setPWMOutput(byte pin_no,  int freq, byte pin_write);

    void releaseServo(byte servo_no);
    void focusServo(byte servo_no);

    void setGripperState(byte mode, int sp);
    void setGripperValue(int data, int sp);
    void setGripperIni();
    int getGripperValue();
    bool isGripperMoving();



    // function
    void pause();
    void resume();
    void stop();

    void setServoData(byte servo_no, byte servo_state, byte servo_data);
    void setFreeMove();

    void setLEDRGB(byte r, byte g, byte b);
    void setGripper(int data);


    //void receiveMessages();
    void setMovementType(MovementType movement_type);
    MovementType getMovementType();

    void setToolReference(MyPalletizerCoords coords);
    void setWorldReference(MyPalletizerCoords coords);
    MyPalletizerCoords getToolReference();
    MyPalletizerCoords getWorldReference();
    void setReferenceFrame(RFType rftype);
    RFType getReferenceFrame();

    void setEndType(EndType end_type);
    EndType getEndType();

private:

    // communication
    bool checkHeader();
    int readSerial(unsigned char *nDat, int nLen);


    void *readData();

    void rFlushSerial();
    byte itr_time = 0;

    MyPalletizerAngles error_angles;
    MyPalletizerCoords error_coords;
    MyPalletizerEncoders error_encoders;
    HardwareSerial *hw_serial;

    //std::map<int, std::string> messages_map;
};

#endif