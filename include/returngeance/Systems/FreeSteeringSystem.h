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