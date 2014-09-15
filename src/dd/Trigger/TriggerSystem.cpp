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
#include "Trigger/TriggerSystem.h"
#include "Core/World.h"

void Systems::TriggerSystem::RegisterComponents( ComponentFactory* cf )
{
	cf->Register<Components::Trigger>([]() { return new Components::Trigger(); });
	cf->Register<Components::TriggerExplosion>([]() { return new Components::TriggerExplosion(); });
	cf->Register<Components::TriggerMove>([]() { return new Components::TriggerMove(); });
	cf->Register<Components::TriggerRotate>([]() { return new Components::TriggerRotate(); });
}

void Systems::TriggerSystem::Initialize()
{
	EVENT_SUBSCRIBE_MEMBER(m_EEnterTrigger, &Systems::TriggerSystem::OnEnterTrigger);
	EVENT_SUBSCRIBE_MEMBER(m_ELeaveTrigger, &Systems::TriggerSystem::OnLeaveTrigger);
}

void Systems::TriggerSystem::Update( double dt )
{

}

void Systems::TriggerSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{

}


void Systems::TriggerSystem::OnComponentRemoved(EntityID entity, std::string type, Component* component )
{

}

void Systems::TriggerSystem::OnEntityCommit( EntityID entity )
{

}

void Systems::TriggerSystem::OnEntityRemoved( EntityID entity )
{

}

bool Systems::TriggerSystem::OnEnterTrigger( const Events::EnterTrigger &event )
{
	auto triggerMoveComponent = m_World->GetComponent<Components::TriggerMove>(event.Trigger);
	if (triggerMoveComponent)
	{
		Move(triggerMoveComponent->Entity, triggerMoveComponent->Queue, triggerMoveComponent->Swap);
	}

	auto triggerRotateComponent = m_World->GetComponent<Components::TriggerRotate>(event.Trigger);
	if (triggerRotateComponent)
	{
		Rotate(triggerMoveComponent->Entity, triggerMoveComponent->Queue, triggerMoveComponent->Swap);
	}

	return true;
}


bool Systems::TriggerSystem::OnLeaveTrigger( const Events::LeaveTrigger &event )
{
	auto triggerMoveComponent = m_World->GetComponent<Components::TriggerMove>(event.Trigger);
	if (triggerMoveComponent)
	{
		Move(triggerMoveComponent->Entity, triggerMoveComponent->Queue, triggerMoveComponent->Swap);
	}

	auto triggerRotateComponent = m_World->GetComponent<Components::TriggerRotate>(event.Trigger);
	if (triggerRotateComponent)
	{
		Rotate(triggerMoveComponent->Entity, triggerMoveComponent->Queue, triggerMoveComponent->Swap);
	}

	return true;
}


void Systems::TriggerSystem::Rotate(EntityID entity, bool queue, bool swap)
{
	auto transform = m_World->GetComponent<Components::Transform>(entity);
	auto rotate = m_World->GetComponent<Components::Rotate>(entity);

	Events::Rotate e;
	e.Entity = entity;
	e.GoalRotation = rotate->GoalRotation;
	e.Time = rotate->Time;
	e.Queue = queue;
	EventBroker->Publish(e);

	if (swap)
	{
		std::swap(rotate->GoalRotation, rotate->StartRotation);
	}
}



void Systems::TriggerSystem::Move(EntityID entity, bool queue, bool swap)
{
	auto move = m_World->GetComponent<Components::Move>(entity);
	Events::Move e;
	e.Entity = entity;
	e.GoalPosition = move->GoalPosition;
	e.Speed = move->Speed;
	e.Queue = queue;
	EventBroker->Publish(e);

	if (swap)
	{
		std::swap(move->GoalPosition, move->StartPosition);
	}
}

void Systems::TriggerSystem::Explosion( EntityID entity, EntityID phantomEntity )
{
	/*auto transformComponent = m_World->GetComponent<Components::Transform>(entity);
	auto PhantomTransformComponent = m_World->GetComponent<Components::Transform>(phantomEntity);
	auto explosionComponent = m_World->GetComponent<Components::TriggerExplosion>(phantomEntity);

	if(transformComponent && PhantomTransformComponent)
	{
		// Velocity = (1 - (distance / radius)^2) * Strength;
		glm::vec3 vect = transformComponent->Position - PhantomTransformComponent->Position;
		float distance = glm::length(vect);
		float radius = explosionComponent->Radius;
		float velocity = (1.f - pow(distance / radius, 2)) * explosionComponent->MaxVelocity;

		glm::vec3 direction = glm::normalize(transformComponent->Position - PhantomTransformComponent->Position);

		Events::SetVelocity e;
		e.Entity = entity;
		e.Velocity = direction*velocity;
		EventBroker->Publish(e);

		m_World->RemoveEntity(phantomEntity);
	}*/
	
	
}



