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

#ifndef Components_Camera_h__
#define Components_Camera_h__

#include "Core/Component.h"
#include "Core/Entity.h"

namespace dd
{

namespace Components
{

struct Camera : Component
{
	Camera() 
	: FOV(glm::radians(45.f))
	, NearClip(0.1f)
	, FarClip(100.f) { }

	float FOV;
	float NearClip;
	float FarClip;
};

}
}

#endif // !Components_Camera_h__