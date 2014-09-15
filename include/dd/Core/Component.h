#ifndef Component_h__
#define Component_h__

#include "Util/Factory.h"
#include "Core/Entity.h"

struct Component
{
	EntityID Entity;
};

class ComponentFactory : public Factory<Component> { };

#endif // Component_h__