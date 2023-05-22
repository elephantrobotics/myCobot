/*
 * MyCobotBasic.h
 * Elephant Robotics,280、320-m5 robot arm bottom firmware interface layer program
 * data: 2020/11/20
 * author: Elephant Robotics
 */

#include "MyCobotBasic.h"

MyCobotBasic::MyCobotBasic()
{
    for (auto &val : error_angles)
        val = -1000.0;
    for (auto &val : error_coords)
        val = -1000.0;
    for (auto &val : error_speeds)
        val = -10000.0;
    /*for (auto val : printList)
        messages_map.insert(val);*/

}

void MyCobotBasic::setup()
{
#if defined MyCobot_M5
    delay(500);
    M5.begin(true, false, true);
    M5.Power.begin();
    dacWrite(25, 0);  // disable mic
    delay(500);
#endif
    mycobot_serial.begin(BAUD_RATE);
}

int MyCobotBasic::readSerial(unsigned char *nDat, int& nLen)
{
    int Size = 0;
    bool flag = false;
    unsigned long t_begin = millis();
    unsigned char data[1024];

    delay(5);
    int index = 0, last_index = 0;
    t_begin = millis();
    while(millis() - t_begin < IO_TimeOut) {
        // Serial.println("start");
        delay(1); //Delay is required when there is a communication problem with the manipulator
        while (mycobot_serial.available() > 0) {
            // delay(1);
            data[index] = mycobot_serial.read();
            index++;
        }
        /*Serial.print("t_begin == ");
        Serial.println(t_begin);
        Serial.print("index == ");
        Serial.println(index);*/
        /*Serial.print("data == ");
        for (int j = last_index; j < index; j++) {
            Serial.print(data[j]);
            Serial.print("  ");
        }
        Serial.println();*/
        for (int i = last_index; i < index; i++) {
            /*Serial.print("data[i] == ");
            Serial.println(data[i]);*/
            if (!flag) {
                if (data[i] == header && data[i+1] == header) {
                    /*Serial.print("have fe fe  ");
                    Serial.println(i);*/
                    flag = true;
                    nLen = data[i+2];
                    /*Serial.print("  nLen  ");
                    Serial.print(nLen);*/
                    i += 1;
                    Size = 0;
                    continue;
                } 
            } else {
                nDat[Size] = data[i];
                //Serial.print(nDat[Size]);
                if (Size == nLen) {
                    //Serial.println("end");
                    break;
                }
            }
            Size++;
        }
        if (Size == nLen) {
            // Serial.println("end2");
            break;
        }
        last_index = index - 1;
    }
    // Serial.println("ttime out");
    return Size;

}


void MyCobotBasic::rFlushSerial()
{
    while (mycobot_serial.read() != -1)
        ;
}


void MyCobotBasic::powerOn()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(POWER_ON_LEN);
    mycobot_serial.write(POWER_ON);
    mycobot_serial.write(footer);
    delay(WRITE_SERVO_GAP);
}

void MyCobotBasic::powerOff()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(POWER_OFF_LEN);
    mycobot_serial.write(POWER_OFF);
    mycobot_serial.write(footer);
    delay(WRITE_SERVO_GAP);
}

bool MyCobotBasic::isPoweredOn()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(IS_POWERED_ON_LEN);
    mycobot_serial.write(IS_POWERED_ON);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pPowerState = nullptr;
    bool powerState;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, powerState, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return powerState;
        }
    }
    return false;
}

int MyCobotBasic::getAtomVersion()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SYSTEM_VERSION_LEN);
    mycobot_serial.write(GET_SYSTEM_VERSION);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pReturnVersion = nullptr;
    int returnVersion;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, returnVersion, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return returnVersion;
        }
    }

}

void MyCobotBasic::DivideSerialData(unsigned char *rec_data, unsigned char *nDat, int nLen)
{
    rec_data = rec_data + 1;
    memcpy(nDat, rec_data, nLen);
}

