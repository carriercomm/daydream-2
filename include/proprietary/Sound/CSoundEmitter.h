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

#ifndef Components_SoundEmitter_h__
#define Components_SoundEmitter_h__

#include "Core/Component.h"

namespace Components
{
	
struct SoundEmitter : Component
{
	enum class SoundType
	{
		SOUND_3D,
		SOUND_2D
	};

	SoundEmitter() : Gain(1.f), MaxDistance(10000.f), MinDistance(1.f), Pitch(1.f), Loop(false) {}
	float Gain;
	float MaxDistance;
	float MinDistance;
	float Pitch;
	bool Loop;
	std::string Path;
	SoundType type;

	virtual SoundEmitter* Clone() const override { return new SoundEmitter(*this); }
};

}
#endif // !Components_SoundEmitter_h__