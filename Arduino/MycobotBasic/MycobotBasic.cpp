#include "MycobotBasic.h"

MycobotBasic::MycobotBasic()
{
	for (auto &val : errorAngles)
		val = -5.0;
	for (auto &val : errorCoords)
		val = -1000.0;
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


void MycobotBasic::rFlushSerial(){
    while( Serial2.read() !=-1)
		;
}


void MycobotBasic::powerOn()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(POWER_ON_LEN);
	Serial2.write(POWER_ON);
	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

void MycobotBasic::powerOff()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(POWER_OFF_LEN);
	Serial2.write(POWER_OFF);
	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

bool MycobotBasic::isPoweredOn()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(IS_POWERED_ON_LEN);
	Serial2.write(IS_POWERED_ON);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	bool* pPowerState = nullptr;
	bool powerState;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pPowerState = (bool*)tempPtr;
			powerState = *pPowerState;
			delete pPowerState;
			return powerState;
		}
	}
	return false;
}

void* MycobotBasic::readData()
{
	rFlushSerial();
	if (!checkHeader())
		return nullptr;

	byte data_len[1];
	byte r_data_3[3], r_data_4[4], r_data_14[14];

	if (readSerial(data_len, 1) != 1)
		return nullptr;

	switch (static_cast<int>(data_len[0]))
	{
	case 3:
		readSerial(r_data_3, 3);
		switch (int(r_data_3[0]))
		{
			case IS_IN_POSITION:
			{
				int* pInt = new int;
				*pInt = r_data_3[1];
				return pInt;
			}

			case CHECK_RUNNING:
			{
				bool* pRunningState = new bool;
				*pRunningState = bool(r_data_3[1]);
				return pRunningState;
			}

			case GET_SPEED:
			{
				int* pSpeed = new int;
				*pSpeed = r_data_3[1];
				return pSpeed;
			}
			case IS_SERVO_ENABLED:
			{
				bool* pServoState = new bool;
				*pServoState = bool(r_data_3[1]);
				return pServoState;
			}
			case IS_ALL_SERVO_ENABLED:
			{
				bool* pServoState = new bool;
				*pServoState = bool(r_data_3[1]);
				return pServoState;
			}
			case IS_POWERED_ON:
			{
				bool* pPowerState = new bool;
				*pPowerState = bool(r_data_3[1]);
				return pPowerState;
			}
			case GET_SERVO_DATA:
			{
				byte* pServoData = new byte;
				*pServoData = r_data_3[1];
				return pServoData;
			}
		}

	case 4:
		readSerial(r_data_4, 4);
		switch (int(r_data_4[0]))
		{
			case GET_FEED_OVERRIDE:
			{
				float* pFeedOverride = new float;
				byte feedOverride_high = r_data_4[1];
				byte feedOverride_low = r_data_4[2];
				float temp = 0.0;
				temp = feedOverride_low + feedOverride_high * 256;
				*pFeedOverride = (temp > 60000 ? (temp - 65536) : temp) / 10;
				return pFeedOverride;
			}

			case GET_ACCELERATION:
			{
				float* pAcceleration = new float;
				byte acceleration_high = r_data_4[1];
				byte acceleration_low = r_data_4[2];
				float temp = 0.0;
				temp = acceleration_low + acceleration_high * 256;
				*pAcceleration = (temp > 60000 ? (temp - 65536) : temp) / 10;
				return pAcceleration;
			}
			case GET_JOINT_MIN:
			{
				float* pJointMin = new float;
				byte jointMin_high = r_data_4[1];
				byte jointMin_low = r_data_4[2];
				float temp = 0.0;
				temp = jointMin_low + jointMin_high * 256;
				*pJointMin = (temp > 60000 ? (temp - 65536) : temp) / 10;
				return pJointMin;
			}
			case GET_JOINT_MAX:
			{
				float* pJointMax = new float;
				byte jointMax_high = r_data_4[1];
				byte jointMax_low = r_data_4[2];
				float temp = 0.0;
				temp = jointMax_low + jointMax_high * 256;
				*pJointMax = (temp > 60000 ? (temp - 65536) : temp) / 10;
				return pJointMax;
			}
			case GET_ENCODER:
			{
				int* pEncoder = new int;
				byte encoder_high = r_data_4[1];
				byte encoder_low = r_data_4[2];
				*pEncoder = encoder_low + encoder_high * 256;
				return pEncoder;
			}
		}

	case 14:
		readSerial(r_data_14, 14);
		switch (int(r_data_14[0]))
		{
			case GET_ANGLES:
			{
					byte angle_1_high = r_data_14[1];
					byte angle_1_low = r_data_14[2];

					byte angle_2_high = r_data_14[3];
					byte angle_2_low = r_data_14[4];

					byte angle_3_high = r_data_14[5];
					byte angle_3_low = r_data_14[6];

					byte angle_4_high = r_data_14[7];
					byte angle_4_low = r_data_14[8];

					byte angle_5_high = r_data_14[9];
					byte angle_5_low = r_data_14[10];

					byte angle_6_high = r_data_14[11];
					byte angle_6_low = r_data_14[12];

					Angles* pAngles = new Angles;
					float temp = 0.0;
					temp = angle_1_low + angle_1_high * 256;
					pAngles->at(0) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
					temp = angle_2_low + angle_2_high * 256;
					pAngles->at(1) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
					temp = angle_3_low + angle_3_high * 256;
					pAngles->at(2) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
					temp = angle_4_low + angle_4_high * 256;
					pAngles->at(3) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
					temp = angle_5_low + angle_5_high * 256;
					pAngles->at(4) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
					temp = angle_6_low + angle_6_high * 256;
					pAngles->at(5) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;

					return pAngles;
			}

			case GET_COORDS:
			{
				byte x_high = r_data_14[1];
				byte x_low = r_data_14[2];

				byte y_high = r_data_14[3];
				byte y_low = r_data_14[4];

				byte z_high = r_data_14[5];
				byte z_low = r_data_14[6];

				byte rx_high = r_data_14[7];
				byte rx_low = r_data_14[8];

				byte ry_high = r_data_14[9];
				byte ry_low = r_data_14[10];

				byte rz_high = r_data_14[11];
				byte rz_low = r_data_14[12];

				Coords* pCoords = new Coords;
				float temp = 0.0;

				temp = x_low + x_high * 256;
				pCoords->at(0) = (temp > 60000 ? (temp - 65536) : temp) / 10;
				temp = y_low + y_high * 256;
				pCoords->at(1) = (temp > 60000 ? (temp - 65536) : temp) / 10;
				temp = z_low + z_high * 256;
				pCoords->at(2) = (temp > 60000 ? (temp - 65536) : temp) / 10;
				temp = rx_low + rx_high * 256;
				pCoords->at(3) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
				temp = ry_low + ry_high * 256;
				pCoords->at(4) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;
				temp = rz_low + rz_high * 256;
				pCoords->at(5) = (temp > 60000 ? (temp - 65536) : temp) / 1000 * COEFFICIENT;

				return pCoords;
			}


		}



	}
	
	return nullptr;
}

