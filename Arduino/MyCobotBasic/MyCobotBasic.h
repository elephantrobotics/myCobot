#ifndef mycobotatom_h
#define mycobotatom_h

#include <Arduino.h>
#include <CommunicateDefine.h>
//#include <string>
#include <MyCobotSaver.h>

//默认mycobot，用哪一款机械臂，就打开注释，
#define MyCobot "mycobot"
//#define MyCobot_Pro "mycobot pro"
//#define MyCobot_Pro_350

// #define AYSN_COMMUNICATE  //new 280 320should comment

#if defined MyCobot
#if defined AYSN_COMMUNICATE
#define SYSTEM_VERSION 11
#else 
#define SYSTEM_VERSION 21
#endif
#else 
    #define SYSTEM_VERSION 21
#endif

#ifdef MyCobot
#define BAUD_RATE           1000000      //mycobot use
#else
#define BAUD_RATE            115200      //mycobot-pro use
#endif

//#define BAUD_RATE           1000000      //mycobot use
// #define BAUD_RATE            115200      //mycobot-pro use
#define IORecWrong          -1
#define header              0xfe
#define footer              0xfa
#define IO_TimeOut          70  //Synchronous reads, which take longer to access when a joint is faulty, but do not affect normal speed(30ms) 
#define ITR_TIMES_MAX       4

#define SEND_DATA_GAP       4
#define WRITE_SERVO_GAP     20
#define WRITE_TIME_GAP      20      // every 8 ms to play one data
#define WRITE_SIGLE_SERVO_GAP 50
#define REC_TIME_DELAY      20      // every 20 ms to store one dat

#define error_angle         -1000

#define angle_to_encoder    11.3777777
#define encoder_cal_point   2048
using namespace myCobotDefine;
using namespace roboticMessages;

class MyCobotBasic
{
public:
#if defined MyCobot_M5
    MyCobotSaver saver;
#endif

    MyCobotBasic();
    void setup();//Enable m5 development version, not applicable to other development boards

    // Overall Status
    void powerOn();  //All motors powered up
    void powerOff();  //Power down all motors
    bool isPoweredOn();  //Returns whether the motor is powered on or powered off
    int getAtomVersion();  //Get Atom firmware version


    // MDI mode and operation
    Angles getAngles();  //Get all joint angles
    void writeAngle(int joint, float value, int speed);  //send individual angles
    void writeAngles(Angles angles, int speed);  //Send all joint angles
    Coords getCoords();  //get all coordinates
    void writeCoord(Axis axis, float value, int speed);  //Send individual coordinates
    void writeCoords(Coords coords, int speed);  //send all coordinates
    void moveCCoords(Coords begin_coord, Coords middle_coord,
                     Coords end_coord);  //Pass in the center of the circle and start drawing the circle from the current point
    void moveCCoords(Coords middle_coord,
                     Coords end_coord);  //Pass in point and radius, draw a circle with current point and incoming point and radius
    //int isInPosition(Coords coord, bool is_linear);
    bool checkRunning();  //Check if moving

    // JOG mode and operation
    void jogAngle(int joint, int direction,
                  int speed);  //Joint control, a joint moves in a certain direction until the robotic arm stops moving or reaches the limit
    void jogCoord(Axis axis, int direction, int speed);  //Coordinate control
    void jogStop();  //JOg stop

    //Encoder mode and operation
    void setEncoder(int joint, int encoder);  //Send individual potential values
    int getEncoder(int joint);  //Get individual potential values
    void setEncoders(Angles angleEncoders, int speed);  //Send all potential values
    Angles getEncoders();  //Get all potential values
    Angles getServoSpeeds();  //get all servo speed
    void setEncodersDrag(Angles angleEncoders, Angles speeds);
#ifdef MyCobot_Pro_350
    Angles getServoCurrents();  //get all currents only 320 have
#endif
    Angles getServoVoltages();  //get all servo voltages
    Angles getServoStatus();    //get all servo status
    Angles getServoTemps();    //get all servo temps
    void setPid(Angles pids); //set pid,control robot move speed
    Angles getPid();   //get pid,beause now type problem,angles 1-6-->p i d p i d 


