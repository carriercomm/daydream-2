#ifndef Events_LockMouse_h__
#define Events_LockMouse_h__

#include "Core/EventBroker.h"

namespace Events
{

struct LockMouse : Event { };
struct UnlockMouse : Event { };

}

#endif // Events_LockMouse_h__