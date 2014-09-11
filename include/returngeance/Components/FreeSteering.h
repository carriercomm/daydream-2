#ifndef FreeSteering_h__
#define FreeSteering_h__

#include "Component.h"

namespace Components
{
struct FreeSteering : Component
{
	FreeSteering() : Speed(35) { }
	float Speed;

	virtual FreeSteering* Clone() const override { return new FreeSteering(*this); }
};
}

#endif // FreeSteering_h__