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

#ifndef Sound_h__
#define Sound_h__

#include <fmod.h>
#include <fmod_errors.h>

#include "Core/ResourceManager.h"

#include "CSoundEmitter.h"

class Sound : public Resource
{
public:
	Sound(std::string path, FMOD_SYSTEM* system, Components::SoundEmitter::SoundType type);
	~Sound();

	operator FMOD_SOUND*() const { return m_Sound; }

private:
	FMOD_SOUND* m_Sound;
};

#endif // Sound_h__