Angles MycobotBasic::GetAngles()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_ANGLES_LEN);
	Serial2.write(GET_ANGLES);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	Angles* pAngles = nullptr;
	Angles angles;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pAngles = (Angles*)tempPtr;
			for (int i = 0; i < 6; ++i)
				angles[i] = pAngles->at(i);
			delete pAngles;
			return angles;
		}
	}
	return errorAngles;
}

void MycobotBasic::WriteAngle(int joint, float value, int speed)
{
	byte joint_number = byte(joint - 1);
	value = value / COEFFICIENT;
	byte angle_low = lowByte(static_cast<int>(value * 1000));
	byte angle_high = highByte(static_cast<int>(value * 1000));

	byte sp = speed;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(WRITE_ANGLE_LEN);
	Serial2.write(WRITE_ANGLE);
	Serial2.write(joint_number);
	Serial2.write(angle_high);
	Serial2.write(angle_low);
	Serial2.write(sp);
	Serial2.write(footer);

	delay(WRITE_SERVO_GAP);
}

void MycobotBasic::WriteAngles(Angles angles, int speed)
{
	for (auto &val : angles)
		val = val / COEFFICIENT;
	byte angle_1_low = lowByte(static_cast<int>(angles[0] * 1000));
	byte angle_1_high = highByte(static_cast<int>(angles[0] * 1000));

	byte angle_2_low = lowByte(static_cast<int>(angles[1] * 1000));
	byte angle_2_high = highByte(static_cast<int>(angles[1] * 1000));

	byte angle_3_low = lowByte(static_cast<int>(angles[2] * 1000));
	byte angle_3_high = highByte(static_cast<int>(angles[2] * 1000));

	byte angle_4_low = lowByte(static_cast<int>(angles[3] * 1000));
	byte angle_4_high = highByte(static_cast<int>(angles[3] * 1000));

	byte angle_5_low = lowByte(static_cast<int>(angles[4] * 1000));
	byte angle_5_high = highByte(static_cast<int>(angles[4] * 1000));

	byte angle_6_low = lowByte(static_cast<int>(angles[5] * 1000));
	byte angle_6_high = highByte(static_cast<int>(angles[5] * 1000));

	byte sp = speed;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(WRITE_ANDLES_LEN);
	Serial2.write(WRITE_ANGLES);

	Serial2.write(angle_1_high);
	Serial2.write(angle_1_low);
	Serial2.write(angle_2_high);
	Serial2.write(angle_2_low);
	Serial2.write(angle_3_high);
	Serial2.write(angle_3_low);
	Serial2.write(angle_4_high);
	Serial2.write(angle_4_low);
	Serial2.write(angle_5_high);
	Serial2.write(angle_5_low);
	Serial2.write(angle_6_high);
	Serial2.write(angle_6_low);

	Serial2.write(sp);

	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

Coords MycobotBasic::GetCoords()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_COORDS_LEN);
	Serial2.write(GET_COORDS);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	Coords* pCoords = nullptr;
	Coords tempCoords;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pCoords = (Coords*)tempPtr;
			for (int i = 0; i < 6; ++i)
				tempCoords[i] = pCoords->at(i);
			delete pCoords;
			return tempCoords;
		}
	}
	return errorCoords;
}

