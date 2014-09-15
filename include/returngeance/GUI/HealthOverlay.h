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

#ifndef GUI_HealthOverlay_h__
#define GUI_HealthOverlay_h__

#include "GUI/TextureFrame.h"
#include "World.h"
#include "Events/Damage.h"
#include "Components/Player.h"
#include "Components/Health.h"

namespace GUI
{

	class HealthOverlay : public TextureFrame
	{
	public:
		HealthOverlay(Frame* parent, std::string name, std::shared_ptr<World> world, int playerID)
			: TextureFrame(parent, name)
			, m_World(world)
			, m_PlayerID(playerID)
		{ 
			EVENT_SUBSCRIBE_MEMBER(m_EDamage, &HealthOverlay::OnDamage);
			
			SetTexture("Textures/GUI/hurt.png");
			SetColor(glm::vec4(0.f));
		}
	
		bool OnDamage(const Events::Damage &event)
		{
			auto player = m_World->GetComponent<Components::Player>(event.Entity);
			if (!player)
				return false;

			if (player->ID != m_PlayerID)
				return false;

			auto health = m_World->GetComponent<Components::Health>(event.Entity);
			if (!health)
				return false;
	
			SetColor(glm::vec4(1.f, 1.f, 1.f, 1 - (health->Amount / 100.f / 2.f)));

			return true;
		}

	protected:
		std::shared_ptr<World> m_World;
		int m_PlayerID;
		EventRelay<Frame, Events::Damage> m_EDamage;
	};

}

#endif // GUI_TextureFrame_h__
