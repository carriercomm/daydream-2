#ifndef Components_Model_h__
#define Components_Model_h__

#include <string>

#include "Core/Component.h"

namespace Components
{

struct Model : Component
{
	Model() : Color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), Visible(true), ShadowCaster(true), Transparent(false), AverageNormals(false) { }
	std::string ModelFile;
	glm::vec4 Color;
	bool Visible;
	bool ShadowCaster;
	bool Transparent;
	bool AverageNormals;
};

}
#endif // !Components_Model_h__