#ifndef Events_LeaveTrigger_h__
#define Events_LeaveTrigger_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct LeaveTrigger : Event
{
	EntityID Trigger;
	EntityID Entity;
};

}

#endif // Events_LeaveTrigger_h__