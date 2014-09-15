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
#include "FollowSystem.h"
#include "World.h"

void Systems::FollowSystem::RegisterComponents( ComponentFactory* cf )
{
	cf->Register<Components::Follow>([]() { return new Components::Follow(); });
}

void Systems::FollowSystem::Update( double dt )
{

}

void Systems::FollowSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{
	auto followComponent = m_World->GetComponent<Components::Follow>(entity);
	auto transformComponent = m_World->GetComponent<Components::Transform>(entity);
	if(!followComponent || !transformComponent)
		return;
	auto absoluteTransformTarget = m_World->GetSystem<Systems::TransformSystem>()->AbsoluteTransform(followComponent->Entity);

	glm::vec3 Offset = (absoluteTransformTarget.Orientation * glm::normalize(absoluteTransformTarget.Position) * followComponent->Distance);
	transformComponent->Position = (absoluteTransformTarget.Position + Offset);
	transformComponent->Orientation = -glm::quat(glm::eulerAngles(absoluteTransformTarget.Orientation) * followComponent->FollowAxis);
}
