#ifndef Trigger_h__
#define Trigger_h__

#include "Core/Component.h"

namespace Components
{

struct Trigger : Component
{
	bool TriggerOnce;
	int TeamID;
};

}

#endif // Trigger_h__