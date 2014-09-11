#ifndef Event_PlayBGM_h__
#define Event_PlayBGM_h__

#include "Core/EventBroker.h"

namespace Events
{

struct PlayBGM : Event
{
	std::string Resource;
	bool Loop;
};

}

#endif // Event_PlayBGM_h__
