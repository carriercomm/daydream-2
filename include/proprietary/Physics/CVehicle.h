#ifndef Components_Vehicle_h__
#define Components_Vehicle_h__

#include "Core/Component.h"

namespace Components
{

struct Vehicle : Component
{
	Vehicle()
		: MaxTorque(1000.0f), MinRPM(200.0f), OptimalRPM(2500.0f), MaxRPM(4000.0f), MaxSteeringAngle(35), TopSpeed(90.0f),
	MaxSpeedFullSteeringAngle(40.0f), SpringDamping(1.f), UpshiftRPM(3500.0f), DownshiftRPM(1000.0f),
	gearsRatio0(3.0f), gearsRatio1(2.25f), gearsRatio2(1.5f), gearsRatio3(1.0f), currentRPM(0.0f){ }
	float MaxTorque;
	float MinRPM;
	float OptimalRPM;
	float MaxRPM;
	// Degrees
	float MaxSteeringAngle;
	//TopSpeed not working fully yet 
	float TopSpeed;
	float MaxSpeedFullSteeringAngle;
	float SpringDamping;
	float DownshiftRPM;
	float UpshiftRPM;
	float gearsRatio0;
	float gearsRatio1;
	float gearsRatio2;
	float gearsRatio3;
	float currentRPM;

	Vehicle* Clone() const override { return new Vehicle(*this); }
};

}

#endif // Components_Vehicle_h__