void MycobotBasic::WriteCoord(Axis axis, float value, int speed)
{
	byte axis_number = byte(axis);
	int temp_value = 0;
	if (axis == Axis::X || axis == Axis::Y || axis == Axis::Z)
		temp_value = value * 10;
	else
		temp_value = value / COEFFICIENT * 1000;
	byte value_high = highByte(temp_value);
	byte value_low = lowByte(temp_value);

	byte sp = byte(speed);

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(WRITE_COORD_LEN);
	Serial2.write(WRITE_COORD);
	Serial2.write(axis_number);
	Serial2.write(value_high);
	Serial2.write(value_low);
	Serial2.write(sp);
	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

void MycobotBasic::WriteCoords(Coords coord, int speed)
{
	byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
	byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

	byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
	byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

	byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
	byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

	byte coord_rx_low = lowByte(static_cast<int>(coord[3] / COEFFICIENT * 1000));
	byte coord_rx_high = highByte(static_cast<int>(coord[3] / COEFFICIENT * 1000));

	byte coord_ry_low = lowByte(static_cast<int>(coord[4] / COEFFICIENT * 1000));
	byte coord_ry_high = highByte(static_cast<int>(coord[4] / COEFFICIENT * 1000));

	byte coord_rz_low = lowByte(static_cast<int>(coord[5] / COEFFICIENT * 1000));
	byte coord_rz_high = highByte(static_cast<int>(coord[5] / COEFFICIENT * 1000));

	byte sp = speed;
	byte mode = 1;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(WRITE_COORDS_LEN);
	Serial2.write(WRITE_COORDS);
	Serial2.write(coord_x_high);
	Serial2.write(coord_x_low);
	Serial2.write(coord_y_high);
	Serial2.write(coord_y_low);
	Serial2.write(coord_z_high);
	Serial2.write(coord_z_low);
	Serial2.write(coord_rx_high);
	Serial2.write(coord_rx_low);
	Serial2.write(coord_ry_high);
	Serial2.write(coord_ry_low);
	Serial2.write(coord_rz_high);
	Serial2.write(coord_rz_low);
	Serial2.write(sp);
	Serial2.write(mode);
	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

int MycobotBasic::isInPosition(Coords coord, bool is_linear)
{
	byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
	byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

	byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
	byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

	byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
	byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

	byte coord_rx_low = lowByte(static_cast<int>(coord[3] / COEFFICIENT * 1000));
	byte coord_rx_high = highByte(static_cast<int>(coord[3] / COEFFICIENT * 1000));

	byte coord_ry_low = lowByte(static_cast<int>(coord[4] / COEFFICIENT * 1000));
	byte coord_ry_high = highByte(static_cast<int>(coord[4] / COEFFICIENT * 1000));

	byte coord_rz_low = lowByte(static_cast<int>(coord[5] / COEFFICIENT * 1000));
	byte coord_rz_high = highByte(static_cast<int>(coord[5] / COEFFICIENT * 1000));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(IS_IN_POSITION_LEN);
	Serial2.write(IS_IN_POSITION);
	Serial2.write(coord_x_high);
	Serial2.write(coord_x_low);
	Serial2.write(coord_y_high);
	Serial2.write(coord_y_low);
	Serial2.write(coord_z_high);
	Serial2.write(coord_z_low);
	Serial2.write(coord_rx_high);
	Serial2.write(coord_rx_low);
	Serial2.write(coord_ry_high);
	Serial2.write(coord_ry_low);
	Serial2.write(coord_rz_low);
	Serial2.write(coord_rz_high);
	Serial2.write(footer);


	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	int* pIsInposition = nullptr;
	int isInposition;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pIsInposition = (int*)tempPtr;
			isInposition = *pIsInposition;
			delete pIsInposition;
			return isInposition;
		}
	}
	return -1;
}

