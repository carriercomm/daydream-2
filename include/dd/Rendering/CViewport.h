#ifndef Components_Viewport_h__
#define Components_Viewport_h__

#include "Core/Component.h"

namespace Components
{

struct Viewport : Component
{
	Viewport()
		: Left(0.f)
		, Top(0.f)
		, Right(1.f)
		, Bottom(1.f)
		, Camera(0) { }

	float Left;
	float Top;
	float Right;
	float Bottom;

	EntityID Camera;
};

}
#endif // Components_Viewport_h__