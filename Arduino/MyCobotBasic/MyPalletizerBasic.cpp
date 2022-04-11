/*
 * MyCobotBasic.h
 * Elephant Robotics,mypalletizer260 robot arm bottom firmware interface layer program
 * data: 2020/11/20
 * author: Elephant Robotics
 */
#include "MyPalletizerBasic.h"

MyPalletizerBasic::MyPalletizerBasic(HardwareSerial *hw_serial)
{
    this->hw_serial = hw_serial;
    for (auto &val : error_angles)
        val = -1000.0;
    for (auto &val : error_coords)
        val = -1000.0;

    /*for (auto val : printList)
        messages_map.insert(val);*/
}

void MyPalletizerBasic::setup()
{
#if defined Mycobot_M5
    delay(500);
    M5.begin(true, false, true);
    M5.Power.begin();
    dacWrite(25, 0);  // disable mic
    delay(500);
#endif
}


bool MyPalletizerBasic::checkHeader()
{
    byte bDat;
    byte bBuf[2] = {0, 0};
    byte Cnt = 0;

    while (1) {
        if (!readSerial(&bDat, 1)) {
            Serial.println("can't get serial data");
            return 0;
        }
        bBuf[1] = bBuf[0];
        bBuf[0] = bDat;

        if (bBuf[0] == header && bBuf[1] == header) {
            break;
        }
        Cnt++;
        if (Cnt > 30) {
            return 0;
        }
    }
    return 1;
}


int MyPalletizerBasic::readSerial(unsigned char *nDat, int nLen)
{
    int Size = 0;
    int rec_data;
    unsigned long t_begin = millis();
    unsigned long t_use;

    while (1) {
        rec_data = hw_serial->read();
        // check data validation
        if (rec_data != IORecWrong) {
            if (nDat) {
                nDat[Size] = rec_data;
            }
            Size ++;
            t_begin = millis();
        }
        // check len
        if (Size >= nLen) {
            break;
        }
        // check time out
        t_use = millis() - t_begin;
        if (t_use > IO_TimeOut) {
            break;
        }
    }
    return Size;

}


void MyPalletizerBasic::rFlushSerial()
{
    while (hw_serial->read() != -1)
        ;
}


void MyPalletizerBasic::powerOn()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(POWER_ON_LEN);
    hw_serial->write(POWER_ON);
    hw_serial->write(footer);
    delay(WRITE_SERVO_GAP);
}

void MyPalletizerBasic::powerOff()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(POWER_OFF_LEN);
    hw_serial->write(POWER_OFF);
    hw_serial->write(footer);
    delay(WRITE_SERVO_GAP);
}

