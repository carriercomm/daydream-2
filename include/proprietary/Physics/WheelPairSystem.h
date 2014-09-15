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
