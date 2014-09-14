#ifndef Event_StopSound_h__
#define Event_StopSound_h__

#include "Core/EventBroker.h"
#include "Core/Entity.h"

namespace Events
{

struct StopSound : Event
{
	EntityID Emitter;
};

}

#endif // Event_StopSound_h__