bool MycobotBasic::CheckRunning()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(CHECK_RUNNING_LEN);
	Serial2.write(CHECK_RUNNING);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	bool* pRunningState = nullptr;
	bool runningState;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pRunningState = (bool*)tempPtr;
			runningState = *pRunningState;
			delete pRunningState;
			return runningState;
		}
	}
	return false;
}


void MycobotBasic::JogAngle(int joint, int direction, int speed)
{
	byte joint_number = joint;
	byte di = direction;
	byte sp = speed;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(JOG_ANGLE_LEN);
	Serial2.write(JOG_ANGLE);
	Serial2.write(joint_number);
	Serial2.write(di);
	Serial2.write(sp);
	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

void MycobotBasic::JogCoord(Axis axis, int direction, int speed)
{
	byte axis_number = axis + 1;
	byte di = direction;
	byte sp = speed;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(JOG_COORD_LEN);
	Serial2.write(JOG_COORD);
	Serial2.write(axis_number);
	Serial2.write(di);
	Serial2.write(sp);
	Serial2.write(footer);
	delay(WRITE_SERVO_GAP);
}

void MycobotBasic::JogStop()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(JOG_STOP_LEN);
	Serial2.write(JOG_STOP);
	Serial2.write(footer);
}

void MycobotBasic::SetEncoder(int joint, int encoder)
{
	byte joint_number = joint - 1;
	byte encoder_high = highByte(encoder);
	byte encoder_low = lowByte(encoder);

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_ENCODER_LEN);
	Serial2.write(SET_ENCODER);
	Serial2.write(joint_number);
	Serial2.write(encoder_high);
	Serial2.write(encoder_low);
	Serial2.write(footer);
}

int MycobotBasic::GetEncoder(int joint)
{
	byte joint_number = joint - 1;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_ENCODER_LEN);
	Serial2.write(GET_ENCODER);
	Serial2.write(joint);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	int* pEncoder = nullptr;
	int encoder;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pEncoder = (int*)tempPtr;
			encoder = *pEncoder;
			delete pEncoder;
			return encoder;
		}
	}

	return -1;
}

