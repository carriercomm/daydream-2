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

#ifndef GUI_Viewport_h__
#define GUI_Viewport_h__

#include <memory>

#include "GUI/Frame.h"
#include "World.h"
#include "Systems/TransformSystem.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "RenderQueue.h"
#include "Camera.h"

namespace GUI
{

class Viewport : public Frame
{
public:
	Viewport(Frame* parent, std::string name, std::shared_ptr<World> world)
		: Frame(parent, name)
		, m_World(world)
	{ }

	EntityID CameraEntity() const { return m_CameraEntity; }
	void SetCameraEntity(EntityID cameraEntity) 
	{ 
		m_CameraEntity = cameraEntity;
		auto transformComponent = m_World->GetComponent<Components::Transform>(cameraEntity);
		if (!transformComponent)
			return;
		auto cameraComponent = m_World->GetComponent<Components::Camera>(cameraEntity);
		if (!cameraComponent)
			return;

		m_Camera = std::make_shared<Camera>(cameraComponent->FOV, cameraComponent->NearClip, cameraComponent->FarClip);
	}


	void Update(double dt) override
	{
		if (!m_TransformSystem)
			m_TransformSystem = m_World->GetSystem<Systems::TransformSystem>();

		auto transformComponent = m_World->GetComponent<Components::Transform>(m_CameraEntity);
		if (!transformComponent)
			return;
		
		auto cameraComponent = m_World->GetComponent<Components::Camera>(m_CameraEntity);
		if (!cameraComponent)
			return;

		Components::Transform absoluteTransform = m_TransformSystem->AbsoluteTransform(m_CameraEntity);
		
		m_Camera->SetFOV(cameraComponent->FOV);
		m_Camera->SetNearClip(cameraComponent->NearClip);
		m_Camera->SetFarClip(cameraComponent->FarClip);
		m_Camera->SetPosition(absoluteTransform.Position);
		m_Camera->SetOrientation(absoluteTransform.Orientation);
	}

	void Draw(std::shared_ptr<Renderer> renderer) override
	{
		if (!m_Camera)
			return;

		renderer->SetCamera(m_Camera);
		renderer->SetViewport(AbsoluteRectangle());
		renderer->DrawWorld(m_Parent->RenderQueue);
	}

private:
	std::shared_ptr<World> m_World;
	std::shared_ptr<Systems::TransformSystem> m_TransformSystem;
	std::shared_ptr<Camera> m_Camera;
	EntityID m_CameraEntity;
};

}

#endif // GUI_Viewport_h__
