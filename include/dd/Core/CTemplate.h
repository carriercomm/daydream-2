#ifndef Components_Template_h__
#define Components_Template_h__

#include "Core/Component.h"

namespace Components
{

struct Template : public Component 
{
	virtual Template* Clone() const override { return nullptr; }
};

}

#endif // !Components_Template_h__