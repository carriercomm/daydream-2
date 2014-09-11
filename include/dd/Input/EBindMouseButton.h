#ifndef Events_BindMouseButton_h__
#define Events_BindMouseButton_h__

#include "Core/EventBroker.h"

namespace Events
{

struct BindMouseButton : Event
{
	int Button;
	std::string Command;
	float Value;
};

}

#endif // Events_BindMouseButton_h__