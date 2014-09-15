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
#include "GameStateSystem.h"
#include "World.h"

void Systems::GameStateSystem::Initialize()
{
	EVENT_SUBSCRIBE_MEMBER(m_EFlagCaptured, &Systems::GameStateSystem::OnFlagCaptured);
}

bool Systems::GameStateSystem::OnFlagCaptured(const Events::FlagCaptured &event)
{
	m_InGame = false;

	Events::GameOver e1;
	e1.Player = event.Player;
	EventBroker->Publish(e1);
	Events::PlayBGM e2;
	e2.Resource = "Sounds/BGM/WilliamTellOverture.mp3";
	EventBroker->Publish(e2);

	return true;
}