template<typename T, typename O, typename R, typename E, typename M>
int MyCobotBasic::readData(T& pData, O& bData, R& rData, E& eData, M& mData)
{
    rFlushSerial();

    int len = 1024;
    byte data[1024]{0};
    if (readSerial(data, len) == 0) {
        //Serial.println("no data");
        return -2;
    }
    byte data_len[1];
    byte r_data_3[3], r_data_4[4], r_data_14[14], r_data_8[8];
    switch (static_cast<int>(data[0])) {
        case 3:
            DivideSerialData(data, r_data_3, 3);
            switch (int(r_data_3[0])) {
                case IS_IN_POSITION: {
                    bData = r_data_3[1];
                    return 1;
                }

                case CHECK_RUNNING: {
                    bData = bool(r_data_3[1]);
                    return 1;
                }

                case GET_SPEED: {
                    bData = r_data_3[1];
                    return 1;
                }

                case IS_ALL_SERVO_ENABLED: {
                    bData = bool(r_data_3[1]);
                    return 1;
                }
                case IS_POWERED_ON: {
                    bData = bool(r_data_3[1]);
                    return 1;
                }
                case GET_SERVO_DATA: {
                    bData = r_data_3[1];
                    return 1;
                }
                case GET_REF_FRAME: {
                    rData = RFType(r_data_3[1]);
                    return 1;
                }
                case GET_MOVEMENT_TYPE: {
                    mData = MovementType(r_data_3[1]);
                    return 1;
                }
                case GET_END_TYPE: {
                    eData = EndType(r_data_3[1]);
                    return 1;
                }
                case ROBOTIC_MESSAGE: {
                    bData = r_data_3[1];
                    return 1;
                }

                case IS_GRIPPER_MOVING: {
                    bData = r_data_3[1];
                    return 1;
                }
                case GET_GRIPPER_VALUE: {
                    bData = r_data_3[1];
                    return 1;
                }
                case GET_ROBOT_VERSION: {
                    bData = r_data_3[1];
                    return 1;
                }
                case GET_SYSTEM_VERSION: {
                    bData = r_data_3[1];
                    return 1;
                }
            }

        case 4:
            DivideSerialData(data, r_data_4, 4);
            switch (int(r_data_4[0])) {
                case IS_SERVO_ENABLED: {
                    bData = bool(r_data_4[2]);
                    return 1;
                }

                case GET_DIGITAL_INPUT: {
                    bData = r_data_4[2];
                    return 1;
                }

                case GET_FEED_OVERRIDE: {
                    byte feed_override_high = r_data_4[1];
                    byte feed_override_low = r_data_4[2];
                    float temp = 0.0;
                    temp = feed_override_low + feed_override_high * 256;
                    bData = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return 1;
                }

                case GET_ACCELERATION: {
                    byte acceleration_high = r_data_4[1];
                    byte acceleration_low = r_data_4[2];
                    float temp = 0.0;
                    temp = acceleration_low + acceleration_high * 256;
                    bData = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return 1;
                }
                case GET_JOINT_MIN: {
                    byte jointMin_high = r_data_4[1];
                    byte jointMin_low = r_data_4[2];
                    float temp = 0.0;
                    temp = jointMin_low + jointMin_high * 256;
                    bData = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return 1;
                }
                case GET_JOINT_MAX: {
                    byte jointMax_high = r_data_4[1];
                    byte jointMax_low = r_data_4[2];
                    float temp = 0.0;
                    temp = jointMax_low + jointMax_high * 256;
                    bData = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    return 1;
                }
                case GET_ENCODER: {
                    byte encoder_high = r_data_4[1];
                    byte encoder_low = r_data_4[2];
                    bData = encoder_low + encoder_high * 256;
                    return 1;
                }

            }
        case 8:    
            DivideSerialData(data, r_data_8, 8);
            switch (int(r_data_8[0])) {
                 case GET_SERVO_VOLTAGES: {
                     pData.at(0) = r_data_8[1];
                     pData.at(1) = r_data_8[2];
                     pData.at(2) = r_data_8[3];
                     pData.at(3) = r_data_8[4];
                     pData.at(4) = r_data_8[5];
                     pData.at(5) = r_data_8[6];
                     return 1;
                 }
                 case GET_SERVO_STATUS: {
                     pData.at(0) = r_data_8[1];
                     pData.at(1) = r_data_8[2];
                     pData.at(2) = r_data_8[3];
                     pData.at(3) = r_data_8[4];
                     pData.at(4) = r_data_8[5];
                     pData.at(5) = r_data_8[6];
                     return 1;
                 }
                 case GET_SERVO_TEMPS: {
                     pData.at(0) = r_data_8[1];
                     pData.at(1) = r_data_8[2];
                     pData.at(2) = r_data_8[3];
                     pData.at(3) = r_data_8[4];
                     pData.at(4) = r_data_8[5];
                     pData.at(5) = r_data_8[6];
                     return 1;
                 }
                 case GET_PID: {
                     pData.at(0) = r_data_8[1];
                     pData.at(1) = r_data_8[2];
                     pData.at(2) = r_data_8[3];
                     pData.at(3) = r_data_8[4];
                     pData.at(4) = r_data_8[5];
                     pData.at(5) = r_data_8[6];
                     return 1;
                 }
            }
        case 14:
            DivideSerialData(data, r_data_14, 14);
           switch (int(r_data_14[0])) {
                 case GET_ANGLES: {
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

                    float temp = 0.0;
                    temp = angle_1_low + angle_1_high * 256;
                    pData.at(0) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_2_low + angle_2_high * 256;
                    pData.at(1) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_3_low + angle_3_high * 256;
                    pData.at(2) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_4_low + angle_4_high * 256;
                    pData.at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_5_low + angle_5_high * 256;
                    pData.at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = angle_6_low + angle_6_high * 256;
                    pData.at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

                    return 1;
                }

                case GET_COORDS: {
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

                    float temp = 0.0;

                    temp = x_low + x_high * 256;
                    pData.at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = y_low + y_high * 256;
                    pData.at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = z_low + z_high * 256;
                    pData.at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = rx_low + rx_high * 256;
                    pData.at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = ry_low + ry_high * 256;
                    pData.at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = rz_low + rz_high * 256;
                    pData.at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

                    return 1;
                }
                case GET_ENCODERS: {
                    byte encode_1_high = r_data_14[1];
                    byte encode_1_low = r_data_14[2];

                    byte encode_2_high = r_data_14[3];
                    byte encode_2_low = r_data_14[4];

                    byte encode_3_high = r_data_14[5];
                    byte encode_3_low = r_data_14[6];

                    byte encode_4_high = r_data_14[7];
                    byte encode_4_low = r_data_14[8];

                    byte encode_5_high = r_data_14[9];
                    byte encode_5_low = r_data_14[10];

                    byte encode_6_high = r_data_14[11];
                    byte encode_6_low = r_data_14[12];

                    pData.at(0) = encode_1_low + encode_1_high * 256;
                    pData.at(1) = encode_2_low + encode_2_high * 256;
                    pData.at(2) = encode_3_low + encode_3_high * 256;
                    pData.at(3) = encode_4_low + encode_4_high * 256;
                    pData.at(4) = encode_5_low + encode_5_high * 256;
                    pData.at(5) = encode_6_low + encode_6_high * 256;
                    return 1;
                }
                case GET_SERVO_SPEEDS: {
                    byte speed_1_high = r_data_14[1];
                    byte speed_1_low = r_data_14[2];

                    byte speed_2_high = r_data_14[3];
                    byte speed_2_low = r_data_14[4];

                    byte speed_3_high = r_data_14[5];
                    byte speed_3_low = r_data_14[6];

                    byte speed_4_high = r_data_14[7];
                    byte speed_4_low = r_data_14[8];

                    byte speed_5_high = r_data_14[9];
                    byte speed_5_low = r_data_14[10];

                    byte speed_6_high = r_data_14[11];
                    byte speed_6_low = r_data_14[12];

                    pData.at(0) = speed_1_low + speed_1_high * 256;
                    pData.at(1) = speed_2_low + speed_2_high * 256;
                    pData.at(2) = speed_3_low + speed_3_high * 256;
                    pData.at(3) = speed_4_low + speed_4_high * 256;
                    pData.at(4) = speed_5_low + speed_5_high * 256;
                    pData.at(5) = speed_6_low + speed_6_high * 256;
                    return 1;
                }
                case GET_SERVO_CURRENTS: {
                    byte current_1_high = r_data_14[1];
                    byte current_1_low = r_data_14[2];

                    byte current_2_high = r_data_14[3];
                    byte current_2_low = r_data_14[4];

                    byte current_3_high = r_data_14[5];
                    byte current_3_low = r_data_14[6];

                    byte current_4_high = r_data_14[7];
                    byte current_4_low = r_data_14[8];

                    byte current_5_high = r_data_14[9];
                    byte current_5_low = r_data_14[10];

                    byte current_6_high = r_data_14[11];
                    byte current_6_low = r_data_14[12];

                    pData.at(0) = current_1_low + current_1_high * 256;
                    pData.at(1) = current_2_low + current_2_high * 256;
                    pData.at(2) = current_3_low + current_3_high * 256;
                    pData.at(3) = current_4_low + current_4_high * 256;
                    pData.at(4) = current_5_low + current_5_high * 256;
                    pData.at(5) = current_6_low + current_6_high * 256;
                    return 1;
                }
                case GET_TOOL_REF: {
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

                    float temp = 0.0;

                    temp = x_low + x_high * 256;
                    pData.at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = y_low + y_high * 256;
                    pData.at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = z_low + z_high * 256;
                    pData.at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = rx_low + rx_high * 256;
                    pData.at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = ry_low + ry_high * 256;
                    pData.at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = rz_low + rz_high * 256;
                    pData.at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

                    return 1;
                }

                case GET_WORLD_REF: {
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

                    float temp = 0.0;

                    temp = x_low + x_high * 256;
                    pData.at(0) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = y_low + y_high * 256;
                    pData.at(1) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = z_low + z_high * 256;
                    pData.at(2) = (temp > 33000 ? (temp - 65536) : temp) / 10;
                    temp = rx_low + rx_high * 256;
                    pData.at(3) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = ry_low + ry_high * 256;
                    pData.at(4) = (temp > 33000 ? (temp - 65536) : temp) / 100;
                    temp = rz_low + rz_high * 256;
                    pData.at(5) = (temp > 33000 ? (temp - 65536) : temp) / 100;

                    return 1;
                }
            }
    }
    return -2;
}

