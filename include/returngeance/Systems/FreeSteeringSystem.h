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

#include <array>

#include "System.h"
#include "Components/Transform.h"
#include "Components/FreeSteering.h"
#include "InputController.h"
#include "Events/LockMouse.h"

namespace Systems
{

class FreeSteeringSystem : public System
{
public:
	FreeSteeringSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager)
	{ }

	void RegisterComponents(ComponentFactory* cf) override;
	void Initialize() override;

	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

private:
	class FreeSteeringInputController;

	std::unique_ptr<FreeSteeringInputController> m_InputController;
};

class FreeSteeringSystem::FreeSteeringInputController : InputController<FreeSteeringSystem>
{
public:
	FreeSteeringInputController(std::shared_ptr<::EventBroker> eventBroker)
		: InputController(eventBroker)
		, SpeedMultiplier(0.f)
		, OrientationActive(false) { }

	glm::vec3 Movement;
	glm::vec3 MouseOrientation;
	glm::vec3 ControllerOrientation;
	float SpeedMultiplier;
	bool OrientationActive;

protected:
	virtual bool OnCommand(const Events::InputCommand &event);
	virtual bool OnMouseMove(const Events::MouseMove &event);
};

}