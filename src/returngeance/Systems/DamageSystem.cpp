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
#include "DamageSystem.h"
#include "World.h"
void Systems::DamageSystem::RegisterComponents( ComponentFactory* cf )
{
	cf->Register<Components::Health>([]() { return new Components::Health(); });
	cf->Register<Components::DamageModel>([]() { return new Components::DamageModel(); });
}

void Systems::DamageSystem::Initialize()
{

	EVENT_SUBSCRIBE_MEMBER(m_EDamage, &Systems::DamageSystem::OnDamage);
}

bool Systems::DamageSystem::OnDamage( const Events::Damage &event )
{
	if(!m_World->ValidEntity(event.Entity))
		return false;
	auto health = m_World->GetComponent<Components::Health>(event.Entity);
	health->Amount -= event.Amount;
	if(health->Amount <= 0)
	{
		Events::Dead e;
		e.Entity = event.Entity;
		EventBroker->Publish(e);
	}
	return true;
}