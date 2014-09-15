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

#ifndef WallSystem_h__
#define WallSystem_h__


#include "System.h"
#include "Systems/TransformSystem.h"
#include "Events/Dead.h"
#include "Events/Damage.h"
#include "Events/ApplyPointImpulse.h"
#include "Components/Model.h"
#include "Components/DamageModel.h"
#include "Components/Wall.h"
#include "Components/Transform.h"
#include "Components/Physics.h"
#include "Components/MeshShape.h"
#include "Components/Tankshell.h"
#include "Components/Health.h"



namespace Systems
{
	class WallSystem : public System
	{
	public:

		WallSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }


		void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;



		EventRelay<WallSystem, Events::Damage> m_eDamage;
		bool Damage(const Events::Damage &event);

	private:

	};

}
#endif // WallSystem_h__