Angles MyCobotBasic::getAngles()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_ANGLES_LEN);
    mycobot_serial.write(GET_ANGLES);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles angles;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(angles, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            return angles;
        }
    }
    return error_angles;
}

void MyCobotBasic::writeAngle(int joint, float value, int speed)
{
    byte joint_number = byte(joint);
    byte angle_low = lowByte(static_cast<int>(value * 100));
    byte angle_high = highByte(static_cast<int>(value * 100));

    byte sp = speed;

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(WRITE_ANGLE_LEN);
    mycobot_serial.write(WRITE_ANGLE);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(angle_high);
    mycobot_serial.write(angle_low);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);

    delay(WRITE_SERVO_GAP);
}

void MyCobotBasic::writeAngles(Angles angles, int speed)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(WRITE_ANDLES_LEN);
    mycobot_serial.write(WRITE_ANGLES);

    mycobot_serial.write(angle_1_high);
    mycobot_serial.write(angle_1_low);
    mycobot_serial.write(angle_2_high);
    mycobot_serial.write(angle_2_low);
    mycobot_serial.write(angle_3_high);
    mycobot_serial.write(angle_3_low);
    mycobot_serial.write(angle_4_high);
    mycobot_serial.write(angle_4_low);
    mycobot_serial.write(angle_5_high);
    mycobot_serial.write(angle_5_low);
    mycobot_serial.write(angle_6_high);
    mycobot_serial.write(angle_6_low);

    mycobot_serial.write(sp);

    mycobot_serial.write(footer);
    delay(WRITE_SERVO_GAP);
}

Coords MyCobotBasic::getCoords()
{
    //Serial.println("get coords");
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_COORDS_LEN);
    mycobot_serial.write(GET_COORDS);
    mycobot_serial.write(footer);
    //Serial.println("get coords2");

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Coords *pCoords = nullptr;
    Coords tempCoords;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(tempCoords, invalid, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return tempCoords;
        }
    }
    return error_coords;
}

void MyCobotBasic::writeCoord(Axis axis, float value, int speed)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(WRITE_COORD_LEN);
    mycobot_serial.write(WRITE_COORD);
    mycobot_serial.write(axis_number);
    mycobot_serial.write(value_high);
    mycobot_serial.write(value_low);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);
    //delay(WRITE_SERVO_GAP);

    //receiveMessages();
}

