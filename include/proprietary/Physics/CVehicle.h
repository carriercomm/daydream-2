/*
	This file is part of Daydream Engine.
	Copyright 2014 Adam Byléhn, Tobias Dahl, Simon Holmberg, Viktor Ljung
	
	Daydream Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Daydream Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Daydream Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

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
