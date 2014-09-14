#ifndef RenderQueue_h__
#define RenderQueue_h__

#include <cstdint>
#include <forward_list>

#include "Texture.h"
#include "Model.h"

class RenderQueue;

struct RenderJob
{
	friend class RenderQueue;

	float Depth;

protected:
	uint64_t Hash;

	virtual void CalculateHash() = 0;

	bool operator<(const RenderJob& rhs)
	{
		return this->Hash < rhs.Hash;
	}
};

struct ModelJob : RenderJob
{
	unsigned int ShaderID;
	unsigned int TextureID;

	glm::mat4 ModelMatrix;
	GLuint DiffuseTexture;
	GLuint NormalTexture;
	GLuint SpecularTexture;
	float Shininess;
	glm::vec4 Color;
	GLuint VAO;
	GLuint ElementBuffer;
	unsigned int StartIndex;
	unsigned int EndIndex;

	void CalculateHash() override
	{
		Hash = TextureID;
	}
};

struct BlendMapModelJob : ModelJob
{
	GLuint BlendMapTextureRed;
	GLuint BlendMapTextureRedNormal;
	GLuint BlendMapTextureRedSpecular;
	GLuint BlendMapTextureGreen;
	GLuint BlendMapTextureGreenNormal;
	GLuint BlendMapTextureGreenSpecular;
	GLuint BlendMapTextureBlue;
	GLuint BlendMapTextureBlueNormal;
	GLuint BlendMapTextureBlueSpecular;
	float TextureRepeat;
};

struct SpriteJob : RenderJob
{
	unsigned int ShaderID;
	unsigned int TextureID;

	glm::mat4 ModelMatrix;
	GLuint Texture;
	glm::vec4 Color;

	void CalculateHash() override
	{
		Hash = TextureID;
	}
};

struct PointLightJob : RenderJob
{
	glm::vec3 Position;
	glm::vec3 SpecularColor = glm::vec3(1, 1, 1);
	glm::vec3 DiffuseColor = glm::vec3(1, 1, 1);
	float Radius = 1.f;

	void CalculateHash() override
	{
		Hash = 0;
	}
};

class RenderQueue
{
public:
	template <typename T>
	void Add(T &job)
	{
		job.CalculateHash();
		Jobs.push_front(std::shared_ptr<T>(new T(job)));
	}

	void Sort()
	{
		Jobs.sort();
	}

	void Clear()
	{
		Jobs.clear();
	}

	std::forward_list<std::shared_ptr<RenderJob>>::const_iterator begin()
	{
		return Jobs.begin();
	}

	std::forward_list<std::shared_ptr<RenderJob>>::const_iterator end()
	{
		return Jobs.end();
	}

	std::forward_list<std::shared_ptr<RenderJob>> Jobs;
};

struct RenderQueueCollection
{
	RenderQueue Deferred;
	RenderQueue Forward;
	RenderQueue Lights;

	void Clear()
	{
		Deferred.Clear();
		Forward.Clear();
		Lights.Clear();
	}

	void Sort()
	{
		Deferred.Sort();
		Forward.Sort();
		Lights.Sort();
	}
};

#endif // RenderQueue_h__