#include "MycobotBasic.h"

MycobotBasic::MycobotBasic()
{
	for (auto &val : error_angles)
		val = -1000.0;
	for (auto &val : error_coords)
		val = -1000.0;

	for (auto val : printList)
		messages_map.insert(val);
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
    if (t_use > IO_TimeOut){ 
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
				bool* prunning_state = new bool;
				*prunning_state = bool(r_data_3[1]);
				return prunning_state;
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
			case GET_REF_FRAME:
			{
				RFType* pRftype = new RFType;
				*pRftype = RFType(r_data_3[1]);
				return pRftype;
			}
			case GET_MOVEMENT_TYPE:
			{
				MovementType* pMovementType = new MovementType;
				*pMovementType = MovementType(r_data_3[1]);
				return pMovementType;
			}
			case GET_END_TYPE:
			{
				EndType* pEndType = new EndType;
				*pEndType = EndType(r_data_3[1]);
				return pEndType;
			}
			case ROBOTIC_MESSAGE:
			{
				byte* pMessage = new byte;
				*pMessage = r_data_3[1];
				return pMessage;
			}

			case GET_DIGITAL_INPUT:
			{
				int* returnValue = new int;
				*returnValue = r_data_3[1];
				return returnValue;
			}

			case IS_GRIPPER_MOVING:
			{
				int* pState = new int;
				*pState = r_data_3[1];
				return pState;
			}

		}

	case 4:
		readSerial(r_data_4, 4);
		switch (int(r_data_4[0]))
		{
			case GET_FEED_OVERRIDE:
			{
				float* pfeed_override = new float;
				byte feed_override_high = r_data_4[1];
				byte feed_override_low = r_data_4[2];
				float temp = 0.0;
				temp = feed_override_low + feed_override_high * 256;
				*pfeed_override = (temp > 33000 ? (temp - 65536) : temp) / 10;
				return pfeed_override;
			}

			case GET_ACCELERATION:
			{
				float* pAcceleration = new float;
				byte acceleration_high = r_data_4[1];
				byte acceleration_low = r_data_4[2];
				float temp = 0.0;
				temp = acceleration_low + acceleration_high * 256;
				*pAcceleration = (temp > 33000 ? (temp - 65536) : temp) / 10;
				return pAcceleration;
			}
			case GET_JOINT_MIN:
			{
				float* pJointMin = new float;
				byte jointMin_high = r_data_4[1];
				byte jointMin_low = r_data_4[2];
				float temp = 0.0;
				temp = jointMin_low + jointMin_high * 256;
				*pJointMin = (temp > 33000 ? (temp - 65536) : temp) / 10;
				return pJointMin;
			}
			case GET_JOINT_MAX:
			{
				float* pJointMax = new float;
				byte jointMax_high = r_data_4[1];
				byte jointMax_low = r_data_4[2];
				float temp = 0.0;
				temp = jointMax_low + jointMax_high * 256;
				*pJointMax = (temp > 33000 ? (temp - 65536) : temp) / 10;
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

			case GET_GRIPPER_VALUE:
			{
				int* returnValue = new int;
				byte gripper_high = r_data_4[1];
				byte gripper_low = r_data_4[2];
				*returnValue = gripper_low + gripper_high * 256;
				return returnValue;
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
					pAngles->at(0) = (temp > 33000 ? (temp - 65536) : temp) / 100;
					temp = angle_2_low + angle_2_high * 256;
					pAngles->at(1) = (temp > 33000 ? (temp - 65536) : temp) / 100;
					temp = angle_3_low + angle_3_high * 256;
					pAngles->at(2) = (temp > 33000 ? (temp - 65536) : temp) / 100;
					temp = angle_4_low + angle_4_high * 256;
					pAngles->at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
					temp = angle_5_low + angle_5_high * 256;
					pAngles->at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
					temp = angle_6_low + angle_6_high * 256;
					pAngles->at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

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
				pCoords->at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = y_low + y_high * 256;
				pCoords->at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = z_low + z_high * 256;
				pCoords->at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = rx_low + rx_high * 256;
				pCoords->at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
				temp = ry_low + ry_high * 256;
				pCoords->at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
				temp = rz_low + rz_high * 256;
				pCoords->at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

				return pCoords;
			}

			case GET_TOOL_REF:
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
				pCoords->at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = y_low + y_high * 256;
				pCoords->at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = z_low + z_high * 256;
				pCoords->at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = rx_low + rx_high * 256;
				pCoords->at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
				temp = ry_low + ry_high * 256;
				pCoords->at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
				temp = rz_low + rz_high * 256;
				pCoords->at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

				return pCoords;
			}

			case GET_WORLD_REF:
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
				pCoords->at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = y_low + y_high * 256;
				pCoords->at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = z_low + z_high * 256;
				pCoords->at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
				temp = rx_low + rx_high * 256;
				pCoords->at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
				temp = ry_low + ry_high * 256;
				pCoords->at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
				temp = rz_low + rz_high * 256;
				pCoords->at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

				return pCoords;
			}
		}



	}

	return nullptr;
}

