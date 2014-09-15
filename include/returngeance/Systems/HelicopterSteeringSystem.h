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

#include "System.h"
#include "Components/Transform.h"
#include "Components/HelicopterSteering.h"
#include "Events/SetVelocity.h"
#include "Events/ApplyForce.h"
#include "InputController.h"

namespace Systems
{

class HelicopterSteeringSystem : public System
{
public:
	HelicopterSteeringSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager)
	{ }

	void RegisterComponents(ComponentFactory* cf) override;
	void Initialize() override;

	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

private:
	class HelicopterSteeringInputController;
	std::unique_ptr<HelicopterSteeringInputController> m_InputController;

	std::map<EntityID, double> m_TimeSinceLastShot;
};

class HelicopterSteeringSystem::HelicopterSteeringInputController : InputController<HelicopterSteeringSystem>
{
public:
	HelicopterSteeringInputController(std::shared_ptr<::EventBroker> eventBroker)
		: InputController(eventBroker)
		, Power(0.f)
	{ }

	float Power;
	glm::vec3 Rotation;

	void Update(double dt);
	
protected:
	bool OnCommand(const Events::InputCommand &event) override;
	bool OnMouseMove(const Events::MouseMove &event) override;

	
};





}