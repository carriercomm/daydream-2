#ifndef Events_BindGamepadAxis_h__
#define Events_BindGamepadAxis_h__

#include "Core/EventBroker.h"
#include "Core/EGamepadAxis.h"

namespace Events
{

struct BindGamepadAxis : Event
{
	Gamepad::Axis Axis;
	std::string Command;
	float Value;
};

}

#endif // Events_BindGamepadAxis_h__