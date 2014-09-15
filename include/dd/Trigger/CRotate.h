#ifndef Components_Rotate_h__
#define Components_Rotate_h__

#include "Core/Component.h"

namespace Components
{

struct Rotate : Component
{
	float Time;
	glm::quat StartRotation;
	glm::quat GoalRotation;
};

}

#endif // Components_Rotate_h__