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

#ifndef Event_CreateExplosion_h__
#define Event_CreateExplosion_h__

#include "EventBroker.h"
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Events
{
	struct CreateExplosion : Event
	{
		CreateExplosion() : 
			Color(glm::vec4(0)), 
			usePointLight(false), 
			UseGoalVector(false) {}

		glm::vec3 Position;
		glm::vec4 Color;
		double LifeTime;
		int ParticlesToSpawn;
		std::string spritePath;
		glm::quat RelativeUpOrientation;
		float Speed;
		float SpreadAngle;
		float usePointLight;
		std::vector<float> ParticleScale;
		bool UseGoalVector;
		glm::vec3 GoalVelocity;
		bool Emitting;
		float SpawnFrequency;
	};

}

#endif // Event_CreateExplosion_h__
