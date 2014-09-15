#ifndef Components_DirectionalLight_h__
#define Components_DirectionalLight_h__

#include "Core/Component.h"
#include "Core/Color.h"

namespace Components
{

struct DirectionalLight : Component
{
	float Intensity;
	float MaxRange;
	float SpecularIntensity;
	Color Color;
};

}
#endif // !Components_DirectionalLight_h__