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

#ifndef RenderQueue_h__
#define RenderQueue_h__

#include <cstdint>
#include <forward_list>

#include "Texture.h"
#include "Model.h"

namespace dd
{

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

}

#endif // RenderQueue_h__