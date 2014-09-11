#ifndef Components_HingeConstraint_h__
#define Components_HingeConstraint_h__

#include "Core/Component.h"

namespace Components
{

struct HingeConstraint : Component
{
	EntityID LinkedEntity;
	glm::vec3 Pivot;
	glm::vec3 Axis;

	virtual HingeConstraint* Clone() const override { return new HingeConstraint(*this); }
};

}

#endif // Components_HingeConstraint_h__
