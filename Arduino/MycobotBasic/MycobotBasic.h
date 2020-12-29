#ifndef mycobotatom_h
#define mycobotatom_h

#include <Arduino.h>
#include <M5Stack.h>
#include <MycobotSaver.h>
#include <ParameterList.h>
#include <CommunicateDefine.h>

#define BAUD_RATE 			1000000
#define IORecWrong			-1
#define	header				0xfe
#define footer				0xfa
#define IOTimeOut			30
#define ITR_TIMES_MAX		4

#define SEND_DATA_GAP 		4
#define WRITE_SERVO_GAP		20
#define WRITE_TIME_GAP		20		// every 8 ms to play one data
#define WRITE_SIGLE_SERVO_GAP 50
#define REC_TIME_DELAY		20		// every 20 ms to store one dat

#define error_angle 		-1000

#define angle_to_encoder	11.3777777
#define encoder_cal_point 	2048


using namespace myCobotDefine;

class MycobotBasic
{
public:

	MycobotBasic();

	MycobotSaver saver;

	void setup();

	// Overall Status
	void powerOn();
	void powerOff();
	bool isPoweredOn();


	// MDI mode and operation
	Angles GetAngles();
	void WriteAngle(int joint, float value, int speed);
	void WriteAngles(Angles angles, int speed);
	Coords GetCoords();
	void WriteCoord(Axis axis, float value, int speed);
	void WriteCoords(Coords coords, int speed);
	int isInPosition(Coords coord, bool is_linear);
	bool CheckRunning();




	// JOG mode and operation
	void JogAngle(int joint, int direction, int speed);
	void JogCoord(Axis axis, int direction, int speed);
	void JogStop();
	void SetEncoder(int joint, int encoder);
	int GetEncoder(int joint);
	void SetEncoders(Angles angleEncoders, int speed);



	// Running Status and Settings
	int GetSpeed();
	void SetSpeed(int percentage);
	float GetFeedOverride();
	void SendFeedOverride(float feedOverride);
	float GetAcceleration();
	void SetAcceleration(float acceleration);
	float getJointMin(int joint);
	float getJointMax(int joint);
	void setJointMin(int joint, float angle);
	void setJointMax(int joint, float angle);



	// Servo Control
	bool isServoEnabled(int joint);
	bool isAllServoEnabled();

	byte getServoData(int joint, byte data_id);
	void setServoCalibration(int joint);
	void JointBrake(int joint);



	// Atom IO
	void setPinMode(byte pin_no, byte pin_mode);


	

	// function
	void pause();
	void resume();
	void stop();

	void setServoData(byte servo_no, byte servo_state, byte servo_data);
	void setFreeMove();

	void setLEDRGB(byte r, byte g, byte b);
	void setGripper(int data);



private:
	
	// communication
	bool checkHeader();
	int readSerial(unsigned char *nDat, int nLen);


	void* readData();

	void rFlushSerial();
	byte itr_time = 0;
	
	Angles errorAngles;
	Coords errorCoords;
};


#endif