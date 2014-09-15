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

#ifndef GarageSystem_h__
#define GarageSystem_h__

#include <set>

#include "System.h"
#include "Components/Transform.h"
#include "Components/Trigger.h"
#include "Components/Garage.h"
#include "Components/SpawnPoint.h"
#include "Events/EnterTrigger.h"
#include "Events/LeaveTrigger.h"
#include "Events/SpawnVehicle.h"
#include "Events/InputCommand.h"

#include "Components/Player.h"
#include "Events/Move.h"
#include "Events/Rotate.h"
#include "Components/Move.h"
#include "Components/Rotate.h"
#include "Components/Team.h"
#include "Components/Flag.h"
#include "Events/FlagCaptured.h"

namespace Systems
{
	class GarageSystem : public System
	{
	public:

		GarageSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }

		void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;
		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

	private:
		std::map<EntityID, std::set<EntityID>> m_EntitiesInTrigger;
		
		EventRelay<GarageSystem, Events::EnterTrigger> m_EEnterTrigger;
		bool OnEnterTrigger(const Events::EnterTrigger &event);
		EventRelay<GarageSystem, Events::LeaveTrigger> m_ELeaveTrigger;
		bool OnLeaveTrigger(const Events::LeaveTrigger &event);
		EventRelay<GarageSystem, Events::InputCommand> m_ECommand;
		bool OnCommand(const Events::InputCommand &event);

		void ToggleGarage(Components::Garage* garageComponent);
	
	};

}
#endif // GarageSystem_h__
