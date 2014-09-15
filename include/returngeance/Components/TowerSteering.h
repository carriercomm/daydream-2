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

#ifndef TowerSteering_h__
#define TowerSteering_h__

#include "Component.h"

	namespace Components
{

struct TowerSteering : Component
{
	TowerSteering()
		: TurnSpeed(1.f), Axis(glm::vec3(0,1,0)){ }
	float TurnSpeed;
	glm::vec3 Axis;
	virtual TowerSteering* Clone() const override { return new TowerSteering(*this); }
};

}

#endif // TowerSteering_h__