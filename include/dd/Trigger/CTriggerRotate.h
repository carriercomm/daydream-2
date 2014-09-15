#ifndef TriggerRotate_h__
#define TriggerRotate_h__

#include "Core/Component.h"

namespace Components
{

struct TriggerRotate : Component
{
	TriggerRotate()
		: Queue(false)
		, Swap(true)
	{ }

	EntityID Entity;
	bool Queue;
	bool Swap;
};

}

#endif // TriggerRotate_h__