Angles MycobotBasic::getAngles()
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
	return error_angles;
}

void MycobotBasic::writeAngle(int joint, float value, int speed)
{
	byte joint_number = byte(joint);
	byte angle_low = lowByte(static_cast<int>(value * 100));
	byte angle_high = highByte(static_cast<int>(value * 100));

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

void MycobotBasic::writeAngles(Angles angles, int speed)
{
	byte angle_1_low = lowByte(static_cast<int>(angles[0] * 100));
	byte angle_1_high = highByte(static_cast<int>(angles[0] * 100));

	byte angle_2_low = lowByte(static_cast<int>(angles[1] * 100));
	byte angle_2_high = highByte(static_cast<int>(angles[1] * 100));

	byte angle_3_low = lowByte(static_cast<int>(angles[2] * 100));
	byte angle_3_high = highByte(static_cast<int>(angles[2] * 100));

	byte angle_4_low = lowByte(static_cast<int>(angles[3] * 100));
	byte angle_4_high = highByte(static_cast<int>(angles[3] * 100));

	byte angle_5_low = lowByte(static_cast<int>(angles[4] * 100));
	byte angle_5_high = highByte(static_cast<int>(angles[4] * 100));

	byte angle_6_low = lowByte(static_cast<int>(angles[5] * 100));
	byte angle_6_high = highByte(static_cast<int>(angles[5] * 100));

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

Coords MycobotBasic::getCoords()
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
	return error_coords;
}

void MycobotBasic::writeCoord(Axis axis, float value, int speed)
{
	byte axis_number = byte(axis);
	int temp_value = 0;
	if (axis == Axis::X || axis == Axis::Y || axis == Axis::Z)
		temp_value = value * 10;
	else
		temp_value = value * 100;
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
	//delay(WRITE_SERVO_GAP);

	receiveMessages();
}

void MycobotBasic::writeCoords(Coords coord, int speed)
{
	byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
	byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

	byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
	byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

	byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
	byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

	byte coord_rx_low = lowByte(static_cast<int>(coord[3] * 100));
	byte coord_rx_high = highByte(static_cast<int>(coord[3] * 100));

	byte coord_ry_low = lowByte(static_cast<int>(coord[4] * 100));
	byte coord_ry_high = highByte(static_cast<int>(coord[4] * 100));

	byte coord_rz_low = lowByte(static_cast<int>(coord[5] * 100));
	byte coord_rz_high = highByte(static_cast<int>(coord[5] * 100));

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
	//delay(WRITE_SERVO_GAP);

	receiveMessages();
}

int MycobotBasic::isInPosition(Coords coord, bool is_linear)
{
	byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
	byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

	byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
	byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

	byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
	byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

	byte coord_rx_low = lowByte(static_cast<int>(coord[3] * 100));
	byte coord_rx_high = highByte(static_cast<int>(coord[3] * 100));

	byte coord_ry_low = lowByte(static_cast<int>(coord[4] * 100));
	byte coord_ry_high = highByte(static_cast<int>(coord[4] * 100));

	byte coord_rz_low = lowByte(static_cast<int>(coord[5] * 100));
	byte coord_rz_high = highByte(static_cast<int>(coord[5] * 100));

	byte type = byte(is_linear);

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
	Serial2.write(coord_rz_high);
	Serial2.write(coord_rz_low);
	Serial2.write(type);
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

bool MycobotBasic::checkRunning()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(CHECK_RUNNING_LEN);
	Serial2.write(CHECK_RUNNING);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	bool* prunning_state = nullptr;
	bool running_state;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			prunning_state = (bool*)tempPtr;
			running_state = *prunning_state;
			delete prunning_state;
			return running_state;
		}
	}
	return false;
}


