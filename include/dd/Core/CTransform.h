#ifndef Components_Transform_h__
#define Components_Transform_h__

#include "Core/Component.h"

namespace Components
{

/** Spatial data of an entity. */
struct Transform : public Component
{
	Transform()
		: Scale(glm::vec3(1.f)) { }

	/** Position in world coordinates (meters). */
	glm::vec3 Position;
	/** Orientation in quaternion form. */
	glm::quat Orientation;
	/** Current velocity of the entity in m/s. */
	glm::vec3 Velocity;
	/** Physical scale multiplier. */
	glm::vec3 Scale;
};

}

#endif // Components_Transform_h__
