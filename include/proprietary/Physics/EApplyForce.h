#ifndef Events_ApplyForce_h__
#define Events_ApplyForce_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct ApplyForce : Event
{
	EntityID Entity;
	double DeltaTime;
	glm::vec3 Force;
};

}

#endif // Events_ApplyForce_h__