void MycobotBasic::jogAngle(int joint, int direction, int speed)
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

void MycobotBasic::jogCoord(Axis axis, int direction, int speed)
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

void MycobotBasic::jogStop()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(JOG_STOP_LEN);
	Serial2.write(JOG_STOP);
	Serial2.write(footer);
}

void MycobotBasic::setEncoder(int joint, int encoder)
{
	byte joint_number = joint;
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

int MycobotBasic::getEncoder(int joint)
{
	byte joint_number = joint;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_ENCODER_LEN);
	Serial2.write(GET_ENCODER);
	Serial2.write(joint_number);
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

void MycobotBasic::setEncoders(Angles angleEncoders, int speed)
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

int MycobotBasic::getSpeed()
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

void MycobotBasic::setSpeed(int percentage)
{
	byte speed = percentage;
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_SPEED_LEN);
	Serial2.write(SET_SPEED);
	Serial2.write(speed);
	Serial2.write(footer);
}

float MycobotBasic::getFeedOverride()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_FEED_OVERRIDE_LEN);
	Serial2.write(GET_FEED_OVERRIDE);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	float* pfeed_override = nullptr;
	float feed_override;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pfeed_override = (float*)tempPtr;
			feed_override = *pfeed_override;
			delete pfeed_override;
			return feed_override;
		}
	}

	return -1.0;
}

void MycobotBasic::sendFeedOverride(float feed_override)
{
	byte feed_override_high = highByte(static_cast<int>(feed_override * 10));
	byte feed_override_low = lowByte(static_cast<int>(feed_override * 10));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SEND_OVERRIDE_LEN);
	Serial2.write(SEND_OVERRIDE);
	Serial2.write(feed_override_high);
	Serial2.write(feed_override_low);
	Serial2.write(footer);
}

float MycobotBasic::getAcceleration()
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

void MycobotBasic::setAcceleration(float acceleration)
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
	byte joint_number = joint;
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
	byte joint_number = joint;
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
	byte joint_number = joint;
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
	byte joint_number = joint;
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
	byte joint_number = joint;
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
	byte joint_number = joint;
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
	byte joint_number = joint;
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
}

void MycobotBasic::receiveMessages()
{
	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	byte* pMessage = nullptr;
	int message;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pMessage = (byte*)tempPtr;
			message = static_cast<int>(*pMessage);
			delete pMessage;

			std::map<int, std::string>::iterator iter = messages_map.find(message);
			char* pChar = (char*)iter->second.c_str();
			if (iter != messages_map.end())
				Serial.println(pChar);
		}
	}

}

void MycobotBasic::setMovementType(MovementType movement_type)
{
	byte mt = movement_type;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_MOVEMENT_TYPE_LEN);
	Serial2.write(SET_MOVEMENT_TYPE);
	Serial2.write(mt);
	Serial2.write(footer);
}

