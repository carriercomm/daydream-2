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

#ifndef DebugSystem_h__
#define DebugSystem_h__

#include "System.h"
#include "Events/CastRay.h"

namespace Systems
{

class RaySystem : public System
{
public:
	RaySystem(World* world, std::shared_ptr<::EventBroker> eventBroker)
		: System(world, eventBroker) { }

	void Initialize() override;

	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

private:
	struct Ray
	{
		glm::vec3 Direction;
	};

	EventRelay<Events::CastRay> m_ECastRay;
	bool OnCastRay(const Events::CastRay &event);

	std::list<Ray> m_UnresolvedRays;
	//void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
};

}
#endif // DebugSystem_h__