bool MyPalletizerBasic::isPoweredOn()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(IS_POWERED_ON_LEN);
    hw_serial->write(IS_POWERED_ON);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pPowerState = nullptr;
    bool powerState;

    while (true) {
        if (millis() - t_begin > 120)
            break;
        Serial.println("readData...........");
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pPowerState = (bool *)tempPtr;
            powerState = *pPowerState;
            delete pPowerState;
            return powerState;
        }
    }
    return false;
}
int MyPalletizerBasic::getAtomVersion()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_SYSTEM_VERSION_LEN);
    hw_serial->write(GET_SYSTEM_VERSION);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pReturnVersion = nullptr;
    int returnVersion;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pReturnVersion = (int *)tempPtr;
            returnVersion = *pReturnVersion;
            delete pReturnVersion;
            return returnVersion;
        }
    }

}
void *MyPalletizerBasic::readData()
{
    rFlushSerial();
    if (!checkHeader())
        return nullptr;
    byte data_len[1];
    byte r_data_3[3], r_data_4[4], r_data_10[10];

    if (readSerial(data_len, 1) != 1)
        return nullptr;
#if defined MyCobot_M5
    Serial.printf("datalen is %d", data_len[0]);
#endif
    switch (static_cast<int>(data_len[0])) {
        case 3:
            readSerial(r_data_3, 3);
#if defined MyCobot_M5
            Serial.printf("cmd is %d", r_data_3[0]);
#endif
            switch (int(r_data_3[0])) {
                case IS_IN_POSITION: {
                    int *pInt = new int;
                    *pInt = r_data_3[1];
                    return pInt;
                }

                case CHECK_RUNNING: {
                    bool *prunning_state = new bool;
                    *prunning_state = bool(r_data_3[1]);
                    return prunning_state;
                }

                case GET_SPEED: {
                    int *pSpeed = new int;
                    *pSpeed = r_data_3[1];
                    return pSpeed;
                }

                case IS_ALL_SERVO_ENABLED: {
                    bool *pServoState = new bool;
                    *pServoState = bool(r_data_3[1]);
                    return pServoState;
                }
                case IS_POWERED_ON: {
                    bool *pPowerState = new bool;
                    *pPowerState = bool(r_data_3[1]);
                    return pPowerState;
                }
                case GET_SERVO_DATA: {
                    byte *pServoData = new byte;
                    *pServoData = r_data_3[1];
                    return pServoData;
                }
                case GET_REF_FRAME: {
                    RFType *pRftype = new RFType;
                    *pRftype = RFType(r_data_3[1]);
                    return pRftype;
                }
                case GET_MOVEMENT_TYPE: {
                    MovementType *pMovementType = new MovementType;
                    *pMovementType = MovementType(r_data_3[1]);
                    return pMovementType;
                }
                case GET_END_TYPE: {
                    EndType *pEndType = new EndType;
                    *pEndType = EndType(r_data_3[1]);
                    return pEndType;
                }
                case ROBOTIC_MESSAGE: {
                    byte *pMessage = new byte;
                    *pMessage = r_data_3[1];
                    return pMessage;
                }

                case GET_DIGITAL_INPUT: {
                    int *returnValue = new int;
                    *returnValue = r_data_3[1];
                    return returnValue;
                }

                case IS_GRIPPER_MOVING: {
                    int *pState = new int;
                    *pState = r_data_3[1];
                    return pState;
                }
                case GET_GRIPPER_VALUE: {
                    int *pValue = new int;
                    *pValue = r_data_3[1];
                    return pValue;
                }
                case GET_ROBOT_VERSION: {
                    int *pVersion = new int;
                    *pVersion = r_data_3[1];
                    return pVersion;
                }
                case GET_SYSTEM_VERSION: {
                    int *pVersion = new int;
                    *pVersion = r_data_3[1];
                    return pVersion;
                }
            }

        case 4:
            readSerial(r_data_4, 4);
            switch (int(r_data_4[0])) {
                case IS_SERVO_ENABLED: {
                    bool *pServoState = new bool;
                    *pServoState = bool(r_data_4[2]);
                    return pServoState;
                }

                case GET_FEED_OVERRIDE: {
                    float *pfeed_override = new float;
                    byte feed_override_high = r_data_4[1];
                    byte feed_override_low = r_data_4[2];
                    float temp = 0.0;
                    temp = feed_override_low + feed_override_high * 256;
                    *pfeed_override = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return pfeed_override;
                }

                case GET_ACCELERATION: {
                    float *pAcceleration = new float;
                    byte acceleration_high = r_data_4[1];
                    byte acceleration_low = r_data_4[2];
                    float temp = 0.0;
                    temp = acceleration_low + acceleration_high * 256;
                    *pAcceleration = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return pAcceleration;
                }
                case GET_JOINT_MIN: {
                    float *pJointMin = new float;
                    byte jointMin_high = r_data_4[1];
                    byte jointMin_low = r_data_4[2];
                    float temp = 0.0;
                    temp = jointMin_low + jointMin_high * 256;
                    *pJointMin = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return pJointMin;
                }
                case GET_JOINT_MAX: {
                    float *pJointMax = new float;
                    byte jointMax_high = r_data_4[1];
                    byte jointMax_low = r_data_4[2];
                    float temp = 0.0;
                    temp = jointMax_low + jointMax_high * 256;
                    *pJointMax = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return pJointMax;
                }
                case GET_ENCODER: {
                    int *pEncoder = new int;
                    byte encoder_high = r_data_4[1];
                    byte encoder_low = r_data_4[2];
                    *pEncoder = encoder_low + encoder_high * 256;
                    return pEncoder;
                }

            }

        case 10:
            readSerial(r_data_10, 10);
            switch (int(r_data_10[0])) {
                case GET_ANGLES: {
                    byte angle_1_high = r_data_10[1];
                    byte angle_1_low = r_data_10[2];

                    byte angle_2_high = r_data_10[3];
                    byte angle_2_low = r_data_10[4];

                    byte angle_3_high = r_data_10[5];
                    byte angle_3_low = r_data_10[6];

                    byte angle_4_high = r_data_10[7];
                    byte angle_4_low = r_data_10[8];

                    MyPalletizerAngles *pAngles = new MyPalletizerAngles;
                    float temp = 0.0;
                    temp = angle_1_low + angle_1_high * 256;
                    pAngles->at(0) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_2_low + angle_2_high * 256;
                    pAngles->at(1) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_3_low + angle_3_high * 256;
                    pAngles->at(2) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_4_low + angle_4_high * 256;
                    pAngles->at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;

                    return pAngles;
                }

                case GET_COORDS: {
                    byte x_high = r_data_10[1];
                    byte x_low = r_data_10[2];

                    byte y_high = r_data_10[3];
                    byte y_low = r_data_10[4];

                    byte z_high = r_data_10[5];
                    byte z_low = r_data_10[6];

                    byte rx_high = r_data_10[7];
                    byte rx_low = r_data_10[8];

                    MyPalletizerCoords *pCoords = new MyPalletizerCoords;
                    float temp = 0.0;

                    temp = x_low + x_high * 256;
                    pCoords->at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = y_low + y_high * 256;
                    pCoords->at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = z_low + z_high * 256;
                    pCoords->at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = rx_low + rx_high * 256;
                    pCoords->at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;

                    return pCoords;
                }
                case GET_ENCODERS: {
                    byte encode_1_high = r_data_10[1];
                    byte encode_1_low = r_data_10[2];

                    byte encode_2_high = r_data_10[3];
                    byte encode_2_low = r_data_10[4];

                    byte encode_3_high = r_data_10[5];
                    byte encode_3_low = r_data_10[6];

                    byte encode_4_high = r_data_10[7];
                    byte encode_4_low = r_data_10[8];

                    MyPalletizerEncoders *pEncoders = new MyPalletizerEncoders;
                    pEncoders->at(0) = encode_1_low + encode_1_high * 256;
                    pEncoders->at(1) = encode_2_low + encode_2_high * 256;
                    pEncoders->at(2) = encode_3_low + encode_3_high * 256;
                    pEncoders->at(3) = encode_4_low + encode_4_high * 256;
                    return pEncoders;
                }

            }



    }

    return nullptr;
}

