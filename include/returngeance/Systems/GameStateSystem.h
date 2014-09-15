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

#ifndef GameStateSystem_h__
#define GameStateSystem_h__

#include <set>

#include "System.h"
#include "Components/Transform.h"
#include "Components/Player.h"
#include "Events/FlagCaptured.h"
#include "Events/GameOver.h"
#include "Events/PlayBGM.h"

namespace Systems
{

class GameStateSystem : public System
{
public:

	GameStateSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager) 
		, m_InGame(true)
	{ }

	void Initialize() override;

	bool InGame() const { return m_InGame; }

private:
	bool m_InGame;

	EventRelay<GameStateSystem, Events::FlagCaptured> m_EFlagCaptured;
	bool OnFlagCaptured(const Events::FlagCaptured &event);
};

}

#endif // GameStateSystem_h__