MovementType MycobotBasic::getMovementType()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_MOVEMENT_TYPE_LEN);
	Serial2.write(GET_MOVEMENT_TYPE);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	MovementType* pMovementType = nullptr;
	MovementType movement_type;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pMovementType = (MovementType*)tempPtr;
			movement_type = *pMovementType;
			delete pMovementType;
			return movement_type;
		}
	}

	return ERROR_MOVEMENT;
}

void MycobotBasic::setToolReference(Coords coord)
{
	byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
	byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

	byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
	byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

	byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
	byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

	byte coord_rx_low = lowByte(static_cast<int>(coord[3] * 100));
	byte coord_rx_high = highByte(static_cast<int>(coord[3] * 100));

	byte coord_ry_low = lowByte(static_cast<int>(coord[4] * 100));
	byte coord_ry_high = highByte(static_cast<int>(coord[4] * 100));

	byte coord_rz_low = lowByte(static_cast<int>(coord[5] * 100));
	byte coord_rz_high = highByte(static_cast<int>(coord[5] * 100));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_TOOL_REF_LEN);
	Serial2.write(SET_TOOL_REF);
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
	Serial2.write(footer);
}

void MycobotBasic::setWorldReference(Coords coord)
{
	byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
	byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

	byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
	byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

	byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
	byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

	byte coord_rx_low = lowByte(static_cast<int>(coord[3] * 100));
	byte coord_rx_high = highByte(static_cast<int>(coord[3] * 100));

	byte coord_ry_low = lowByte(static_cast<int>(coord[4] * 100));
	byte coord_ry_high = highByte(static_cast<int>(coord[4] * 100));

	byte coord_rz_low = lowByte(static_cast<int>(coord[5] * 100));
	byte coord_rz_high = highByte(static_cast<int>(coord[5] * 100));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_WORLD_REF_LEN);
	Serial2.write(SET_WORLD_REF);
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
	Serial2.write(footer);
}

Coords MycobotBasic::getToolReference()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_TOOL_REF_LEN);
	Serial2.write(GET_TOOL_REF);
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
	return error_coords;
}

Coords MycobotBasic::getWorldReference()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_WORLD_REF_LEN);
	Serial2.write(GET_WORLD_REF);
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
	return error_coords;
}

void MycobotBasic::setReferenceFrame(RFType rftype)
{
	byte rt = rftype;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_REF_FRAME_LEN);
	Serial2.write(SET_REF_FRAME);
	Serial2.write(rt);
	Serial2.write(footer);
}

RFType MycobotBasic::getReferenceFrame()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_REF_FRAME_LEN);
	Serial2.write(GET_REF_FRAME);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	RFType* pRFType = nullptr;
	RFType rftype;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pRFType = (RFType*)tempPtr;
			rftype = *pRFType;
			delete pRFType;
			return rftype;
		}
	}

	return ERROR_RF;
}

void MycobotBasic::setEndType(EndType end_type)
{
	byte et = end_type;

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_END_TYPE_LEN);
	Serial2.write(SET_END_TYPE);
	Serial2.write(et);
	Serial2.write(footer);
}

EndType MycobotBasic::getEndType()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_END_TYPE_LEN);
	Serial2.write(GET_END_TYPE);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	EndType* pEndType = nullptr;
	EndType end_type;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pEndType = (EndType*)tempPtr;
			end_type = *pEndType;
			delete pEndType;
			return end_type;
		}
	}

	return ERROR_END;
}

void MycobotBasic::setDigitalOutput(byte pin_no, byte pin_state)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_DIGITAL_OUTPUT_LEN);
	Serial2.write(SET_DIGITAL_OUTPUT);
	Serial2.write(pin_no);
	Serial2.write(pin_state);
	Serial2.write(footer);
}

int MycobotBasic::getDigitalInput(byte pin_no)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_DIGITAL_INPUT_LEN);
	Serial2.write(GET_DIGITAL_INPUT);
	Serial2.write(pin_no);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	int* pReturnValue = nullptr;
	int returnValue;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pReturnValue = (int*)tempPtr;
			returnValue = *pReturnValue;
			delete pReturnValue;
			return returnValue;
		}
	}

	return -1;
}