MyPalletizerAngles MyPalletizerBasic::getAngles()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_ANGLES_LEN);
    hw_serial->write(GET_ANGLES);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MyPalletizerAngles *pAngles = nullptr;
    MyPalletizerAngles angles;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pAngles = (MyPalletizerAngles *)tempPtr;
            for (int i = 0; i < 4; ++i)
                angles[i] = pAngles->at(i);
            delete pAngles;
            return angles;
        }
    }
    return error_angles;
}


void MyPalletizerBasic::writeAngle(int joint, float value, int speed)
{
    byte joint_number = byte(joint);
    byte angle_low = lowByte(static_cast<int>(value * 100));
    byte angle_high = highByte(static_cast<int>(value * 100));

    byte sp = speed;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(WRITE_ANGLE_LEN);
    hw_serial->write(WRITE_ANGLE);
    hw_serial->write(joint_number);
    hw_serial->write(angle_high);
    hw_serial->write(angle_low);
    hw_serial->write(sp);
    hw_serial->write(footer);

    delay(WRITE_SERVO_GAP);
}


void MyPalletizerBasic::writeAngles(MyPalletizerAngles angles, int speed)
{
    byte angle_1_low = lowByte(static_cast<int>(angles[0] * 100));
    byte angle_1_high = highByte(static_cast<int>(angles[0] * 100));

    byte angle_2_low = lowByte(static_cast<int>(angles[1] * 100));
    byte angle_2_high = highByte(static_cast<int>(angles[1] * 100));

    byte angle_3_low = lowByte(static_cast<int>(angles[2] * 100));
    byte angle_3_high = highByte(static_cast<int>(angles[2] * 100));

    byte angle_4_low = lowByte(static_cast<int>(angles[3] * 100));
    byte angle_4_high = highByte(static_cast<int>(angles[3] * 100));

    byte sp = speed;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(WRITE_ANDLES_LEN);
    hw_serial->write(WRITE_ANGLES);

    hw_serial->write(angle_1_high);
    hw_serial->write(angle_1_low);
    hw_serial->write(angle_2_high);
    hw_serial->write(angle_2_low);
    hw_serial->write(angle_3_high);
    hw_serial->write(angle_3_low);
    hw_serial->write(angle_4_high);
    hw_serial->write(angle_4_low);

    hw_serial->write(sp);

    hw_serial->write(footer);
    delay(WRITE_SERVO_GAP);
}


MyPalletizerCoords MyPalletizerBasic::getCoords()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_COORDS_LEN);
    hw_serial->write(GET_COORDS);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MyPalletizerCoords *pCoords = nullptr;
    MyPalletizerCoords tempCoords;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pCoords = (MyPalletizerCoords *)tempPtr;
            for (int i = 0; i < 4; ++i)
                tempCoords[i] = pCoords->at(i);
            delete pCoords;
            return tempCoords;
        }
    }
    return error_coords;
}


void MyPalletizerBasic::writeCoord(MyPalletizerAxis axis, float value,
                                   int speed)
{
    byte axis_number = byte(axis);
    int temp_value = 0;
    if (axis == MyPalletizerAxis::P_X || axis == MyPalletizerAxis::P_Y
            || axis == MyPalletizerAxis::P_Z)
        temp_value = value * 10;
    else
        temp_value = value * 100;
    byte value_high = highByte(temp_value);
    byte value_low = lowByte(temp_value);

    byte sp = byte(speed);

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(WRITE_COORD_LEN);
    hw_serial->write(WRITE_COORD);
    hw_serial->write(axis_number);
    hw_serial->write(value_high);
    hw_serial->write(value_low);
    hw_serial->write(sp);
    hw_serial->write(footer);
    //delay(WRITE_SERVO_GAP);

    //receiveMessages();
}

void MyPalletizerBasic::writeCoords(MyPalletizerCoords coord, int speed)
{
    byte coord_x_low = lowByte(static_cast<int>(coord[0] * 10));
    byte coord_x_high = highByte(static_cast<int>(coord[0] * 10));

    byte coord_y_low = lowByte(static_cast<int>(coord[1] * 10));
    byte coord_y_high = highByte(static_cast<int>(coord[1] * 10));

    byte coord_z_low = lowByte(static_cast<int>(coord[2] * 10));
    byte coord_z_high = highByte(static_cast<int>(coord[2] * 10));

    byte coord_theta_low = lowByte(static_cast<int>(coord[3] * 100));
    byte coord_theta_high = highByte(static_cast<int>(coord[3] * 100));

    byte sp = speed;
    byte mode = 1;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(WRITE_COORDS_LEN);
    hw_serial->write(WRITE_COORDS);
    hw_serial->write(coord_x_high);
    hw_serial->write(coord_x_low);
    hw_serial->write(coord_y_high);
    hw_serial->write(coord_y_low);
    hw_serial->write(coord_z_high);
    hw_serial->write(coord_z_low);
    hw_serial->write(coord_theta_high);
    hw_serial->write(coord_theta_low);
    hw_serial->write(sp);
    hw_serial->write(mode);
    hw_serial->write(footer);
    //delay(WRITE_SERVO_GAP);

    //receiveMessages();
}

