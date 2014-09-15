#ifndef Components_Template_h__
#define Components_Template_h__

#include "Core/Component.h"

namespace Components
{

/** Template flag component.
	
	A template entity is used as a blueprint for cloning. For example, 
	pre-defined particles that a particle emitter will clone and emit into the world.

	Systems __MUST__ ignore entities with a Template component for general processing.

	__Observe:__ Cloning an entity with a Template component will not remove the template component!
*/
struct Template : public Component { };

}

#endif // !Components_Template_h__