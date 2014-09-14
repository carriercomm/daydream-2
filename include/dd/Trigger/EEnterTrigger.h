#ifndef Events_EnterTrigger_h__
#define Events_EnterTrigger_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

/** Thrown when an entity _partially_ enters a trigger volume. */
struct EnterTrigger : Event
{
	/** The trigger that was entered. */
	EntityID Trigger;
	/** The entity that triggered the event. */
	EntityID Entity;
};

}

#endif // Events_EnterTrigger_h__