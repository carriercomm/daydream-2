#ifndef Component_h__
#define Component_h__

#include "Util/Factory.h"
#include "Core/Entity.h"

struct Component
{
	EntityID Entity;

	virtual Component* Clone() const = 0;
};

class ComponentFactory : public Factory<Component*> { };

#endif // Component_h__