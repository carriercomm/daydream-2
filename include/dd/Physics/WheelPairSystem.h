#ifndef Systems_WheelPairSystem_h__
#define Systems_WheelPairSystem_h__

#include "Core/World.h"
#include "Core/System.h"
#include "Core/CTransform.h"
#include "CWheelPair.h"

namespace Systems
{

class WheelPairSystem : public System
{
public:

	WheelPairSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager) { }

	void RegisterComponents(ComponentFactory* cf) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
};

}
#endif // Systems_WheelPairSystem_h__
