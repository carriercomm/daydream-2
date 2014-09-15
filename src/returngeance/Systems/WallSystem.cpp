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
#include "WallSystem.h"
#include "World.h"

void Systems::WallSystem::RegisterComponents( ComponentFactory* cf )
{
	cf->Register<Components::Wall>([]() { return new Components::Wall(); });
}

void Systems::WallSystem::Initialize()
{
	EVENT_SUBSCRIBE_MEMBER(m_eDamage, &Systems::WallSystem::Damage);
}

bool Systems::WallSystem::Damage( const Events::Damage &event )
{
	auto wallComponent = m_World->GetComponent<Components::Wall>(event.Entity);
	if(!wallComponent)
	{
		return false;
	}
	LOG_INFO("WallSystem::Damage");

	// Change to damage model
	auto modelComponent = m_World->GetComponent<Components::Model>(event.Entity);
	auto damageModel = m_World->GetComponent<Components::DamageModel>(event.Entity);
	if (modelComponent)
	{
		modelComponent->ModelFile = damageModel->ModelFile;
		modelComponent->Color = damageModel->Color;
		modelComponent->ShadowCaster = damageModel->ShadowCaster;
		modelComponent->Transparent = damageModel->Transparent;
	}

	auto wallhealthcomponent = m_World->GetComponent<Components::Health>(event.Entity);
	if(wallhealthcomponent->Amount > 0)
	{
		return false;
	}
	LOG_INFO("Entity %i is dead", event.Entity);
	//auto transformComponent = m_World->GetComponent<Components::Transform>(event.Entity);
	Components::Transform transformComponent = m_World->GetSystem<Systems::TransformSystem>()->AbsoluteTransform(event.Entity);

	// Spawn debris
	for(auto d : wallComponent->Walldebris)
	{
		auto debris = m_World->CloneEntity(d);
		
		auto transform = m_World->GetComponent<Components::Transform>(debris);
		transform->Orientation = transform->Orientation * transformComponent.Orientation;
		transform->Position = transform->Orientation * transform->Position + transformComponent.Position;
		
		//DO STUFF! :D
		float distance = glm::distance(transform->Position, transformComponent.Position);
		float radius = 5.f;
		float strength = (1.f - pow(distance / radius, 2)) * 20.f;
		glm::vec3 direction = glm::normalize(transformComponent.Position - transform->Position);

		Events::ApplyPointImpulse e;
		e.Entity = debris;
		e.Impulse = direction * strength;
		e.Position = transformComponent.Position;
		EventBroker->Publish(e);
	}

	m_World->RemoveEntity(event.Entity);
	return true;
}