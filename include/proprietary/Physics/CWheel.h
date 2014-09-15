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

#ifndef Components_Wheel_h__
#define Components_Wheel_h__

#include "Core/Component.h"

namespace Systems { class PhysicsSystem; }

namespace Components
{

struct Wheel : Component
{	
	friend class Systems::PhysicsSystem;

	Wheel()
		: AxleID(0), Radius(0), Width(0), Mass(0), Steering(false), DownDirection(glm::vec3(0, -1, 0)), Friction(1.5f), SlipAngle(0.0f),
	MaxBreakingTorque(50000.f), ConnectedToHandbrake(false), SuspensionStrength(50.0f), TorqueRatio(0.25f) { }

	// The Hardpoint MUST be positioned INSIDE the chassis.
	glm::vec3 Hardpoint;
	unsigned int AxleID;
	float Radius;
	float Width;
	float Mass;
	bool Steering;
	glm::vec3 DownDirection;

	float SuspensionStrength;
	float Friction;
	float SlipAngle;
	float MaxBreakingTorque;
	bool ConnectedToHandbrake;
	// The wheels total TorqueRatio must be equal to 1
	float TorqueRatio;

private:
	int ID;
	glm::quat OriginalOrientation;

	Wheel* Clone() const override { return new Wheel(*this); }
};

}
#endif // Components_Wheel_h__