int MyPalletizerBasic::isInPosition(MyPalletizerCoords coord, bool is_linear)
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

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(IS_IN_POSITION_LEN);
    hw_serial->write(IS_IN_POSITION);
    hw_serial->write(coord_x_high);
    hw_serial->write(coord_x_low);
    hw_serial->write(coord_y_high);
    hw_serial->write(coord_y_low);
    hw_serial->write(coord_z_high);
    hw_serial->write(coord_z_low);
    hw_serial->write(coord_rx_high);
    hw_serial->write(coord_rx_low);
    hw_serial->write(coord_ry_high);
    hw_serial->write(coord_ry_low);
    hw_serial->write(coord_rz_high);
    hw_serial->write(coord_rz_low);
    hw_serial->write(type);
    hw_serial->write(footer);


    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pIsInposition = nullptr;
    int isInposition;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pIsInposition = (int *)tempPtr;
            isInposition = *pIsInposition;
            delete pIsInposition;
            return isInposition;
        }
    }
    return -1;
}

bool MyPalletizerBasic::checkRunning()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(CHECK_RUNNING_LEN);
    hw_serial->write(CHECK_RUNNING);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *prunning_state = nullptr;
    bool running_state;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            prunning_state = (bool *)tempPtr;
            running_state = *prunning_state;
            delete prunning_state;
            return running_state;
        }
    }
    return false;
}


void MyPalletizerBasic::jogAngle(int joint, int direction, int speed)
{
    byte joint_number = joint;
    byte di = direction;
    byte sp = speed;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(JOG_ANGLE_LEN);
    hw_serial->write(JOG_ANGLE);
    hw_serial->write(joint_number);
    hw_serial->write(di);
    hw_serial->write(sp);
    hw_serial->write(footer);
    delay(WRITE_SERVO_GAP);
}

void MyPalletizerBasic::jogCoord(MyPalletizerAxis axis, int direction,
                                 int speed)
{
    byte axis_number = axis + 1;
    byte di = direction;
    byte sp = speed;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(JOG_COORD_LEN);
    hw_serial->write(JOG_COORD);
    hw_serial->write(axis_number);
    hw_serial->write(di);
    hw_serial->write(sp);
    hw_serial->write(footer);
    delay(WRITE_SERVO_GAP);
}

void MyPalletizerBasic::jogStop()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(JOG_STOP_LEN);
    hw_serial->write(JOG_STOP);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setEncoder(int joint, int encoder)
{
    byte joint_number = joint;
    byte encoder_high = highByte(encoder);
    byte encoder_low = lowByte(encoder);

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_ENCODER_LEN);
    hw_serial->write(SET_ENCODER);
    hw_serial->write(joint_number);
    hw_serial->write(encoder_high);
    hw_serial->write(encoder_low);
    hw_serial->write(footer);
}

int MyPalletizerBasic::getEncoder(int joint)
{
    byte joint_number = joint;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_ENCODER_LEN);
    hw_serial->write(GET_ENCODER);
    hw_serial->write(joint_number);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pEncoder = nullptr;
    int encoder;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pEncoder = (int *)tempPtr;
            encoder = *pEncoder;
            delete pEncoder;
            return encoder;
        }
    }

    return -1;
}

MyPalletizerEncoders MyPalletizerBasic::getEncoders()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_ENCODERS_LEN);
    hw_serial->write(GET_ENCODERS);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MyPalletizerEncoders *pEncoders = nullptr;
    MyPalletizerEncoders encoders;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pEncoders = (MyPalletizerEncoders *)tempPtr;
            for (int i = 0; i < 4; ++i)
                encoders[i] = pEncoders->at(i);
            delete pEncoders;
            return encoders;
        }
    }
    return error_encoders;
}


void MyPalletizerBasic::setEncoders(MyPalletizerEncoders angleEncoders,
                                    int speed)
{
    byte angle_1_high = highByte(static_cast<int>(angleEncoders[0]));
    byte angle_1_low = lowByte(static_cast<int>(angleEncoders[0]));
    byte angle_2_high = highByte(static_cast<int>(angleEncoders[1]));
    byte angle_2_low = lowByte(static_cast<int>(angleEncoders[1]));
    byte angle_3_high = highByte(static_cast<int>(angleEncoders[2]));
    byte angle_3_low = lowByte(static_cast<int>(angleEncoders[2]));
    byte angle_4_high = highByte(static_cast<int>(angleEncoders[3]));
    byte angle_4_low = lowByte(static_cast<int>(angleEncoders[3]));
    byte sp = speed;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_ENCODERS_LEN);
    hw_serial->write(SET_ENCODERS);
    hw_serial->write(angle_1_high);
    hw_serial->write(angle_1_low);
    hw_serial->write(angle_2_high);
    hw_serial->write(angle_2_low);
    hw_serial->write(angle_3_high);
    hw_serial->write(angle_3_low);
    hw_serial->write(angle_4_high);
    hw_serial->write(angle_4_low);
    hw_serial->write(sp);
    hw_serial->write(footer);
}

