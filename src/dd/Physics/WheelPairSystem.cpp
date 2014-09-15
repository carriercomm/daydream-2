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
#include "Physics/WheelPairSystem.h"
#include "Core/World.h"

void Systems::WheelPairSystem::RegisterComponents(ComponentFactory* cf)
{
	cf->Register<Components::WheelPair>([]() { return new Components::WheelPair(); });
}

void Systems::WheelPairSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	auto wheelPair = m_World->GetComponent<Components::WheelPair>(entity);
	if (!wheelPair)
		return;

	auto transform = m_World->GetComponent<Components::Transform>(entity);
	if (!transform)
		return;
	auto transformFakeFront = m_World->GetComponent<Components::Transform>(wheelPair->FakeWheelFront);
	if (!transformFakeFront)
		return;
	auto transformFakeBack = m_World->GetComponent<Components::Transform>(wheelPair->FakeWheelBack);
	if (!transformFakeBack)
		return;

	glm::vec3 thing = transformFakeBack->Position - transformFakeFront->Position;

	float height = ((transformFakeFront->Position + transformFakeBack->Position) / 2.f).y;
	float angle = std::atan2f(thing.y, thing.z);

	transform->Position.y = height;
	transform->Orientation = glm::quat(glm::eulerAngles(transform->Orientation) * glm::vec3(0, 1, 1) + glm::vec3(-angle, 0, 0));
}