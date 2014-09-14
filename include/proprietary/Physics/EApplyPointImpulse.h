#ifndef Events_ApplyPointImpulse_h__
#define Events_ApplyPointImpulse_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct ApplyPointImpulse : Event
{
	EntityID Entity;
	glm::vec3 Position;
	glm::vec3 Impulse;
};

}

#endif // Events_ApplyPointImpulse_h__