void MyCobotBasic::writeCoords(Coords coord, int speed)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(WRITE_COORDS_LEN);
    mycobot_serial.write(WRITE_COORDS);
    mycobot_serial.write(coord_x_high);
    mycobot_serial.write(coord_x_low);
    mycobot_serial.write(coord_y_high);
    mycobot_serial.write(coord_y_low);
    mycobot_serial.write(coord_z_high);
    mycobot_serial.write(coord_z_low);
    mycobot_serial.write(coord_rx_high);
    mycobot_serial.write(coord_rx_low);
    mycobot_serial.write(coord_ry_high);
    mycobot_serial.write(coord_ry_low);
    mycobot_serial.write(coord_rz_high);
    mycobot_serial.write(coord_rz_low);
    mycobot_serial.write(sp);
    mycobot_serial.write(mode);
    mycobot_serial.write(footer);
    //delay(WRITE_SERVO_GAP);

    //receiveMessages();
}

/*
int MyCobotBasic::isInPosition(Coords coord, bool is_linear)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(IS_IN_POSITION_LEN);
    mycobot_serial.write(IS_IN_POSITION);
    mycobot_serial.write(coord_x_high);
    mycobot_serial.write(coord_x_low);
    mycobot_serial.write(coord_y_high);
    mycobot_serial.write(coord_y_low);
    mycobot_serial.write(coord_z_high);
    mycobot_serial.write(coord_z_low);
    mycobot_serial.write(coord_rx_high);
    mycobot_serial.write(coord_rx_low);
    mycobot_serial.write(coord_ry_high);
    mycobot_serial.write(coord_ry_low);
    mycobot_serial.write(coord_rz_high);
    mycobot_serial.write(coord_rz_low);
    mycobot_serial.write(type);
    mycobot_serial.write(footer);


    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pIsInposition = nullptr;
    int isInposition;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, isInposition, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return isInposition;
        }
    }
    return -1;
}
*/


bool MyCobotBasic::checkRunning()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(CHECK_RUNNING_LEN);
    mycobot_serial.write(CHECK_RUNNING);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *prunning_state = nullptr;
    bool running_state;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, running_state, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return running_state;
        }
    }
    return false;
}


void MyCobotBasic::jogAngle(int joint, int direction, int speed)
{
    byte joint_number = joint;
    byte di = direction;
    byte sp = speed;

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(JOG_ANGLE_LEN);
    mycobot_serial.write(JOG_ANGLE);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(di);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);
    delay(WRITE_SERVO_GAP);
}

void MyCobotBasic::jogCoord(Axis axis, int direction, int speed)
{
    byte axis_number = axis + 1;
    byte di = direction;
    byte sp = speed;

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(JOG_COORD_LEN);
    mycobot_serial.write(JOG_COORD);
    mycobot_serial.write(axis_number);
    mycobot_serial.write(di);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);
    delay(WRITE_SERVO_GAP);
}

void MyCobotBasic::jogStop()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(JOG_STOP_LEN);
    mycobot_serial.write(JOG_STOP);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setEncoder(int joint, int encoder)
{
    byte joint_number = joint;
    byte encoder_high = highByte(encoder);
    byte encoder_low = lowByte(encoder);

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_ENCODER_LEN);
    mycobot_serial.write(SET_ENCODER);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(encoder_high);
    mycobot_serial.write(encoder_low);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setEncodersDrag(Angles angleEncoders, Angles speeds)
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
    //byte sp = speed;
    byte speed_1_high = highByte(static_cast<int>(speeds[0]));
    byte speed_1_low = lowByte(static_cast<int>(speeds[0]));
    byte speed_2_high = highByte(static_cast<int>(speeds[1]));
    byte speed_2_low = lowByte(static_cast<int>(speeds[1]));
    byte speed_3_high = highByte(static_cast<int>(speeds[2]));
    byte speed_3_low = lowByte(static_cast<int>(speeds[2]));
    byte speed_4_high = highByte(static_cast<int>(speeds[3]));
    byte speed_4_low = lowByte(static_cast<int>(speeds[3]));
    byte speed_5_high = highByte(static_cast<int>(speeds[4]));
    byte speed_5_low = lowByte(static_cast<int>(speeds[4]));
    byte speed_6_high = highByte(static_cast<int>(speeds[5]));
    byte speed_6_low = lowByte(static_cast<int>(speeds[5]));

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_ENCODERS_DRAG_LEN);
    mycobot_serial.write(SET_ENCODERS_DRAG);
    mycobot_serial.write(angle_1_high);
    mycobot_serial.write(angle_1_low);
    mycobot_serial.write(angle_2_high);
    mycobot_serial.write(angle_2_low);
    mycobot_serial.write(angle_3_high);
    mycobot_serial.write(angle_3_low);
    mycobot_serial.write(angle_4_high);
    mycobot_serial.write(angle_4_low);
    mycobot_serial.write(angle_5_high);
    mycobot_serial.write(angle_5_low);
    mycobot_serial.write(angle_6_high);
    mycobot_serial.write(angle_6_low);
    
    mycobot_serial.write(speed_1_high);
    mycobot_serial.write(speed_1_low);
    mycobot_serial.write(speed_2_high);
    mycobot_serial.write(speed_2_low);
    mycobot_serial.write(speed_3_high);
    mycobot_serial.write(speed_3_low);
    mycobot_serial.write(speed_4_high);
    mycobot_serial.write(speed_4_low);
    mycobot_serial.write(speed_5_high);
    mycobot_serial.write(speed_5_low);
    mycobot_serial.write(speed_6_high);
    mycobot_serial.write(speed_6_low);
    //mycobot_serial.write(sp);
    mycobot_serial.write(footer);
}