void MycobotBasic::SetEncoders(Angles angleEncoders, int speed)
{
	byte angle_1_high = highByte(static_cast<int>(angleEncoders[0]));
	byte angle_1_low = lowByte(static_cast<int>(angleEncoders[0]));
	byte angle_2_high = highByte(static_cast<int>(angleEncoders[1]));
	byte angle_2_low = lowByte(static_cast<int>(angleEncoders[1]));
	byte angle_3_high = highByte(static_cast<int>(angleEncoders[2]));
	byte angle_3_low = lowByte(static_cast<int>(angleEncoders[2]));
	byte angle_4_high = highByte(static_cast<int>(angleEncoders[3]));
	byte angle_4_low = lowByte(static_cast<int>(angleEncoders[3]));
	byte angle_5_high = highByte(static_cast<int>(angleEncoders[4]));
	byte angle_5_low = lowByte(static_cast<int>(angleEncoders[4]));
	byte angle_6_high = highByte(static_cast<int>(angleEncoders[5]));
	byte angle_6_low = lowByte(static_cast<int>(angleEncoders[5]));
	byte sp = speed;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_ENCODERS_LEN);
	Serial2.write(SET_ENCODERS);
	Serial2.write(angle_1_high);
	Serial2.write(angle_1_low);
	Serial2.write(angle_2_high);
	Serial2.write(angle_2_low);
	Serial2.write(angle_3_high);
	Serial2.write(angle_3_low);
	Serial2.write(angle_4_high);
	Serial2.write(angle_4_low);
	Serial2.write(angle_5_high);
	Serial2.write(angle_5_low);
	Serial2.write(angle_6_high);
	Serial2.write(angle_6_low);
	Serial2.write(sp);
	Serial2.write(footer);
}

int MycobotBasic::GetSpeed()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_SPEED_LEN);
	Serial2.write(GET_SPEED);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	int* pSpeed = nullptr;
	int speed;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pSpeed = (int*)tempPtr;
			speed = *pSpeed;
			delete pSpeed;
			return speed;
		}
	}

	return -1;
}

void MycobotBasic::SetSpeed(int percentage)
{
	byte speed = percentage;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_SPEED_LEN);
	Serial2.write(SET_SPEED);
	Serial2.write(speed);
	Serial2.write(footer);
}

float MycobotBasic::GetFeedOverride()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_FEED_OVERRIDE_LEN);
	Serial2.write(GET_FEED_OVERRIDE);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	float* pFeedOverride = nullptr;
	float feedOverride;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pFeedOverride = (float*)tempPtr;
			feedOverride = *pFeedOverride;
			delete pFeedOverride;
			return feedOverride;
		}
	}

	return -1.0;
}

void MycobotBasic::SendFeedOverride(float feedOverride)
{
	byte feedOverride_high = highByte(static_cast<int>(feedOverride * 10));
	byte feedOverride_low = lowByte(static_cast<int>(feedOverride * 10));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SEND_OVERRIDE_LEN);
	Serial2.write(SEND_OVERRIDE);
	Serial2.write(feedOverride_high);
	Serial2.write(feedOverride_low);
	Serial2.write(footer);
}

float MycobotBasic::GetAcceleration()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_ACCELERATION_LEN);
	Serial2.write(GET_ACCELERATION);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	float* pAcceleration = nullptr;
	float acceleration;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pAcceleration = (float*)tempPtr;
			acceleration = *pAcceleration;
			delete pAcceleration;
			return acceleration;
		}
	}

	return -1.0;
}

void MycobotBasic::SetAcceleration(float acceleration)
{
	byte acceleration_high = highByte(static_cast<int>(acceleration * 10));
	byte acceleration_low = lowByte(static_cast<int>(acceleration * 10));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_ACCELERATION_LEN);
	Serial2.write(SET_ACCELERATION);
	Serial2.write(acceleration_high);
	Serial2.write(acceleration_low);
	Serial2.write(footer);
}

float MycobotBasic::getJointMin(int joint)
{
	byte joint_number = joint - 1;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_JOINT_MIN_LEN);
	Serial2.write(GET_JOINT_MIN);
	Serial2.write(joint_number);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	float* pJointMin = nullptr;
	float jointMin;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pJointMin = (float*)tempPtr;
			jointMin = *pJointMin;
			delete pJointMin;
			return jointMin;
		}
	}

	return -5.0;
}

float MycobotBasic::getJointMax(int joint)
{
	byte joint_number = joint - 1;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_JOINT_MAX_LEN);
	Serial2.write(GET_JOINT_MAX);
	Serial2.write(joint_number);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	float* pJointMax = nullptr;
	float jointMax;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pJointMax = (float*)tempPtr;
			jointMax = *pJointMax;
			delete pJointMax;
			return jointMax;
		}
	}

	return -5.0;
}

