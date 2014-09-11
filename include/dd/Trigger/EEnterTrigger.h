#ifndef Events_EnterTrigger_h__
#define Events_EnterTrigger_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct EnterTrigger : Event
{
	EntityID Trigger;
	EntityID Entity;
};

}

#endif // Events_EnterTrigger_h__