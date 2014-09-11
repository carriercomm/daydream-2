#ifndef Event_Move_h__
#define Event_Move_h__

#include "Core/EventBroker.h"

namespace Events
{

struct Move : Event
{
	EntityID Entity;
	glm::vec3 GoalPosition;
	float Speed;
	bool Queue;
};

}

#endif // Event_Move_h__