Angles MyCobotBasic::getServoSpeeds()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SERVO_SPEEDS_LEN);
    mycobot_serial.write(GET_SERVO_SPEEDS);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles speeds;
    
    while (true) {
        if (millis() - t_begin > 40) {
            break;
        }
        if (readData(speeds, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            //Serial.println("have data");
            //Serial.println(millis() - t_begin);
            return speeds;
        }
    }
    return error_speeds;
}
#ifdef MyCobot_Pro_350
Angles MyCobotBasic::getServoCurrents()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SERVO_CURRENTS_LEN);
    mycobot_serial.write(GET_SERVO_CURRENTS);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles currents;
    
    while (true) {
        if (millis() - t_begin > 40) {
            break;
        }
        if (readData(currents, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            //Serial.println("have data");
            //Serial.println(millis() - t_begin);
            return currents;
        }
    }
    return error_speeds;
}
#endif
Angles MyCobotBasic::getServoVoltages()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SERVO_VOLTAGES_LEN);
    mycobot_serial.write(GET_SERVO_VOLTAGES);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles voltages;
    
    while (true) {
        if (millis() - t_begin > 40) {
            break;
        }
        if (readData(voltages, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            //Serial.println("have data");
            //Serial.println(millis() - t_begin);
            return voltages;
        }
    }
    return error_speeds;
}

Angles MyCobotBasic::getServoStatus()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SERVO_STATUS_LEN);
    mycobot_serial.write(GET_SERVO_STATUS);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles status;
    
    while (true) {
        if (millis() - t_begin > 40) {
            break;
        }
        if (readData(status, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            //Serial.println("have data");
            //Serial.println(millis() - t_begin);
            return status;
        }
    }
    return error_speeds;
}

Angles MyCobotBasic::getServoTemps()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SERVO_TEMPS_LEN);
    mycobot_serial.write(GET_SERVO_TEMPS);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles temps;
    
    while (true) {
        if (millis() - t_begin > 40) {
            break;
        }
        if (readData(temps, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            //Serial.println("have data");
            //Serial.println(millis() - t_begin);
            return temps;
        }
    }
    return error_speeds;
}

void MyCobotBasic::setPid(Angles pids)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_PID_LEN);
    mycobot_serial.write(SET_PID);
    for (int i = 0; i < 6; i++) {
        mycobot_serial.write(static_cast<int>(pids[i]));
    }
    mycobot_serial.write(footer);
}

Angles MyCobotBasic::getPid()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_PID_LEN);
    mycobot_serial.write(GET_PID);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pAngles = nullptr;
    Angles pids;
    
    while (true) {
        if (millis() - t_begin > 40) {
            break;
        }
        if (readData(pids, invalid, r_invalid, e_invalid, m_invalid) == -2) {
            continue;
        } else {
            //Serial.println("have data");
            //Serial.println(millis() - t_begin);
            return pids;
        }
    }
    return error_speeds;
}

int MyCobotBasic::getEncoder(int joint)
{
    byte joint_number = joint;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_ENCODER_LEN);
    mycobot_serial.write(GET_ENCODER);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pEncoder = nullptr;
    int encoder;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, encoder, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return encoder;
        }
    }

    return -1;
}

Angles MyCobotBasic::getEncoders()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_ENCODERS_LEN);
    mycobot_serial.write(GET_ENCODERS);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Angles *pEncoders = nullptr;
    Angles encoders;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(encoders, invalid, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return encoders;
        }
    }
    return error_encoders;
}

void MyCobotBasic::setEncoders(Angles angleEncoders, int speed)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_ENCODERS_LEN);
    mycobot_serial.write(SET_ENCODERS);
    mycobot_serial.write(angle_1_high);
    mycobot_serial.write(angle_1_low);
    mycobot_serial.write(angle_2_high);
    mycobot_serial.write(angle_2_low);
    mycobot_serial.write(angle_3_high);
    mycobot_serial.write(angle_3_low);
    mycobot_serial.write(angle_4_high);
    mycobot_serial.write(angle_4_low);
    mycobot_serial.write(angle_5_high);
    mycobot_serial.write(angle_5_low);
    mycobot_serial.write(angle_6_high);
    mycobot_serial.write(angle_6_low);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);
}

int MyCobotBasic::getSpeed()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SPEED_LEN);
    mycobot_serial.write(GET_SPEED);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pSpeed = nullptr;
    int speed;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, speed, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return speed;
        }
    }

    return -1;
}

void MyCobotBasic::setSpeed(int percentage)
{
    byte speed = percentage;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_SPEED_LEN);
    mycobot_serial.write(SET_SPEED);
    mycobot_serial.write(speed);
    mycobot_serial.write(footer);
}

