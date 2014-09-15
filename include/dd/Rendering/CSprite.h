#ifndef Components_Sprite_h__
#define Components_Sprite_h__

#include <string>

#include "Core/Component.h"

namespace Components
{

struct Sprite : Component
{
	Sprite() : Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) { }

	std::string SpriteFile;
	glm::vec4 Color;
};

}
#endif // !Components_Sprite_h__