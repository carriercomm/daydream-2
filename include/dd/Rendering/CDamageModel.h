#ifndef Components_DamageModel_h__
#define Components_DamageModel_h__

#include <string>

#include "Core/Component.h"

namespace Components
{

struct DamageModel : Component
{
	DamageModel() 
		: Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		, ShadowCaster(true)
		, Transparent(false)
	{ }
	std::string ModelFile;
	glm::vec4 Color;
	bool ShadowCaster;
	bool Transparent;
};

}
#endif // !Components_DamageModel_h__