#ifndef Events_DisableCollisions_h__
#define Events_DisableCollisions_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct DisableCollisions : Event
{
	int Layer1;
	int Layer2;
};

}

#endif // Events_DisableCollisions_h__