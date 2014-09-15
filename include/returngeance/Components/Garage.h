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

#ifndef Components_Garage_h__
#define Components_Garage_h__

#include "Component.h"

namespace Components
{
	struct Garage : Component
	{
		Garage()
			: Open(false)
			, Elevator(0)
			, DoorLeft(0)
			, DoorRight(0)
			, Light1(0)
			, Light2(0)
			, Light3(0)
			, Light4(0)
		{ }

		EntityID Elevator;
		EntityID DoorLeft;
		EntityID DoorRight;
		EntityID Light1;
		EntityID Light2;
		EntityID Light3;
		EntityID Light4;

		bool Open;

		virtual Garage* Clone() const override { return new Garage(*this); }
	};
}

#endif // Components_TankShell_h__
