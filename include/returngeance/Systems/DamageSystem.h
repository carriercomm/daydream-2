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

#ifndef DamageSystem_h__
#define DamageSystem_h__


#include "System.h"
#include "Components/Health.h"
#include "Components/DamageModel.h"
#include "Events/Damage.h"
#include "Events/Dead.h"

namespace Systems
{
	class DamageSystem : public System
	{
	public:

		DamageSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }


		void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;



		EventRelay<DamageSystem, Events::Damage> m_EDamage;
		bool OnDamage(const Events::Damage &event);

	private:

	};

}
#endif // DamageSystem_h__