int MyPalletizerBasic::getSpeed()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_SPEED_LEN);
    hw_serial->write(GET_SPEED);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pSpeed = nullptr;
    int speed;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pSpeed = (int *)tempPtr;
            speed = *pSpeed;
            delete pSpeed;
            return speed;
        }
    }

    return -1;
}

void MyPalletizerBasic::setSpeed(int percentage)
{
    byte speed = percentage;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_SPEED_LEN);
    hw_serial->write(SET_SPEED);
    hw_serial->write(speed);
    hw_serial->write(footer);
}

float MyPalletizerBasic::getFeedOverride()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_FEED_OVERRIDE_LEN);
    hw_serial->write(GET_FEED_OVERRIDE);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pfeed_override = nullptr;
    float feed_override;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pfeed_override = (float *)tempPtr;
            feed_override = *pfeed_override;
            delete pfeed_override;
            return feed_override;
        }
    }

    return -1.0;
}

void MyPalletizerBasic::sendFeedOverride(float feed_override)
{
    byte feed_override_high = highByte(static_cast<int>(feed_override * 10));
    byte feed_override_low = lowByte(static_cast<int>(feed_override * 10));

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SEND_OVERRIDE_LEN);
    hw_serial->write(SEND_OVERRIDE);
    hw_serial->write(feed_override_high);
    hw_serial->write(feed_override_low);
    hw_serial->write(footer);
}

float MyPalletizerBasic::getAcceleration()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_ACCELERATION_LEN);
    hw_serial->write(GET_ACCELERATION);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pAcceleration = nullptr;
    float acceleration;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pAcceleration = (float *)tempPtr;
            acceleration = *pAcceleration;
            delete pAcceleration;
            return acceleration;
        }
    }

    return -1.0;
}

void MyPalletizerBasic::setAcceleration(float acceleration)
{
    byte acceleration_high = highByte(static_cast<int>(acceleration * 10));
    byte acceleration_low = lowByte(static_cast<int>(acceleration * 10));

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_ACCELERATION_LEN);
    hw_serial->write(SET_ACCELERATION);
    hw_serial->write(acceleration_high);
    hw_serial->write(acceleration_low);
    hw_serial->write(footer);
}

float MyPalletizerBasic::getJointMin(int joint)
{
    byte joint_number = joint;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_JOINT_MIN_LEN);
    hw_serial->write(GET_JOINT_MIN);
    hw_serial->write(joint_number);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pJointMin = nullptr;
    float jointMin;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pJointMin = (float *)tempPtr;
            jointMin = *pJointMin;
            delete pJointMin;
            return jointMin;
        }
    }

    return -5.0;
}

float MyPalletizerBasic::getJointMax(int joint)
{
    byte joint_number = joint;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_JOINT_MAX_LEN);
    hw_serial->write(GET_JOINT_MAX);
    hw_serial->write(joint_number);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pJointMax = nullptr;
    float jointMax;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pJointMax = (float *)tempPtr;
            jointMax = *pJointMax;
            delete pJointMax;
            return jointMax;
        }
    }

    return -5.0;
}

void MyPalletizerBasic::setJointMin(int joint, float angle)
{
    byte joint_number = joint;
    byte angle_low = lowByte(static_cast<int>(angle * 10));
    byte angle_high = highByte(static_cast<int>(angle * 10));
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_JOINT_MIN_LEN);
    hw_serial->write(SET_JOINT_MIN);
    hw_serial->write(joint_number);
    hw_serial->write(angle_high);
    hw_serial->write(angle_low);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setJointMax(int joint, float angle)
{
    byte joint_number = joint;
    byte angle_low = lowByte(static_cast<int>(angle * 10));
    byte angle_high = highByte(static_cast<int>(angle * 10));
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_JOINT_MAX_LEN);
    hw_serial->write(SET_JOINT_MAX);
    hw_serial->write(joint_number);
    hw_serial->write(angle_high);
    hw_serial->write(angle_low);
    hw_serial->write(footer);
}

bool MyPalletizerBasic::isServoEnabled(int joint)
{
    byte joint_number = joint;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(IS_SERVO_ENABLED_LEN);
    hw_serial->write(IS_SERVO_ENABLED);
    hw_serial->write(joint_number);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pServoState = nullptr;
    bool servoState;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pServoState = (bool *)tempPtr;
            servoState = *pServoState;
            delete pServoState;
            return servoState;
        }
    }
    return false;
}

bool MyPalletizerBasic::isAllServoEnabled()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(IS_ALL_SERVO_ENABLED_LEN);
    hw_serial->write(IS_ALL_SERVO_ENABLED);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pServoState = nullptr;
    bool servoState;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pServoState = (bool *)tempPtr;
            servoState = *pServoState;
            delete pServoState;
            return servoState;
        }
    }
    return false;
}

