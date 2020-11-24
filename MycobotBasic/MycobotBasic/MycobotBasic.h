#ifndef mycobotatom_h
#define mycobotatom_h

#include <Arduino.h>
#include <M5Stack.h>
#include <MycobotSaver.h>

#define BAUD_RATE 			1000000
#define IORecWrong			-1
#define	header				0xfa
#define footer				0xfe
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

#define GET_ANGLE_ENCODER	0x11
#define SET_SERVO_ANGLE		0x20
#define SET_SERVO_DATA		0x24
#define SET_CALIBRATAION	0x25
#define SET_ATOM_PIN_MODE	0x30
#define SET_ATOM_DIGITAL	0X31
#define SET_RGB				0x33


class MycobotBasic
{
public:

	MycobotBasic();

	MycobotSaver saver;

	void setup();

	// set data 
	void setServoEncoder(byte servo_no, int servo_encoder, int servo_sp);
	void setAngle(byte servo_no, int angle , int sp);
	void setServosEncoder(int servo_encoder_1, int servo_encoder_2, int servo_encoder_3, int servo_encoder_4, int servo_encoder_5, int servo_encoder_6, int servo_sp );
	void calibrateServo(byte servo_no);
	void setServoData(byte servo_no,byte servo_state, byte servo_data);
	void releaseAllServos();

	// get data
	int getAngleEncoder(byte joint_no);
	double getAngle(byte joint_no);

	// led
	void setRGB(byte R, byte G, byte B);
	void setColor(byte color);

	// atom pin mode changes
	void setAtomPinMode(byte pin, byte mode);
	void setAtomDigitalWrite(byte pin, byte data);

private:
	
	// communication
	bool checkHeader();
	int readSerial(unsigned char *nDat, int nLen);

	void rFlushSerial();
	byte itr_time = 0;
	
};


#endif