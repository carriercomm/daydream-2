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

#include "PrecompiledHeader.h"
#include "Sound.h"


Sound::Sound(std::string path, FMOD_SYSTEM* system, Components::SoundEmitter::SoundType type)
{
	if(type == Components::SoundEmitter::SoundType::SOUND_2D)
	{
		FMOD_System_CreateSound(system, path.c_str(), FMOD_2D, NULL, &m_Sound);
	}
	if(type == Components::SoundEmitter::SoundType::SOUND_3D)
	{
		FMOD_System_CreateSound(system, path.c_str(), FMOD_3D, NULL, &m_Sound);
	}
}

Sound::~Sound()
{
	 FMOD_Sound_Release(m_Sound);
}