byte MyPalletizerBasic::getServoData(int joint, byte data_id)
{
    byte joint_number = joint;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_SERVO_DATA_LEN);
    hw_serial->write(GET_SERVO_DATA);
    hw_serial->write(joint_number);
    hw_serial->write(data_id);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    byte *pServoData = nullptr;
    byte servoData;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pServoData = (byte *)tempPtr;
            servoData = *pServoData;
            delete pServoData;
            return servoData;
        }
    }

    return -1.0;
}

void MyPalletizerBasic::setServoCalibration(int joint)
{
    byte joint_number = joint;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_SERVO_CALIBRATION_LEN);
    hw_serial->write(SET_SERVO_CALIBRATION);
    hw_serial->write(joint_number);
    hw_serial->write(footer);
}


void MyPalletizerBasic::setPinMode(byte pin_no, byte pin_mode)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_PIN_MODE_LEN);
    hw_serial->write(SET_PIN_MODE);
    hw_serial->write(pin_no);
    hw_serial->write(pin_mode);
    hw_serial->write(footer);
}

void MyPalletizerBasic::pause()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(PROGRAM_PAUSE_LEN);
    hw_serial->write(PROGRAM_PAUSE);
    hw_serial->write(footer);
}

void MyPalletizerBasic::resume()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(PROGRAM_RESUME_LEN);
    hw_serial->write(PROGRAM_RESUME);
    hw_serial->write(footer);
}

void MyPalletizerBasic::stop()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(TASK_STOP_LEN);
    hw_serial->write(TASK_STOP);
    hw_serial->write(footer);
}


void MyPalletizerBasic::setLEDRGB(byte r, byte g, byte b)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_LED_LEN);
    hw_serial->write(SET_LED);
    hw_serial->write(r);
    hw_serial->write(g);
    hw_serial->write(b);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setGripper(int data)
{
    byte gripper_data = data;
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_GRIPPER_STATE_LEN);
    hw_serial->write(SET_GRIPPER_STATE);
    hw_serial->write(gripper_data);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setServoData(byte servo_no, byte servo_state,
                                     byte servo_data)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_SERVO_DATA_LEN);
    hw_serial->write(SET_SERVO_DATA);

    hw_serial->write(servo_no);
    hw_serial->write(servo_state);
    hw_serial->write(servo_data);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setFreeMove()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_FREE_MOVE_LEN);
    hw_serial->write(SET_FREE_MOVE);
    hw_serial->write(footer);
}

/*
void MyPalletizerBasic::receiveMessages()
{
    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    byte *pMessage = nullptr;
    int message;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pMessage = (byte *)tempPtr;
            message = static_cast<int>(*pMessage);
            delete pMessage;

            /*std::map<int, std::string>::iterator iter = messages_map.find(message);
            char *pChar = (char *)iter->second.c_str();
            if (iter != messages_map.end())
                Serial.println(pChar);*//*
        }
    }

}*/

void MyPalletizerBasic::setMovementType(MovementType movement_type)
{
    byte mt = movement_type;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_MOVEMENT_TYPE_LEN);
    hw_serial->write(SET_MOVEMENT_TYPE);
    hw_serial->write(mt);
    hw_serial->write(footer);
}

MovementType MyPalletizerBasic::getMovementType()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_MOVEMENT_TYPE_LEN);
    hw_serial->write(GET_MOVEMENT_TYPE);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MovementType *pMovementType = nullptr;
    MovementType movement_type;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pMovementType = (MovementType *)tempPtr;
            movement_type = *pMovementType;
            delete pMovementType;
            return movement_type;
        }
    }

    return ERROR_MOVEMENT;
}

void MyPalletizerBasic::setToolReference(MyPalletizerCoords coord)
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

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_TOOL_REF_LEN);
    hw_serial->write(SET_TOOL_REF);
    hw_serial->write(coord_x_high);
    hw_serial->write(coord_x_low);
    hw_serial->write(coord_y_high);
    hw_serial->write(coord_y_low);
    hw_serial->write(coord_z_high);
    hw_serial->write(coord_z_low);
    hw_serial->write(coord_rx_high);
    hw_serial->write(coord_rx_low);
    hw_serial->write(coord_ry_high);
    hw_serial->write(coord_ry_low);
    hw_serial->write(coord_rz_high);
    hw_serial->write(coord_rz_low);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setWorldReference(MyPalletizerCoords coord)
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

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_WORLD_REF_LEN);
    hw_serial->write(SET_WORLD_REF);
    hw_serial->write(coord_x_high);
    hw_serial->write(coord_x_low);
    hw_serial->write(coord_y_high);
    hw_serial->write(coord_y_low);
    hw_serial->write(coord_z_high);
    hw_serial->write(coord_z_low);
    hw_serial->write(coord_rx_high);
    hw_serial->write(coord_rx_low);
    hw_serial->write(coord_ry_high);
    hw_serial->write(coord_ry_low);
    hw_serial->write(coord_rz_high);
    hw_serial->write(coord_rz_low);
    hw_serial->write(footer);
}

