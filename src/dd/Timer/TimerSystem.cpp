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
#include "Timer/TimerSystem.h"
#include "Core/World.h"

void dd::Systems::TimerSystem::RegisterComponents( ComponentFactory* cf )
{
	cf->Register<Components::Timer>([]() { return new Components::Timer(); });
	cf->Register<Components::FrameTimer>([]() { return new Components::FrameTimer(); });
}

void dd::Systems::TimerSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{
	auto timer = m_World->GetComponent<Components::Timer>(entity);
	if(timer)
	{
		timer->Time -= dt;
		
		if(timer->Time <= 0)
		{
			m_World->RemoveEntity(entity);
		}
	}

	auto frameTimer = m_World->GetComponent<Components::FrameTimer>(entity);
	if(frameTimer)
	{
		frameTimer->Frames -= 1;

		if(frameTimer->Frames <= 0)
		{
			m_World->RemoveEntity(entity);
		}
	}

	
}


