#ifndef Texture_h__
#define Texture_h__

#include <string>
#include <unordered_map>
#include <cstdio>

#include "ResourceManager.h"
#include "PNG.h"

class Texture : public Resource
{
private:
	Texture(std::string path);

public:
	static Texture* Create(std::string resourceName) { return new Texture(resourceName); }
	~Texture();

	void Bind(GLenum textureUnit = GL_TEXTURE0);

	operator GLuint() const { return m_Texture; }

private:
	GLuint m_Texture = 0;
};


#endif // Texture_h__
