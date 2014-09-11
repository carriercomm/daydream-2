#ifndef Components_Listener_h__
#define Components_Listener_h__

#include "Core/Component.h"

namespace Components
{

struct Listener : Component
{
	Listener() {} 
		
	virtual Listener* Clone() const override { return new Listener(*this); }
};

}

#endif // !Components_Listener_h__