#ifndef TimerSystem_h__
#define TimerSystem_h__

#include "Core/System.h"
#include "Core/CTransform.h"

#include "CTimer.h"
#include "CFrameTimer.h"

namespace Systems
{

class TimerSystem : public System
{
public:
	TimerSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
		: System(world, eventBroker, resourceManager) { }

	void RegisterComponents(ComponentFactory* cf) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

private:

};

}
#endif // TimerSystem_h__
