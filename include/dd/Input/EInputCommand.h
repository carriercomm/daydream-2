#ifndef Events_InputCommand_h__
#define Events_InputCommand_h__

#include "Core/EventBroker.h"

namespace Events
{

struct InputCommand : Event
{
	unsigned int PlayerID;
	std::string Command;
	float Value;
};

}

#endif // Events_InputCommand_h__