MyPalletizerCoords MyPalletizerBasic::getToolReference()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_TOOL_REF_LEN);
    hw_serial->write(GET_TOOL_REF);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MyPalletizerCoords *pCoords = nullptr;
    MyPalletizerCoords tempCoords;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pCoords = (MyPalletizerCoords *)tempPtr;
            for (int i = 0; i < 4; ++i)
                tempCoords[i] = pCoords->at(i);
            delete pCoords;
            return tempCoords;
        }
    }
    return error_coords;
}

MyPalletizerCoords MyPalletizerBasic::getWorldReference()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_WORLD_REF_LEN);
    hw_serial->write(GET_WORLD_REF);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MyPalletizerCoords *pCoords = nullptr;
    MyPalletizerCoords tempCoords;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pCoords = (MyPalletizerCoords *)tempPtr;
            for (int i = 0; i < 4; ++i)
                tempCoords[i] = pCoords->at(i);
            delete pCoords;
            return tempCoords;
        }
    }
    return error_coords;
}

void MyPalletizerBasic::setReferenceFrame(RFType rftype)
{
    byte rt = rftype;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_REF_FRAME_LEN);
    hw_serial->write(SET_REF_FRAME);
    hw_serial->write(rt);
    hw_serial->write(footer);
}

RFType MyPalletizerBasic::getReferenceFrame()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_REF_FRAME_LEN);
    hw_serial->write(GET_REF_FRAME);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    RFType *pRFType = nullptr;
    RFType rftype;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pRFType = (RFType *)tempPtr;
            rftype = *pRFType;
            delete pRFType;
            return rftype;
        }
    }

    return ERROR_RF;
}

void MyPalletizerBasic::setEndType(EndType end_type)
{
    byte et = end_type;

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_END_TYPE_LEN);
    hw_serial->write(SET_END_TYPE);
    hw_serial->write(et);
    hw_serial->write(footer);
}

EndType MyPalletizerBasic::getEndType()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_END_TYPE_LEN);
    hw_serial->write(GET_END_TYPE);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    EndType *pEndType = nullptr;
    EndType end_type;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pEndType = (EndType *)tempPtr;
            end_type = *pEndType;
            delete pEndType;
            return end_type;
        }
    }

    return ERROR_END;
}

void MyPalletizerBasic::setDigitalOutput(byte pin_no, byte pin_state)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_DIGITAL_OUTPUT_LEN);
    hw_serial->write(SET_DIGITAL_OUTPUT);
    hw_serial->write(pin_no);
    hw_serial->write(pin_state);
    hw_serial->write(footer);
}

int MyPalletizerBasic::getDigitalInput(byte pin_no)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_DIGITAL_INPUT_LEN);
    hw_serial->write(GET_DIGITAL_INPUT);
    hw_serial->write(pin_no);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pReturnValue = nullptr;
    int returnValue;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pReturnValue = (int *)tempPtr;
            returnValue = *pReturnValue;
            delete pReturnValue;
            return returnValue;
        }
    }

    return -1;
}

/*
void MyPalletizerBasic::setPWMMode(int freq, byte pin_no, byte channel)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_PWM_MODE_LEN);
    hw_serial->write(SET_PWM_MODE);


    byte freq_high = highByte(freq);
    byte freq_low = lowByte(freq);

    hw_serial->write(freq_high);
    hw_serial->write(freqa_low);

    hw_serial->write(pin_no);
    hw_serial->write(channel);
    hw_serial->write(footer);
}*/

void MyPalletizerBasic::setPWMOutput(byte pin_no, int freq,  byte pin_write)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_PWM_OUTPUT_LEN);
    hw_serial->write(SET_PWM_OUTPUT);
    hw_serial->write(pin_no);

    byte freq_high = highByte(freq);
    byte freq_low = lowByte(freq);

    hw_serial->write(freq_high);
    hw_serial->write(freq_low);


    hw_serial->write(pin_write);
    hw_serial->write(footer);
}

void MyPalletizerBasic::releaseServo(byte servo_no)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(RELEASE_SERVO_LEN);
    hw_serial->write(RELEASE_SERVO);
    hw_serial->write(servo_no);
    hw_serial->write(footer);
}

void MyPalletizerBasic::focusServo(byte servo_no)
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(FOCUS_SERVO_LEN);
    hw_serial->write(FOCUS_SERVO);
    hw_serial->write(servo_no);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setGripperState(byte mode, int sp)
{
    if (sp > 100) {
        sp = 100;
    }
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_GRIPPER_STATE_LEN);
    hw_serial->write(SET_GRIPPER_STATE);
    hw_serial->write(mode);
    hw_serial->write(sp);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setGripperValue(int data, int sp)
{
    if (data > 100) {
        data = 100;
    }
    if (sp > 100) {
        sp = 100;
    }
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_GRIPPER_VALUE_LEN);
    hw_serial->write(SET_GRIPPER_VALUE);
    hw_serial->write(data);
    hw_serial->write(sp);
    hw_serial->write(footer);
}

void MyPalletizerBasic::setGripperIni()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(SET_GRIPPER_INI_LEN);
    hw_serial->write(SET_GRIPPER_INI);
    hw_serial->write(footer);
}

