/*
	This file is part of Daydream Engine.
	Copyright 2014 Adam Byléhn, Tobias Dahl, Simon Holmberg, Viktor Ljung
	
	Daydream Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Daydream Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Daydream Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef Components_Input_h__
#define Components_Input_h__

#include "Component.h"

namespace Components
{

struct Input : Component
{
	/*Input()
		: Keyboard(false)
		, Mouse(false)
		, GamepadID(0) { }

	bool Keyboard;
	bool Mouse;
	int GamepadID;*/

	virtual Input* Clone() const override { return new Input(*this); }
};

}

#endif // !Components_Input_h__