/*
void MycobotBasic::setPWMMode(int freq, byte pin_no, byte channel)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_PWM_MODE_LEN);
	Serial2.write(SET_PWM_MODE);


	byte freq_high = highByte(freq);
	byte freq_low = lowByte(freq);

	Serial2.write(freq_high);
	Serial2.write(freqa_low);

	Serial2.write(pin_no);
	Serial2.write(channel);
	Serial2.write(footer);
}*/

void MycobotBasic::setPWMOutput(byte pin_no, int freq,  byte pin_write)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_PWM_OUTPUT_LEN);
	Serial2.write(SET_PWM_OUTPUT);
	Serial2.write(pin_no);

	byte freq_high = highByte(freq);
	byte freq_low = lowByte(freq);

	Serial2.write(freq_high);
	Serial2.write(freq_low);


	Serial2.write(pin_write);
	Serial2.write(footer);
}

void MycobotBasic::releaseServo(byte servo_no)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(RELEASE_SERVO_LEN);
	Serial2.write(RELEASE_SERVO);
	Serial2.write(servo_no);
	Serial2.write(footer);
}

void MycobotBasic::focusServo(byte servo_no)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(FOCUS_SERVO_LEN);
	Serial2.write(FOCUS_SERVO);
	Serial2.write(servo_no);
	Serial2.write(footer);
}

void MycobotBasic::setGripperState(byte mode, int sp)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_GRIPPER_STATE_LEN);
	Serial2.write(SET_GRIPPER_STATE);
	Serial2.write(mode);
	Serial2.write(sp);
	Serial2.write(footer);
}

void MycobotBasic::setGripperValue(int data, int sp)
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_GRIPPER_VALUE_LEN);
	Serial2.write(SET_GRIPPER_VALUE);

	byte data_high = highByte(data);
	byte data_low = lowByte(data);

	Serial2.write(data_high);
	Serial2.write(data_low);
	Serial2.write(sp);
	Serial2.write(footer);
}

void MycobotBasic::setGripperIni()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(SET_GRIPPER_INI_LEN);
	Serial2.write(SET_GRIPPER_INI);
	Serial2.write(footer);
}

int MycobotBasic::getGripperValue()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(GET_GRIPPER_VALUE_LEN);
	Serial2.write(GET_GRIPPER_VALUE);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	int* pReturnValue = nullptr;
	int returnValue;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pReturnValue = (int*)tempPtr;
			returnValue = *pReturnValue;
			delete pReturnValue;
			return returnValue;
		}
	}

	return -1;
}

bool MycobotBasic::isGripperMoving()
{
	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(IS_GRIPPER_MOVING_LEN);
	Serial2.write(IS_GRIPPER_MOVING);
	Serial2.write(footer);

	unsigned long t_begin = millis();
	void* tempPtr = nullptr;
	bool* pState = nullptr;
	bool state;

	while (true)
	{
		if (millis() - t_begin > 40)
			break;
		tempPtr = readData();
		if (tempPtr == nullptr)
			continue;
		else
		{
			pState = (bool*)tempPtr;
			state = *pState;
			delete pState;
			return state;
		}
	}
	return false;
}