    // Running Status and Settings
    int getSpeed();  //read current speed4
    void setSpeed(int percentage);  //set speed
    float getJointMin(int joint);  //Read the joint minimum angle
    float getJointMax(int joint);  //Read the joint maximum angle
    //void setJointMin(int joint, float angle);
    //void setJointMax(int joint, float angle);
    //float getFeedOverride();
    //void sendFeedOverride(float feed_override);
    //float getAcceleration();
    //void setAcceleration(float acceleration);



    // Servo Control
    bool isServoEnabled(int joint);  //Check whether a single motor is powered on
    bool isAllServoEnabled();  //Check whether all motors are powered on

    byte getServoData(int joint, byte data_id);  //Get the status of a single servo
    void setServoCalibration(int joint);  //Set a single servo zero point
    //void jointBrake(int joint);



    // Atom IO
    void setPinMode(byte pin_no,
                    byte pin_mode);  //Set pin mode to input/output
    void setDigitalOutput(byte pin_no,
                          byte pin_state);  //set io state (high/low level)
    int getDigitalInput(byte pin_no);  //get io status

    void setPWMOutput(byte pin_no,  int freq, byte pin_write);  //Set PWM output
    //void setPWMMode(int freq, byte pin_no, byte channel);

    void releaseServo(byte servo_no);  //Power down of a single motor
    void focusServo(byte servo_no);  //Power up a single motor

    void setGripperState(byte mode,
                         int sp);  //Set gripper mode Parameter 1: 1-On 0-Off Parameter 2: Speed (0-100)
    void setGripperValue(int data,
                         int sp);  //Set gripper jaw angle Parameter 1: Angle Parameter 2: Speed
    void setGripperIni();  //Gripper setting 0 point
    int getGripperValue();  //Get gripper angle
    bool isGripperMoving();  //Detect if the gripper is moving

    // function
    void ProgramPause();  //program pause
    void ProgramResume();  //Program recovery
    void TaskStop();  //program stops

    void setServoData(byte servo_no, byte servo_state,
                      byte servo_data);  //Set servo status
    void setFreeMove();  //set to move freely

    void setLEDRGB(byte r, byte g, byte b);  //Set RGB color
    //void setGripper(int data);


    //void receiveMessages();  //receive message
    void setMovementType(MovementType
                         movement_type);  //Set the move type, parameter 1: move type (1-movel, 0-moveJ)
    MovementType getMovementType();

    void setToolReference(Coords coords);  //Set tool coordinate system
    void setWorldReference(Coords coords);  //Set the world coordinate system
    Coords getToolReference();  //Get tool coordinate system
    Coords getWorldReference();  //Get the world coordinate system
    void setReferenceFrame(RFType
                           rftype);  //Set the base coordinate system Parameter 1: 0-base 1-world (RFType::BASE takes the robot base as the base coordinate, RFType::WORLD takes the world coordinate system as the base coordinate)
    RFType getReferenceFrame();  //Get the base coordinate system

    void setEndType(EndType
                    end_type);  //Set the end coordinate system, parameter 1: 0-flange 1-tool (EndType::FLANGE is to set the end as the flange, EndType::TOOL is to set the end as the tool end)
    EndType getEndType();  //Get end coordinate system



private:
    // communication
    int readSerial(unsigned char *nDat, int &nLen);  //Read serial messages
template<typename T, typename O, typename R, typename E, typename M>
    int readData(T& pData, O& bData, R& rData, E& eData, M& mData);  //retrieve data
    void rFlushSerial();  //Clear serial port cache
    void DivideSerialData(unsigned char *rec_data, unsigned char *nDat, int nLen);

private:
    byte itr_time = 0;
    Angles error_angles;
    Angles error_speeds;
    Coords error_coords;
    Angles error_encoders;

    //std::map<int, std::string> messages_map;
    int invalid = 0;
    RFType r_invalid;
    EndType e_invalid;
    MovementType m_invalid;
    Angles a_invalid;
};

#endif