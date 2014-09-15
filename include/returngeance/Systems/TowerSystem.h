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

#ifndef TowerSystem_h__
#define TowerSystem_h__


#include "System.h"
#include "Systems/TransformSystem.h"
#include "Components/Player.h"
#include "Components/Tower.h"
#include "Components/Turret.h"
#include "Components/TurretShot.h"
#include "Components/Health.h"
#include "Components/TowerDebris.h"
#include "Components/Model.h"
#include "Events/SetVelocity.h"
#include "Events/CreateExplosion.h"
#include "Events/Collision.h"
#include "Events/Damage.h"
#include "Events/ApplyPointImpulse.h"






namespace Systems
{
	class TowerSystem : public System
	{
	public:

		TowerSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }


		void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;

		virtual void Update(double dt);
		virtual void UpdateEntity(double dt, EntityID entity, EntityID parent);


		EventRelay<TowerSystem, Events::Collision> m_ECollision;
		bool OnCollision(const Events::Collision &e);
		EventRelay<TowerSystem, Events::Damage> m_eDamage;
		bool Damage(const Events::Damage &event);


	private:
		std::map<EntityID, double> m_TimeSinceLastShot;
		float Temp_m_TimeSinceLastShot;

	};

}
#endif // TowerSystem_h__