void MycobotBasic::setJointMin(int joint, float angle)
{
	byte joint_number = joint - 1;
	byte angle_low = lowByte(static_cast<int>(angle * 10));
	byte angle_high = highByte(static_cast<int>(angle * 10));
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_JOINT_MIN_LEN);
	Serial2.write(SET_JOINT_MIN);
	Serial2.write(joint_number);
	Serial2.write(angle_high);
	Serial2.write(angle_low);
	Serial2.write(footer);
}

void MycobotBasic::setJointMax(int joint, float angle)
{
	byte joint_number = joint - 1;
	byte angle_low = lowByte(static_cast<int>(angle * 10));
	byte angle_high = highByte(static_cast<int>(angle * 10));
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_JOINT_MAX_LEN);
	Serial2.write(SET_JOINT_MAX);
	Serial2.write(joint_number);
	Serial2.write(angle_high);
	Serial2.write(angle_low);
	Serial2.write(footer);
}

bool MycobotBasic::isServoEnabled(int joint)
{
	byte joint_number = joint - 1;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(IS_SERVO_ENABLED_LEN);
	Serial2.write(IS_SERVO_ENABLED);
	Serial2.write(joint_number);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	bool* pServoState = nullptr;
	bool servoState;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pServoState = (bool*)tempPtr;
			servoState = *pServoState;
			delete pServoState;
			return servoState;
		}
	}
	return false;
}

bool MycobotBasic::isAllServoEnabled()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(IS_ALL_SERVO_ENABLED_LEN);
	Serial2.write(IS_ALL_SERVO_ENABLED);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	bool* pServoState = nullptr;
	bool servoState;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pServoState = (bool*)tempPtr;
			servoState = *pServoState;
			delete pServoState;
			return servoState;
		}
	}
	return false;
}

byte MycobotBasic::getServoData(int joint, byte data_id)
{
	byte joint_number = joint - 1;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_SERVO_DATA_LEN);
	Serial2.write(GET_SERVO_DATA);
	Serial2.write(joint_number);
	Serial2.write(data_id);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	byte* pServoData = nullptr;
	byte servoData;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pServoData = (byte*)tempPtr;
			servoData = *pServoData;
			delete pServoData;
			return servoData;
		}
	}

	return -1.0;
}

void MycobotBasic::setServoCalibration(int joint)
{
	byte joint_number = joint - 1;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_SERVO_CALIBRATION_LEN);
	Serial2.write(SET_SERVO_CALIBRATION);
	Serial2.write(joint_number);
	Serial2.write(footer);
}


void MycobotBasic::setPinMode(byte pin_no, byte pin_mode)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_PIN_MODE_LEN);
	Serial2.write(SET_PIN_MODE);
	Serial2.write(pin_no);
	Serial2.write(pin_mode);
	Serial2.write(footer);
}

void MycobotBasic::pause()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(PROGRAM_PAUSE_LEN);
	Serial2.write(PROGRAM_PAUSE);
	Serial2.write(footer);
}

void MycobotBasic::resume()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(PROGRAM_RESUME_LEN);
	Serial2.write(PROGRAM_RESUME);
	Serial2.write(footer);
}

void MycobotBasic::stop()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(TASK_STOP_LEN);
	Serial2.write(TASK_STOP);
	Serial2.write(footer);
}


void MycobotBasic::setLEDRGB(byte r, byte g, byte b)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_LED_LEN);
	Serial2.write(SET_LED);
	Serial2.write(r);
	Serial2.write(g);
	Serial2.write(b);
	Serial2.write(footer);
}

void MycobotBasic::setGripper(int data)
{
	byte gripper_data = data;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_GRIPPER_STATE_LEN);
	Serial2.write(SET_GRIPPER_STATE);
	Serial2.write(gripper_data);
	Serial2.write(footer);
}

void MycobotBasic::setServoData(byte servo_no, byte servo_state, byte servo_data)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_SERVO_DATA_LEN);
	Serial2.write(SET_SERVO_DATA);

	Serial2.write(servo_no);
	Serial2.write(servo_state);
	Serial2.write(servo_data);
	Serial2.write(footer);
}

void MycobotBasic::setFreeMove()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_FREE_MOVE_LEN);
	Serial2.write(SET_FREE_MOVE);
	Serial2.write(footer);
	delay(500);  //wait for servo relass
}
