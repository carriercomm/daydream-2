#ifndef Events_KeyUp_h__
#define Events_KeyUp_h__

#include "Core/EventBroker.h"

namespace Events
{

/** Thrown on key release. */
struct KeyUp : Event
{
	/** GLFW key code */
	int KeyCode;
};

}

#endif // Events_KeyUp_h__