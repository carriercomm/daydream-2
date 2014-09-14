#ifndef Events_LeaveTrigger_h__
#define Events_LeaveTrigger_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

/** Thrown when an entity _completely_ leaves a trigger volume. */
struct LeaveTrigger : Event
{
	/** The trigger that was left. */
	EntityID Trigger;
	/** The entity that triggered the event. */
	EntityID Entity;
};

}

#endif // Events_LeaveTrigger_h__