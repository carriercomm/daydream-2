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

#ifndef FlagSystem_h__
#define FlagSystem_h__


#include "System.h"
#include "Components/Flag.h"
#include "Components/Player.h"
#include "Components/Team.h"
#include "Components/Trigger.h"
#include "Components/Transform.h"
#include "Components/JeepSteering.h"

#include "Events/FlagCaptured.h"
#include "Events/FlagDropped.h"
#include "Events/FlagPickup.h"
#include "Events/FlagReturned.h"


#include "Events/EnterTrigger.h"

namespace Systems
{
	class FlagSystem : public System
	{
	public:

		FlagSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }


		void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;
		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

	private:
		EventRelay<FlagSystem, Events::EnterTrigger> m_EEnterTrigger;
		bool OnEnterTrigger(const Events::EnterTrigger &event);

		void PickUpFlag(EntityID entity, EntityID trigger);
	};

}
#endif // DamageSystem_h__