void MycobotBasic::moveCCoords(Coords begin_coord, Coords middle_coord, Coords end_coord)
{
	// begin_coord
	byte begin_x_low = lowByte(static_cast<int>(begin_coord[0] * 10));
	byte begin_x_high = highByte(static_cast<int>(begin_coord[0] * 10));

	byte begin_y_low = lowByte(static_cast<int>(begin_coord[1] * 10));
	byte begin_y_high = highByte(static_cast<int>(begin_coord[1] * 10));

	byte begin_z_low = lowByte(static_cast<int>(begin_coord[2] * 10));
	byte begin_z_high = highByte(static_cast<int>(begin_coord[2] * 10));

	byte begin_rx_low = lowByte(static_cast<int>(begin_coord[3] * 100));
	byte begin_rx_high = highByte(static_cast<int>(begin_coord[3] * 100));

	byte begin_ry_low = lowByte(static_cast<int>(begin_coord[4] * 100));
	byte begin_ry_high = highByte(static_cast<int>(begin_coord[4] * 100));

	byte begin_rz_low = lowByte(static_cast<int>(begin_coord[5] * 100));
	byte begin_rz_high = highByte(static_cast<int>(begin_coord[5] * 100));

	// middle_coord
	byte middle_x_low = lowByte(static_cast<int>(middle_coord[0] * 10));
	byte middle_x_high = highByte(static_cast<int>(middle_coord[0] * 10));

	byte middle_y_low = lowByte(static_cast<int>(middle_coord[1] * 10));
	byte middle_y_high = highByte(static_cast<int>(middle_coord[1] * 10));

	byte middle_z_low = lowByte(static_cast<int>(middle_coord[2] * 10));
	byte middle_z_high = highByte(static_cast<int>(middle_coord[2] * 10));

	byte middle_rx_low = lowByte(static_cast<int>(middle_coord[3] * 100));
	byte middle_rx_high = highByte(static_cast<int>(middle_coord[3] * 100));

	byte middle_ry_low = lowByte(static_cast<int>(middle_coord[4] * 100));
	byte middle_ry_high = highByte(static_cast<int>(middle_coord[4] * 100));

	byte middle_rz_low = lowByte(static_cast<int>(middle_coord[5] * 100));
	byte middle_rz_high = highByte(static_cast<int>(middle_coord[5] * 100));

	// end_coord
	byte end_x_low = lowByte(static_cast<int>(end_coord[0] * 10));
	byte end_x_high = highByte(static_cast<int>(end_coord[0] * 10));

	byte end_y_low = lowByte(static_cast<int>(end_coord[1] * 10));
	byte end_y_high = highByte(static_cast<int>(end_coord[1] * 10));

	byte end_z_low = lowByte(static_cast<int>(end_coord[2] * 10));
	byte end_z_high = highByte(static_cast<int>(end_coord[2] * 10));

	byte end_rx_low = lowByte(static_cast<int>(end_coord[3] * 100));
	byte end_rx_high = highByte(static_cast<int>(end_coord[3] * 100));

	byte end_ry_low = lowByte(static_cast<int>(end_coord[4] * 100));
	byte end_ry_high = highByte(static_cast<int>(end_coord[4] * 100));

	byte end_rz_low = lowByte(static_cast<int>(end_coord[5] * 100));
	byte end_rz_high = highByte(static_cast<int>(end_coord[5] * 100));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(MOVEC_COORDS_DEFAULT_LEN);
	Serial2.write(MOVEC_COORDS_DEFAULT);
	Serial2.write(begin_x_high);
	Serial2.write(begin_x_low);
	Serial2.write(begin_y_high);
	Serial2.write(begin_y_low);
	Serial2.write(begin_z_high);
	Serial2.write(begin_z_low);
	Serial2.write(begin_rx_high);
	Serial2.write(begin_rx_low);
	Serial2.write(begin_ry_high);
	Serial2.write(begin_ry_low);
	Serial2.write(begin_rz_high);
	Serial2.write(begin_rz_low);
	Serial2.write(middle_x_high);
	Serial2.write(middle_x_low);
	Serial2.write(middle_y_high);
	Serial2.write(middle_y_low);
	Serial2.write(middle_z_high);
	Serial2.write(middle_z_low);
	Serial2.write(middle_rx_high);
	Serial2.write(middle_rx_low);
	Serial2.write(middle_ry_high);
	Serial2.write(middle_ry_low);
	Serial2.write(middle_rz_high);
	Serial2.write(middle_rz_low);
	Serial2.write(end_x_high);
	Serial2.write(end_x_low);
	Serial2.write(end_y_high);
	Serial2.write(end_y_low);
	Serial2.write(end_z_high);
	Serial2.write(end_z_low);
	Serial2.write(end_rx_high);
	Serial2.write(end_rx_low);
	Serial2.write(end_ry_high);
	Serial2.write(end_ry_low);
	Serial2.write(end_rz_high);
	Serial2.write(end_rz_low);
	Serial2.write(footer);
}

