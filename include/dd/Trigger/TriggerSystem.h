#ifndef TriggerSystem_h__
#define TriggerSystem_h__

#include <unordered_map>
#include <math.h>

#include "Core/System.h"
#include "Core/CTransform.h"
#include "Transform/EMove.h"
#include "Transform/ERotate.h"

#include "CTrigger.h"
#include "CTriggerExplosion.h"
#include "CTriggerMove.h"
#include "CMove.h"
#include "CTriggerRotate.h"
#include "CRotate.h"
#include "EEnterTrigger.h"
#include "ELeaveTrigger.h"

namespace Systems
{
	class TriggerSystem : public System
	{
	public:
		TriggerSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }

		void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;
		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
		//void OnComponentCreated(std::string type, std::shared_ptr<Component> component) override;
		void OnComponentRemoved(EntityID entity, std::string type, Component* component) override;
		void OnEntityCommit(EntityID entity) override;
		void OnEntityRemoved(EntityID entity) override;

		EventRelay<TriggerSystem, Events::EnterTrigger> m_EEnterTrigger;
		bool OnEnterTrigger(const Events::EnterTrigger &event);
		EventRelay<TriggerSystem, Events::LeaveTrigger> m_ELeaveTrigger;
		bool OnLeaveTrigger(const Events::LeaveTrigger &event);
	private:
		void Explosion(EntityID entity, EntityID phantomEntity);
		void Move(EntityID entity, bool queue, bool swap);
		void Rotate(EntityID entity, bool queue, bool swap);
	};

}
#endif // TriggerSystem_h__
