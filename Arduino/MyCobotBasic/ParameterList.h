#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H

#define MyCobot_M5 "m5"  //To use non-MyCobot280-m5 robotic arms, you need to comment out this line
//#define MyCobot_Mega "mega"   //if use non-mega,you need to should comment out this line
//#define MyCobot_Uno "uno"   if use non-Uno,you need to should comment out this line
//#define MyCobot_Mkr "mkr"   //if use non-Mkr,you need to should comment out this line

#if defined MyCobot_Mega || defined MyCobot_Uno
#include <hashtable-aux.h>
#endif

#if defined MyCobot_Mega || defined MyCobot_Mkr
#define mycobot_serial Serial1
#endif

#if defined MyCobot_Uno
#define mycobot_serial Serial
#endif

#if defined MyCobot_M5
#include <M5Stack.h>
#define mycobot_serial Serial2
#endif

#include <array>
#include <map>

namespace myCobotDefine
{

#define SYSTEM_VERSION        0x01

#define MYCOBOT_500_VERSION            1
#define PI                        3.14159265
#define COEFFICIENT                (180.0 / PI)

    // DH parameters
    const float a2 = -110.4;
    const float a3 = -96.0;

    const float alpha_1 = PI / 2;
    const float alpha_4 = PI / 2;
    const float alpha_5 = -PI / 2;

    const float d1 = 131.56;
    const float d4 = 64.62;
    const float d5 = 73.18;
    const float d6 = 48.6;

    // initial theta offset
    const float theta_init_2 = -PI / 2;
    const float theta_init_4 = -PI / 2;
    const float theta_init_5 = PI / 2;

    // Servo maximum and minimum offset
    const float range_offset = 0.01;

    // convert encoder value to rad
    const float cvt_encoder_to_rad = 2048 / PI;

    // robotic data struct
    enum Axis : int { X = 0, Y, Z, RX, RY, RZ };
    enum Joint : int { J1 = 0, J2, J3, J4, J5, J6 };
    constexpr const int Axes = 6;
    constexpr const int Joints = 6;
    using Coords = std::array<float, Axes>;
    using Angles = std::array<float, Joints>;

    using Encoders = std::array<float, Joints>;


    //MyPalletizer data struct
    enum MyPalletizerAxis : int { P_X = 0, P_Y, P_Z, P_THETA };
    enum MyPalletizerJoint : int { P_J1 = 0, P_J2, P_J3, P_J4 };
    constexpr const int MyPalletizerAxesNum = 4;
    constexpr const int MyPalletizerJointsNum = 4;
    using MyPalletizerCoords = std::array<float, MyPalletizerAxesNum>;
    using MyPalletizerAngles = std::array<float, MyPalletizerJointsNum>;

    using MyPalletizerEncoders = std::array<float, MyPalletizerJointsNum>;

    // servo speed
    const float maximum_large_servo_speed = 1000;    //2000?
    const float maximum_small_servo_speed = 1400; // 3000?

    // isInPosition offset
    const float is_in_position_offset = 5;
    const float is_in_poseture_offset = 0.3;
    const float is_in_angles_offset = 0.1;

    // reference frame type
    enum RFType : int { ERROR_RF = -1, BASE = 0, WORLD };

    // compute flange pose or tool pose
    enum EndType : int { ERROR_END = -1, FLANGE = 0, TOOL };

    // movement type
    enum MovementType : int { ERROR_MOVEMENT = -1, MOVEJ = 0, MOVEL };

    struct RobotPose {
        RobotPose()
        {
            for (auto &val : position)
                val = 0.0;
            for (auto &val : poseture)
                val = 0.0;
        };

        RobotPose operator=(const RobotPose &rp)
        {
            for (int i = 0; i < 3; ++i)
                position[i] = rp.position[i];
            for (int i = 0; i < 3; ++i)
                poseture[i] = rp.poseture[i];
            for (int i = 0; i < 4; ++i)
                quaternion[i] = rp.quaternion[i];
        }

        float position[3];
        float poseture[3];
        float quaternion[4];
    };



}

namespace roboticMessages
{

#define IK_NO_SOLUTION            0x20
#define ITS_POWER_OFF            0x21


    /*const std::pair<int, std::string> printList[] = { {IK_NO_SOLUTION, "inverse kinematics no solution"},
        {ITS_POWER_OFF, "robotic is power off"}
    };*/


}

#endif // !PARAMETERLIST_H
