#ifndef COMMUNICATEDEFINE_H
#define COMMUNICATEDEFINE_H

// System Infor
#define GET_ROBOT_VERSION			0X01
#define GET_ROBOT_VERSION_LEN		2
#define GET_ROBOT_VERSION_RETURN_LEN	3

#define GET_SYSTEM_VERSION			0X02
#define GET_SYSTEM_VERSION_LEN		2
#define GET_SYSTEM_VERSION_RETURN_LEN	3

#define GET_ROBOT_ID				0X03
#define GET_ROBOT_ID_LEN			2
#define GET_ROBOT_ID_RETURN_LEN		3

#define SET_ROBOT_ID				0X04
#define SET_ROBOT_ID_LEN			0


// Overall Status
#define POWER_ON					0x10
#define POWER_ON_LEN				2

#define POWER_OFF					0x11
#define POWER_OFF_LEN				2

#define IS_POWERED_ON				0x12
#define IS_POWERED_ON_LEN			2
#define IS_POWERED_ON_RETURN_LEN	3

#define SET_FREE_MOVE				0x13
#define SET_FREE_MOVE_LEN			2

#define IS_CONTROLLER_CONNECTED		0x14
#define IS_CONTROLLER_CONNECTED_LEN	2
#define IS_CONTROLLER_CONNECTED_RETURN_LEN	3

#define READ_NEXT_ERROR				0x15
//#define READ_NEXT_ERROR_LEN			






// MDI mode and operation
#define GET_ANGLES					0x20
#define GET_ANGLES_LEN				2
#define GET_ANGLES_RETURN_LEN		14

#define WRITE_ANGLE					0x21
#define WRITE_ANGLE_LEN				6

#define WRITE_ANGLES				0x22
#define WRITE_ANDLES_LEN			15

#define GET_COORDS					0x23
#define GET_COORDS_LEN				2
#define GET_COORDS_RETURN_LEN		14

#define WRITE_COORD					0x24
#define WRITE_COORD_LEN				6

#define WRITE_COORDS				0x25
#define WRITE_COORDS_LEN			16

#define PROGRAM_PAUSE				0x26
#define PROGRAM_PAUSE_LEN			2

#define IS_PROGRAM_PAUSED			0x27
#define IS_PROGRAM_PAUSED_LEN		2

#define PROGRAM_RESUME				0x28
#define PROGRAM_RESUME_LEN			2

#define TASK_STOP					0x29
#define TASK_STOP_LEN				2

#define IS_IN_POSITION				0x2A
#define IS_IN_POSITION_LEN			14
#define IS_IN_POSITION_RETURN_LEN	3

#define CHECK_RUNNING				0x2B
#define CHECK_RUNNING_LEN			2
#define CHECK_RUNNING_RETURN_LEN	3


// JOG mode and operation
#define JOG_ANGLE					0x30
#define JOG_ANGLE_LEN				5

#define JOG_ABSOLUTE				0x31
//#define JOG_ABSOLUTE_LEN			

#define JOG_COORD					0x32
#define JOG_COORD_LEN				5

#define SEND_JOG_INCREMENT			0x33
//#define SEND_JOG_INCREMENT_LEN		

#define JOG_STOP					0x34
#define JOG_STOP_LEN				2

#define SET_ENCODER					0x3A
#define SET_ENCODER_LEN				5

#define GET_ENCODER					0x3B
#define GET_ENCODER_LEN				3
#define GET_ENCODER_RETURN_LEN		4

#define SET_ENCODERS				0x3C
#define SET_ENCODERS_LEN			15


// Running Status and Settings
#define GET_SPEED					0x40
#define GET_SPEED_LEN				2
#define GET_SPEED_RETURN_LEN		3

#define SET_SPEED					0x41
#define SET_SPEED_LEN				3

#define GET_FEED_OVERRIDE			0x42
#define GET_FEED_OVERRIDE_LEN		2
#define GET_FEED_OVERRIDE_RETURN_LEN 4

#define SEND_OVERRIDE				0x43
#define SEND_OVERRIDE_LEN			4

#define GET_ACCELERATION			0x44
#define GET_ACCELERATION_LEN		2
#define GET_ACCELERATION_RETURN_LEN		4

#define SET_ACCELERATION			0x45
#define SET_ACCELERATION_LEN		4		

#define GET_JOINT_MIN				0x4A
#define GET_JOINT_MIN_LEN			3
#define GET_JOINT_MIN_RETURN_LEN	4

#define GET_JOINT_MAX				0x4B
#define GET_JOINT_MAX_LEN			3
#define GET_JOINT_MAX_RETURN_LEN	4

#define SET_JOINT_MIN				0x4C
#define SET_JOINT_MIN_LEN			5

#define SET_JOINT_MAX				0x4D
#define SET_JOINT_MAX_LEN			5


// Servo Control
#define IS_SERVO_ENABLED			0x50
#define IS_SERVO_ENABLED_LEN		3
#define IS_SERVO_ENABLED_RETURN_LEN		3

#define IS_ALL_SERVO_ENABLED		0x51
#define IS_ALL_SERVO_ENABLED_LEN	2
#define IS_ALL_SERVO_ENABLED_RETURN_LEN	3

#define SET_SERVO_DATA				0x52
#define SET_SERVO_DATA_LEN			5

#define GET_SERVO_DATA				0x53
#define GET_SERVO_DATA_LEN			4
#define GET_SERVO_DATA_RETURN_LEN	3	

#define SET_SERVO_CALIBRATION		0x54
#define SET_SERVO_CALIBRATION_LEN	3

#define VOID_JOINT_BRAKE			0x55
#define VOID_JOINT_BRAKE_LEN		3

//
//// ATOM IO
#define	SET_PIN_MODE				0x60
#define	SET_PIN_MODE_LEN			4
//
#define	SET_PIN_DATA				0x61
					
//
#define	GET_PIN_INPUT				0x62
#define	GET_PIN_INPUT_LEN			3					
#define GET_PIN_INPUT_RETURN_LEN	3
//
//#define								0x63
//#define								
//
//#define								0x65
//#define								2
//
#define	SET_GRIPPER_STATE				0x66
#define	SET_GRIPPER_STATE_LEN			3
//
//#define								0x67
//#define								2
//
#define	SET_LED						0x6A
#define	SET_LED_LEN					5
//
//// Base basic and IO control
//#define								0x70
//#define								

#endif // !COMMUNICATEDEFINE_H