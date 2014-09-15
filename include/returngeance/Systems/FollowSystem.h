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

#ifndef FollowSystem_h__
#define FollowSystem_h__


#include "System.h"
#include "Systems/TransformSystem.h"
#include "Components/Transform.h"
#include "Components/Follow.h"

#include "Events/Move.h"
#include "Events/Rotate.h"


namespace Systems
{
	class FollowSystem : public System
	{
	public:

		FollowSystem(World* world, std::shared_ptr<::EventBroker> eventBroker, std::shared_ptr<::ResourceManager> resourceManager)
			: System(world, eventBroker, resourceManager) { }

		//void Initialize() override;
		void RegisterComponents(ComponentFactory* cf) override;
		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
		/*void OnComponentCreated(std::string type, std::shared_ptr<Component> component) override;
		void OnComponentRemoved(EntityID entity, std::string type, Component* component) override;
		void OnEntityCommit(EntityID entity) override;
		void OnEntityRemoved(EntityID entity) override;*/

	private:

	};

}
#endif // FollowSystem_h__
