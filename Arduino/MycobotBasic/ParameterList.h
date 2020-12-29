#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H

#include <array>

namespace myCobotDefine {

#define SYSTEM_VERSION		0x01

#define MYCOBOT_500_VERSION			1
#define PI						3.14159265
#define COEFFICIENT				(180.0 / PI)

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

	// servo speed
	const float maximumLargeServoSpeed = 1000;	//2000?
	const float maximumSmallServoSpeed = 1000; // 3000?

	// isInPosition offset
	const float isInPositionOffset = 5;
	const float isInPosetureOffset = 0.3;

	// reference frame type
	enum RFType : int { BASE = 0, WORLD };

	// compute flange pose or tool pose
	enum EndType : int { FLANGE = 0, TOOL };

	struct RobotPose
	{
		RobotPose() {
			for (auto &val : position)
				val = 0.0;
			for (auto &val : poseture)
				val = 0.0;
		};

		RobotPose operator=(const RobotPose& rp)
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

	// robotic joint range
	struct JointRanges
	{
		//jonit 1 range
		float j_1_min = -165 / COEFFICIENT;
		float j_1_max = 165 / COEFFICIENT;
		//jonit 2 range
		float j_2_min = -155 / COEFFICIENT;
		float j_2_max = 155 / COEFFICIENT;
		//jonit 3 range
		float j_3_min = -165 / COEFFICIENT;
		float j_3_max = 165 / COEFFICIENT;
		//jonit 4 range
		float j_4_min = -165 / COEFFICIENT;
		float j_4_max = 165 / COEFFICIENT;
		//jonit 5 range
		float j_5_min = -165 / COEFFICIENT;
		float j_5_max = 165 / COEFFICIENT;
		//jonit 6 range
		float j_6_min = -175 / COEFFICIENT;
		float j_6_max = 175 / COEFFICIENT;
	};

}
#endif // !PARAMETERLIST_H