/*
float MyCobotBasic::getFeedOverride()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_FEED_OVERRIDE_LEN);
    mycobot_serial.write(GET_FEED_OVERRIDE);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pfeed_override = nullptr;
    float feed_override;
    //Angles invalid;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, feed_override, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return feed_override;
        }
    }

    return -1.0;
}
*/
/*
void MyCobotBasic::sendFeedOverride(float feed_override)
{
    byte feed_override_high = highByte(static_cast<int>(feed_override * 10));
    byte feed_override_low = lowByte(static_cast<int>(feed_override * 10));

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SEND_OVERRIDE_LEN);
    mycobot_serial.write(SEND_OVERRIDE);
    mycobot_serial.write(feed_override_high);
    mycobot_serial.write(feed_override_low);
    mycobot_serial.write(footer);
}
*/
/*
float MyCobotBasic::getAcceleration()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_ACCELERATION_LEN);
    mycobot_serial.write(GET_ACCELERATION);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pAcceleration = nullptr;
    float acceleration;
    //Angles invalid;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, acceleration, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return acceleration;
        }
    }

    return -1.0;
}
*/
/*
void MyCobotBasic::setAcceleration(float acceleration)
{
    byte acceleration_high = highByte(static_cast<int>(acceleration * 10));
    byte acceleration_low = lowByte(static_cast<int>(acceleration * 10));

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_ACCELERATION_LEN);
    mycobot_serial.write(SET_ACCELERATION);
    mycobot_serial.write(acceleration_high);
    mycobot_serial.write(acceleration_low);
    mycobot_serial.write(footer);
}
*/
/*
float MyCobotBasic::getJointMin(int joint)
{
    byte joint_number = joint;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_JOINT_MIN_LEN);
    mycobot_serial.write(GET_JOINT_MIN);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pJointMin = nullptr;
    float jointMin;
    //Angles invalid;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, jointMin, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return jointMin;
        }
    }

    return -5.0;
}

float MyCobotBasic::getJointMax(int joint)
{
    byte joint_number = joint;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_JOINT_MAX_LEN);
    mycobot_serial.write(GET_JOINT_MAX);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    float *pJointMax = nullptr;
    float jointMax;
    //Angles invalid;

    while (true) {
        if (millis() - t_begin > 40)
            break;
       if (readData(a_invalid, jointMax, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return jointMax;
        }
    }

    return -5.0;
}

/*
void MyCobotBasic::setJointMin(int joint, float angle)
{
    byte joint_number = joint;
    byte angle_low = lowByte(static_cast<int>(angle * 10));
    byte angle_high = highByte(static_cast<int>(angle * 10));
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_JOINT_MIN_LEN);
    mycobot_serial.write(SET_JOINT_MIN);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(angle_high);
    mycobot_serial.write(angle_low);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setJointMax(int joint, float angle)
{
    byte joint_number = joint;
    byte angle_low = lowByte(static_cast<int>(angle * 10));
    byte angle_high = highByte(static_cast<int>(angle * 10));
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_JOINT_MAX_LEN);
    mycobot_serial.write(SET_JOINT_MAX);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(angle_high);
    mycobot_serial.write(angle_low);
    mycobot_serial.write(footer);
}
*/

bool MyCobotBasic::isServoEnabled(int joint)
{
    byte joint_number = joint;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(IS_SERVO_ENABLED_LEN);
    mycobot_serial.write(IS_SERVO_ENABLED);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pServoState = nullptr;
    bool servoState;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, servoState, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return servoState;
        }
    }
    return false;
}

bool MyCobotBasic::isAllServoEnabled()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(IS_ALL_SERVO_ENABLED_LEN);
    mycobot_serial.write(IS_ALL_SERVO_ENABLED);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pServoState = nullptr;
    bool servoState;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, servoState, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return servoState;
        }
    }
    return false;
}

byte MyCobotBasic::getServoData(int joint, byte data_id)
{
    byte joint_number = joint;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_SERVO_DATA_LEN);
    mycobot_serial.write(GET_SERVO_DATA);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(data_id);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    byte *pServoData = nullptr;
    byte servoData;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, servoData, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return servoData;
        }
    }

    return -1.0;
}

void MyCobotBasic::setServoCalibration(int joint)
{
    byte joint_number = joint;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_SERVO_CALIBRATION_LEN);
    mycobot_serial.write(SET_SERVO_CALIBRATION);
    mycobot_serial.write(joint_number);
    mycobot_serial.write(footer);
}


void MyCobotBasic::setPinMode(byte pin_no, byte pin_mode)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_PIN_MODE_LEN);
    mycobot_serial.write(SET_PIN_MODE);
    mycobot_serial.write(pin_no);
    mycobot_serial.write(pin_mode);
    mycobot_serial.write(footer);
}

void MyCobotBasic::ProgramPause()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(PROGRAM_PAUSE_LEN);
    mycobot_serial.write(PROGRAM_PAUSE);
    mycobot_serial.write(footer);
}

void MyCobotBasic::ProgramResume()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(PROGRAM_RESUME_LEN);
    mycobot_serial.write(PROGRAM_RESUME);
    mycobot_serial.write(footer);
}

void MyCobotBasic::TaskStop()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(TASK_STOP_LEN);
    mycobot_serial.write(TASK_STOP);
    mycobot_serial.write(footer);
}


void MyCobotBasic::setLEDRGB(byte r, byte g, byte b)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_LED_LEN);
    mycobot_serial.write(SET_LED);
    mycobot_serial.write(r);
    mycobot_serial.write(g);
    mycobot_serial.write(b);
    mycobot_serial.write(footer);
}

/*
void MyCobotBasic::setGripper(int data)
{
    byte gripper_data = data;
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_GRIPPER_STATE_LEN);
    mycobot_serial.write(SET_GRIPPER_STATE);
    mycobot_serial.write(gripper_data);
    mycobot_serial.write(footer);
}
*/

void MyCobotBasic::setServoData(byte servo_no, byte servo_state,
                                byte servo_data)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_SERVO_DATA_LEN);
    mycobot_serial.write(SET_SERVO_DATA);

    mycobot_serial.write(servo_no);
    mycobot_serial.write(servo_state);
    mycobot_serial.write(servo_data);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setFreeMove()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_FREE_MOVE_LEN);
    mycobot_serial.write(SET_FREE_MOVE);
    mycobot_serial.write(footer);
}

/*
void MyCobotBasic::receiveMessages()
{
    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    byte *pMessage = nullptr;
    int message;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, message, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            /*std::map<int, std::string>::iterator iter = messages_map.find(message);
            char *pChar = (char *)iter->second.c_str();
            if (iter != messages_map.end())
                Serial.println(pChar);*//*
        }
    }

}
*/

