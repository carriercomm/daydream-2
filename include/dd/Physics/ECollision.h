#ifndef Events_Collision_h__
#define Events_Collision_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct Collision : Event
{
	EntityID Entity1;
	EntityID Entity2;
};

}

#endif // Events_Collision_h__