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
#include "DebugSystem.h"
#include "World.h"


void Systems::DebugSystem::Initialize()
{
	// Subscribe to events
	m_EKeyDown = decltype(m_EKeyDown)(std::bind(&Systems::DebugSystem::OnKeyDown, this, std::placeholders::_1));
	EventBroker->Subscribe(m_EKeyDown);
}

void Systems::DebugSystem::Update(double dt)
{

}

bool Systems::DebugSystem::OnKeyDown(const Events::KeyDown &event)
{
	if (event.KeyCode == GLFW_KEY_ENTER)
	{
		Events::PlaySFX e;
		e.Position = glm::vec3(0);
		e.Resource = "Sounds/korvring.wav";
		EventBroker->Publish<Events::PlaySFX>(e);

		return true;
	}

	return false;
}