void MyCobotBasic::setMovementType(MovementType movement_type)
{
    byte mt = movement_type;

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_MOVEMENT_TYPE_LEN);
    mycobot_serial.write(SET_MOVEMENT_TYPE);
    mycobot_serial.write(mt);
    mycobot_serial.write(footer);
}

MovementType MyCobotBasic::getMovementType()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_MOVEMENT_TYPE_LEN);
    mycobot_serial.write(GET_MOVEMENT_TYPE);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    MovementType *pMovementType = nullptr;
    MovementType movement_type;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, invalid, r_invalid, e_invalid, movement_type) == -2)
            continue;
        else {
            return movement_type;
        }
    }

    return ERROR_MOVEMENT;
}

void MyCobotBasic::setToolReference(Coords coord)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_TOOL_REF_LEN);
    mycobot_serial.write(SET_TOOL_REF);
    mycobot_serial.write(coord_x_high);
    mycobot_serial.write(coord_x_low);
    mycobot_serial.write(coord_y_high);
    mycobot_serial.write(coord_y_low);
    mycobot_serial.write(coord_z_high);
    mycobot_serial.write(coord_z_low);
    mycobot_serial.write(coord_rx_high);
    mycobot_serial.write(coord_rx_low);
    mycobot_serial.write(coord_ry_high);
    mycobot_serial.write(coord_ry_low);
    mycobot_serial.write(coord_rz_high);
    mycobot_serial.write(coord_rz_low);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setWorldReference(Coords coord)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_WORLD_REF_LEN);
    mycobot_serial.write(SET_WORLD_REF);
    mycobot_serial.write(coord_x_high);
    mycobot_serial.write(coord_x_low);
    mycobot_serial.write(coord_y_high);
    mycobot_serial.write(coord_y_low);
    mycobot_serial.write(coord_z_high);
    mycobot_serial.write(coord_z_low);
    mycobot_serial.write(coord_rx_high);
    mycobot_serial.write(coord_rx_low);
    mycobot_serial.write(coord_ry_high);
    mycobot_serial.write(coord_ry_low);
    mycobot_serial.write(coord_rz_high);
    mycobot_serial.write(coord_rz_low);
    mycobot_serial.write(footer);
}

Coords MyCobotBasic::getToolReference()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_TOOL_REF_LEN);
    mycobot_serial.write(GET_TOOL_REF);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Coords *pCoords = nullptr;
    Coords tempCoords;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(tempCoords, invalid, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return tempCoords;
        }
    }
    return error_coords;
}

Coords MyCobotBasic::getWorldReference()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_WORLD_REF_LEN);
    mycobot_serial.write(GET_WORLD_REF);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    Coords *pCoords = nullptr;
    Coords tempCoords;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(tempCoords, invalid, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return tempCoords;
        }
    }
    return error_coords;
}

void MyCobotBasic::setReferenceFrame(RFType rftype)
{
    byte rt = rftype;

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_REF_FRAME_LEN);
    mycobot_serial.write(SET_REF_FRAME);
    mycobot_serial.write(rt);
    mycobot_serial.write(footer);
}
/*
RFType MyCobotBasic::getReferenceFrame()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_REF_FRAME_LEN);
    mycobot_serial.write(GET_REF_FRAME);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    RFType *pRFType = nullptr;
    RFType rftype;
    //Angles invalid;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, invalid, rftype, e_invalid, m_invalid) == -2)
            continue;
        else {
            return rftype;
        }
    }

    return ERROR_RF;
}
*/
void MyCobotBasic::setEndType(EndType end_type)
{
    byte et = end_type;

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_END_TYPE_LEN);
    mycobot_serial.write(SET_END_TYPE);
    mycobot_serial.write(et);
    mycobot_serial.write(footer);
}

EndType MyCobotBasic::getEndType()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_END_TYPE_LEN);
    mycobot_serial.write(GET_END_TYPE);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    EndType *pEndType = nullptr;
    EndType end_type;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, invalid, r_invalid, end_type, m_invalid) == -2)
            continue;
        else {
            return end_type;
        }
    }

    return ERROR_END;
}

void MyCobotBasic::setDigitalOutput(byte pin_no, byte pin_state)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_DIGITAL_OUTPUT_LEN);
    mycobot_serial.write(SET_DIGITAL_OUTPUT);
    mycobot_serial.write(pin_no);
    mycobot_serial.write(pin_state);
    mycobot_serial.write(footer);
}

int MyCobotBasic::getDigitalInput(byte pin_no)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_DIGITAL_INPUT_LEN);
    mycobot_serial.write(GET_DIGITAL_INPUT);
    mycobot_serial.write(pin_no);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pReturnValue = nullptr;
    int returnValue;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, returnValue, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return returnValue;
        }
    }

    return -1;
}

/*
void MyCobotBasic::setPWMMode(int freq, byte pin_no, byte channel)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_PWM_MODE_LEN);
    mycobot_serial.write(SET_PWM_MODE);


    byte freq_high = highByte(freq);
    byte freq_low = lowByte(freq);

    mycobot_serial.write(freq_high);
    mycobot_serial.write(freqa_low);

    mycobot_serial.write(pin_no);
    mycobot_serial.write(channel);
    mycobot_serial.write(footer);
}*/

void MyCobotBasic::setPWMOutput(byte pin_no, int freq,  byte pin_write)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_PWM_OUTPUT_LEN);
    mycobot_serial.write(SET_PWM_OUTPUT);
    mycobot_serial.write(pin_no);

    byte freq_high = highByte(freq);
    byte freq_low = lowByte(freq);

    mycobot_serial.write(freq_high);
    mycobot_serial.write(freq_low);


    mycobot_serial.write(pin_write);
    mycobot_serial.write(footer);
}

