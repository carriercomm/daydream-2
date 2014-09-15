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

#ifndef Components_Physics_h__
#define Components_Physics_h__

#include "Core/Component.h"

namespace Components
{

struct Physics : Component
{
	enum class CollisionLayer
	{
		STATIC = 1,
		VEHICLE1_ = 2,
		VEHICLE2 = 3,
		EXPLOSION = 4,
	};

	enum class MotionTypeEnum
	{
		Dynamic,
		Fixed,
		Keyframed
	};

	Physics()
		: Mass(1.f)
		//, Static(false)
		, MotionType(MotionTypeEnum::Fixed)
		, Phantom(false)
		, CalculateCenterOfMass(true)
		, CenterOfMass(glm::vec3(0))
		, InitialLinearVelocity(glm::vec3(0))
		, InitialAngularVelocity(glm::vec3(0))
		, LinearDamping(0.f)
		, AngularDamping(0.05f)
		, GravityFactor(1.f)
		, Friction(0.5f)
		, Restitution(0.4f)
		, MaxLinearVelocity(200.f)
		, MaxAngularVelocity(200.f)
		, CollisionLayer(0)
		, CollisionSystemGroup(0)
		, CollisionSubSystemId(0)
		, CollisionSubSystemDontCollideWith(0)
		, CollisionEvent(false)
	{ }

	float Mass;
	MotionTypeEnum MotionType;
	bool Phantom;

	bool CalculateCenterOfMass;
	glm::vec3 CenterOfMass;
	glm::vec3 InitialLinearVelocity;
	glm::vec3 InitialAngularVelocity;
	float LinearDamping;
	float AngularDamping;
	float GravityFactor;
	float Friction;
	float Restitution;
	float MaxLinearVelocity;
	float MaxAngularVelocity;
	
	int CollisionLayer;
	int CollisionSystemGroup;
	int CollisionSubSystemId;
	int CollisionSubSystemDontCollideWith;
	
	bool CollisionEvent;

	virtual Physics* Clone() const override { return new Physics(*this); }
};

}

#endif // Components_Physics_h__
