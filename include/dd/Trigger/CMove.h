#ifndef Components_Move_h__
#define Components_Move_h__

#include "Core/Component.h"

namespace Components
{

struct Move : Component
{
	float Speed;
	glm::vec3 StartPosition;
	glm::vec3 GoalPosition;
};

}

#endif // Components_Move_h__