void MycobotBasic::moveCCoords(Coords middle_coord, Coords end_coord)
{
	// middle_coord
	byte middle_x_low = lowByte(static_cast<int>(middle_coord[0] * 10));
	byte middle_x_high = highByte(static_cast<int>(middle_coord[0] * 10));

	byte middle_y_low = lowByte(static_cast<int>(middle_coord[1] * 10));
	byte middle_y_high = highByte(static_cast<int>(middle_coord[1] * 10));

	byte middle_z_low = lowByte(static_cast<int>(middle_coord[2] * 10));
	byte middle_z_high = highByte(static_cast<int>(middle_coord[2] * 10));

	byte middle_rx_low = lowByte(static_cast<int>(middle_coord[3] * 100));
	byte middle_rx_high = highByte(static_cast<int>(middle_coord[3] * 100));

	byte middle_ry_low = lowByte(static_cast<int>(middle_coord[4] * 100));
	byte middle_ry_high = highByte(static_cast<int>(middle_coord[4] * 100));

	byte middle_rz_low = lowByte(static_cast<int>(middle_coord[5] * 100));
	byte middle_rz_high = highByte(static_cast<int>(middle_coord[5] * 100));

	// end_coord
	byte end_x_low = lowByte(static_cast<int>(end_coord[0] * 10));
	byte end_x_high = highByte(static_cast<int>(end_coord[0] * 10));

	byte end_y_low = lowByte(static_cast<int>(end_coord[1] * 10));
	byte end_y_high = highByte(static_cast<int>(end_coord[1] * 10));

	byte end_z_low = lowByte(static_cast<int>(end_coord[2] * 10));
	byte end_z_high = highByte(static_cast<int>(end_coord[2] * 10));

	byte end_rx_low = lowByte(static_cast<int>(end_coord[3] * 100));
	byte end_rx_high = highByte(static_cast<int>(end_coord[3] * 100));

	byte end_ry_low = lowByte(static_cast<int>(end_coord[4] * 100));
	byte end_ry_high = highByte(static_cast<int>(end_coord[4] * 100));

	byte end_rz_low = lowByte(static_cast<int>(end_coord[5] * 100));
	byte end_rz_high = highByte(static_cast<int>(end_coord[5] * 100));

	Serial2.write(header);
	Serial2.write(header);
	Serial2.write(MOVEC_COORDS_LEN);
	Serial2.write(MOVEC_COORDS);
	Serial2.write(middle_x_high);
	Serial2.write(middle_x_low);
	Serial2.write(middle_y_high);
	Serial2.write(middle_y_low);
	Serial2.write(middle_z_high);
	Serial2.write(middle_z_low);
	Serial2.write(middle_rx_high);
	Serial2.write(middle_rx_low);
	Serial2.write(middle_ry_high);
	Serial2.write(middle_ry_low);
	Serial2.write(middle_rz_high);
	Serial2.write(middle_rz_low);
	Serial2.write(end_x_high);
	Serial2.write(end_x_low);
	Serial2.write(end_y_high);
	Serial2.write(end_y_low);
	Serial2.write(end_z_high);
	Serial2.write(end_z_low);
	Serial2.write(end_rx_high);
	Serial2.write(end_rx_low);
	Serial2.write(end_ry_high);
	Serial2.write(end_ry_low);
	Serial2.write(end_rz_high);
	Serial2.write(end_rz_low);
	Serial2.write(footer);
}