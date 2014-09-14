#ifndef Event_ComponentCreated_h__
#define Event_ComponentCreated_h__

#include "EventBroker.h"
#include "Entity.h"
#include "Component.h"

namespace Events
{

/** Thrown when a new component is created and attached to an entity. */
struct ComponentCreated : Event
{
	/** The entity the component was attached to. */
	EntityID Entity;
	/** Pointer to the newly created component. */
	std::shared_ptr<::Component> Component;
};

}

#endif // Event_ComponentCreated_h__
