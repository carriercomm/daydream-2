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
#include "FreeSteeringSystem.h"
#include "World.h"

void Systems::FreeSteeringSystem::RegisterComponents(ComponentFactory* cf)
{
	cf->Register<Components::FreeSteering>([]() { return new Components::FreeSteering(); });
}

void Systems::FreeSteeringSystem::Initialize()
{
	m_InputController = std::unique_ptr<FreeSteeringInputController>(new FreeSteeringInputController(EventBroker));
}

void Systems::FreeSteeringSystem::Update(double dt)
{
	
}

void Systems::FreeSteeringSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	auto steering = m_World->GetComponent<Components::FreeSteering>(entity);
	if (steering)
	{
		auto transform = m_World->GetComponent<Components::Transform>(entity);

		glm::vec3 cameraRight = glm::vec3(transform->Orientation * glm::vec4(1, 0, 0, 0));
		glm::vec3 cameraForward = glm::vec3(transform->Orientation * glm::vec4(0, 0, -1, 0));
		glm::vec3 movement;
		movement += cameraRight * m_InputController->Movement.x;
		movement.y += m_InputController->Movement.y;
		movement += cameraForward * -m_InputController->Movement.z;
		float speedMultiplier = 1.f;
		if (m_InputController->SpeedMultiplier > 0)
			speedMultiplier *= 4;
		else if (m_InputController->SpeedMultiplier < 0)
			speedMultiplier /= 4;

		transform->Position += movement * steering->Speed * speedMultiplier * (float)dt;

		glm::quat mouseOrientationPitch = glm::quat(m_InputController->MouseOrientation * glm::vec3(1, 0, 0));
		glm::quat mouseOrientationYaw = glm::quat(m_InputController->MouseOrientation * glm::vec3(0, 1, 0));
		m_InputController->MouseOrientation = glm::vec3(0);

		glm::vec3 controllerOrientationEuler = m_InputController->ControllerOrientation * (float)dt;
		glm::quat controllerOrientationPitch = glm::quat(controllerOrientationEuler * glm::vec3(1, 0, 0));
		glm::quat controllerOrientationYaw = glm::quat(controllerOrientationEuler * glm::vec3(0, 1, 0));

		// TOUCHING THIS CODE MIGHT CAUSE THE UNIVERSE TO IMPLODE, ALSO DRAGONS
		//---------------------------------------------------------------------
		transform->Orientation = (mouseOrientationYaw * controllerOrientationYaw)
			* transform->Orientation 
			* (mouseOrientationPitch * controllerOrientationPitch);
		//---------------------------------------------------------------------
		// TOUCHING THIS CODE MIGHT CAUSE THE UNIVERSE TO IMPLODE, ALSO DRAGONS
	}
}

bool Systems::FreeSteeringSystem::FreeSteeringInputController::OnCommand(const Events::InputCommand &event)
{
	// Movement
	if (event.Command == "cam_vertical")
	{
		Movement.z = -event.Value;
	}
	else if (event.Command == "cam_horizontal")
	{
		Movement.x = event.Value;
	}
	else if (event.Command == "cam_normal")
	{
		Movement.y = event.Value;
	}

	// Speed
	else if (event.Command == "cam_speed")
	{
		SpeedMultiplier = event.Value;
	}

	// Mouse click
	else if (event.Command == "cam_lock")
	{
		OrientationActive = event.Value > 0;

		if (OrientationActive)
		{
			Events::LockMouse e;
			EventBroker->Publish(e);
		}
		else
		{
			Events::UnlockMouse e;
			EventBroker->Publish(e);
		}
	}

	else if (event.Command == "cam_vertical2")
	{
		ControllerOrientation.x = event.Value;
	}
	else if (event.Command == "cam_horizontal2")
	{
		ControllerOrientation.y = -event.Value;
	}

	return true;
}

bool Systems::FreeSteeringSystem::FreeSteeringInputController::OnMouseMove(const Events::MouseMove &event)
{
	if (OrientationActive)
	{
		MouseOrientation = -glm::vec3(event.DeltaY / 300.f, event.DeltaX / 300.f, 0.f);
		LOG_DEBUG("Mouse DX: %f", event.DeltaX);
	}

	return true;
}