void MyCobotBasic::releaseServo(byte servo_no)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(RELEASE_SERVO_LEN);
    mycobot_serial.write(RELEASE_SERVO);
    mycobot_serial.write(servo_no);
    mycobot_serial.write(footer);
}

void MyCobotBasic::focusServo(byte servo_no)
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(FOCUS_SERVO_LEN);
    mycobot_serial.write(FOCUS_SERVO);
    mycobot_serial.write(servo_no);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setGripperState(byte mode, int sp)
{
    if (sp > 100) {
        sp = 100;
    }
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_GRIPPER_STATE_LEN);
    mycobot_serial.write(SET_GRIPPER_STATE);
    mycobot_serial.write(mode);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setGripperValue(int data, int sp)
{
    if (data > 100) {
        data = 100;
    }
    if (sp > 100) {
        sp = 100;
    }
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_GRIPPER_VALUE_LEN);
    mycobot_serial.write(SET_GRIPPER_VALUE);
    mycobot_serial.write(data);
    mycobot_serial.write(sp);
    mycobot_serial.write(footer);
}

void MyCobotBasic::setGripperIni()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(SET_GRIPPER_INI_LEN);
    mycobot_serial.write(SET_GRIPPER_INI);
    mycobot_serial.write(footer);
}

int MyCobotBasic::getGripperValue()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(GET_GRIPPER_VALUE_LEN);
    mycobot_serial.write(GET_GRIPPER_VALUE);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    int *pReturnValue = nullptr;
    int returnValue;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, returnValue, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return returnValue;
        }
    }

    return -1;
}

bool MyCobotBasic::isGripperMoving()
{
    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(IS_GRIPPER_MOVING_LEN);
    mycobot_serial.write(IS_GRIPPER_MOVING);
    mycobot_serial.write(footer);

    unsigned long t_begin = millis();
    void *tempPtr = nullptr;
    bool *pState = nullptr;
    bool state;

    while (true) {
        if (millis() - t_begin > 40)
            break;
        if (readData(a_invalid, state, r_invalid, e_invalid, m_invalid) == -2)
            continue;
        else {
            return state;
        }
    }
    return false;
}

void MyCobotBasic::moveCCoords(Coords begin_coord, Coords middle_coord,
                               Coords end_coord)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(MOVEC_COORDS_DEFAULT_LEN);
    mycobot_serial.write(MOVEC_COORDS_DEFAULT);
    mycobot_serial.write(begin_x_high);
    mycobot_serial.write(begin_x_low);
    mycobot_serial.write(begin_y_high);
    mycobot_serial.write(begin_y_low);
    mycobot_serial.write(begin_z_high);
    mycobot_serial.write(begin_z_low);
    mycobot_serial.write(begin_rx_high);
    mycobot_serial.write(begin_rx_low);
    mycobot_serial.write(begin_ry_high);
    mycobot_serial.write(begin_ry_low);
    mycobot_serial.write(begin_rz_high);
    mycobot_serial.write(begin_rz_low);
    mycobot_serial.write(middle_x_high);
    mycobot_serial.write(middle_x_low);
    mycobot_serial.write(middle_y_high);
    mycobot_serial.write(middle_y_low);
    mycobot_serial.write(middle_z_high);
    mycobot_serial.write(middle_z_low);
    mycobot_serial.write(middle_rx_high);
    mycobot_serial.write(middle_rx_low);
    mycobot_serial.write(middle_ry_high);
    mycobot_serial.write(middle_ry_low);
    mycobot_serial.write(middle_rz_high);
    mycobot_serial.write(middle_rz_low);
    mycobot_serial.write(end_x_high);
    mycobot_serial.write(end_x_low);
    mycobot_serial.write(end_y_high);
    mycobot_serial.write(end_y_low);
    mycobot_serial.write(end_z_high);
    mycobot_serial.write(end_z_low);
    mycobot_serial.write(end_rx_high);
    mycobot_serial.write(end_rx_low);
    mycobot_serial.write(end_ry_high);
    mycobot_serial.write(end_ry_low);
    mycobot_serial.write(end_rz_high);
    mycobot_serial.write(end_rz_low);
    mycobot_serial.write(footer);
}

void MyCobotBasic::moveCCoords(Coords middle_coord, Coords end_coord)
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

    mycobot_serial.write(header);
    mycobot_serial.write(header);
    mycobot_serial.write(MOVEC_COORDS_LEN);
    mycobot_serial.write(MOVEC_COORDS);
    mycobot_serial.write(middle_x_high);
    mycobot_serial.write(middle_x_low);
    mycobot_serial.write(middle_y_high);
    mycobot_serial.write(middle_y_low);
    mycobot_serial.write(middle_z_high);
    mycobot_serial.write(middle_z_low);
    mycobot_serial.write(middle_rx_high);
    mycobot_serial.write(middle_rx_low);
    mycobot_serial.write(middle_ry_high);
    mycobot_serial.write(middle_ry_low);
    mycobot_serial.write(middle_rz_high);
    mycobot_serial.write(middle_rz_low);
    mycobot_serial.write(end_x_high);
    mycobot_serial.write(end_x_low);
    mycobot_serial.write(end_y_high);
    mycobot_serial.write(end_y_low);
    mycobot_serial.write(end_z_high);
    mycobot_serial.write(end_z_low);
    mycobot_serial.write(end_rx_high);
    mycobot_serial.write(end_rx_low);
    mycobot_serial.write(end_ry_high);
    mycobot_serial.write(end_ry_low);
    mycobot_serial.write(end_rz_high);
    mycobot_serial.write(end_rz_low);
    mycobot_serial.write(footer);
}