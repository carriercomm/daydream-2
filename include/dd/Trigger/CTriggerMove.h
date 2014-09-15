#ifndef TriggerMove_h__
#define TriggerMove_h__

#include "Core/Component.h"

namespace Components
{

struct TriggerMove : Component
{
	TriggerMove()
		: Queue(false)
		, Swap(true)
	{ }

	EntityID Entity;
	bool Queue;
	bool Swap;
};

}

#endif // TriggerMove_h__