int MyPalletizerBasic::getGripperValue()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(GET_GRIPPER_VALUE_LEN);
    hw_serial->write(GET_GRIPPER_VALUE);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pReturnValue = nullptr;
    int returnValue;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pReturnValue = (int *)tempPtr;
            returnValue = *pReturnValue;
            delete pReturnValue;
            return returnValue;
        }
    }

    return -1;
}

bool MyPalletizerBasic::isGripperMoving()
{
    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(IS_GRIPPER_MOVING_LEN);
    hw_serial->write(IS_GRIPPER_MOVING);
    hw_serial->write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pState = nullptr;
    bool state;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        tempPtr = readData();
        if (tempPtr == nullptr)
            continue;
        else {
            pState = (bool *)tempPtr;
            state = *pState;
            delete pState;
            return state;
        }
    }
    return false;
}


void MyPalletizerBasic::moveCCoords(MyPalletizerCoords end_coord, int radius,
                                    int direction, int speed) //direction:  0-clockwise,1-anticlockwise
{
    // end_coord
    byte end_x_low = lowByte(static_cast<int>(end_coord[0] * 10));
    byte end_x_high = highByte(static_cast<int>(end_coord[0] * 10));

    byte end_y_low = lowByte(static_cast<int>(end_coord[1] * 10));
    byte end_y_high = highByte(static_cast<int>(end_coord[1] * 10));

    byte end_z_low = lowByte(static_cast<int>(end_coord[2] * 10));
    byte end_z_high = highByte(static_cast<int>(end_coord[2] * 10));

    byte end_theta_low = lowByte(static_cast<int>(end_coord[3] * 100));
    byte end_theta_high = highByte(static_cast<int>(end_coord[3] * 100));

    byte radius_low = lowByte(static_cast<int>(radius * 10));
    byte radius_high = highByte(static_cast<int>(radius * 10));

    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(MOVEC_COORDS_LEN);
    hw_serial->write(MOVEC_COORDS);

    hw_serial->write(end_x_high);
    hw_serial->write(end_x_low);
    hw_serial->write(end_y_high);
    hw_serial->write(end_y_low);
    hw_serial->write(end_z_high);
    hw_serial->write(end_z_low);
    hw_serial->write(end_theta_high);
    hw_serial->write(end_theta_low);

    hw_serial->write(radius_high);
    hw_serial->write(radius_low);
    hw_serial->write(direction);
    hw_serial->write(speed);

    hw_serial->write(footer);
}

void MyPalletizerBasic::moveCCoords(MyPalletizerCoords center_coord,
                                    int direction, int speed) //direction:  0-clockwise,1-anticlockwise
{
    // middle_coord
    byte center_x_low = lowByte(static_cast<int>(center_coord[0] * 10));
    byte center_x_high = highByte(static_cast<int>(center_coord[0] * 10));

    byte center_y_low = lowByte(static_cast<int>(center_coord[1] * 10));
    byte center_y_high = highByte(static_cast<int>(center_coord[1] * 10));

    byte center_z_low = lowByte(static_cast<int>(center_coord[2] * 10));
    byte center_z_high = highByte(static_cast<int>(center_coord[2] * 10));

    byte center_theta_low = lowByte(static_cast<int>(center_coord[3] * 100));
    byte center_theta_high = highByte(static_cast<int>(center_coord[3] * 100));



    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(MOVEC_COORDS_DEFAULT_LEN);
    hw_serial->write(MOVEC_COORDS_DEFAULT);
    hw_serial->write(center_x_high);
    hw_serial->write(center_x_low);
    hw_serial->write(center_y_high);
    hw_serial->write(center_y_low);
    hw_serial->write(center_z_high);
    hw_serial->write(center_z_low);
    hw_serial->write(center_theta_high);
    hw_serial->write(center_theta_low);
    hw_serial->write(direction);
    hw_serial->write(speed);
    hw_serial->write(footer);
}

void MyPalletizerBasic::moveLCoords(MyPalletizerCoords end_coord, int speed)
{
    // end_coord
    byte end_x_low = lowByte(static_cast<int>(end_coord[0] * 10));
    byte end_x_high = highByte(static_cast<int>(end_coord[0] * 10));

    byte end_y_low = lowByte(static_cast<int>(end_coord[1] * 10));
    byte end_y_high = highByte(static_cast<int>(end_coord[1] * 10));

    byte end_z_low = lowByte(static_cast<int>(end_coord[2] * 10));
    byte end_z_high = highByte(static_cast<int>(end_coord[2] * 10));

    byte end_theta_low = lowByte(static_cast<int>(end_coord[3] * 100));
    byte end_theta_high = highByte(static_cast<int>(end_coord[3] * 100));


    hw_serial->write(header);
    hw_serial->write(header);
    hw_serial->write(MOVEL_COORDS_LEN);
    hw_serial->write(MOVEL_COORDS);

    hw_serial->write(end_x_high);
    hw_serial->write(end_x_low);
    hw_serial->write(end_y_high);
    hw_serial->write(end_y_low);
    hw_serial->write(end_z_high);
    hw_serial->write(end_z_low);
    hw_serial->write(end_theta_high);
    hw_serial->write(end_theta_low);
    hw_serial->write(speed);
    hw_serial->write(footer);
}