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

#ifndef Components_Particle_h__
#define Components_Particle_h__

#include "Core/Component.h"
#include "Core/Color.h"
#include <vector>

namespace Components
{

struct Particle : Component
{
	std::vector<glm::vec3> ScaleSpectrum;
	double LifeTime;
	double SpawnTime;
	bool Fade;
	std::vector<glm::vec3> VelocitySpectrum;
	std::vector<float> AngularVelocitySpectrum;
	std::vector<glm::vec3> OrientationSpectrum; //Keep?
};

}
#endif // !Components_Particle_h__