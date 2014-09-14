#ifndef Model_h__
#define Model_h__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <stack>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <boost/filesystem/path.hpp>

#include "Core/ResourceManager.h"
#include "Core/Texture.h"
#include "Core/Skeleton.h"

class Model : public Resource
{
private:
	Model(std::string fileName);

public:
	~Model();
	static Model* Create(std::string resourceName) { return new Model(resourceName); }

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 BiTangent;
		glm::vec2 TextureCoords;
		glm::vec4 DiffuseVertexColor;
		glm::vec4 SpecularVertexColor;
		glm::vec4 BoneIndices1;
		glm::vec4 BoneIndices2;
		glm::vec4 BoneWeights1;
		glm::vec4 BoneWeights2;
	};

	struct MaterialGroup
	{
		float Shininess;
		std::shared_ptr<::Texture> Texture;
		std::shared_ptr<::Texture> NormalMap;
		std::shared_ptr<::Texture> SpecularMap;
		unsigned int StartIndex;
		unsigned int EndIndex;
	};

	GLuint VAO;
	GLuint ElementBuffer;
	std::vector<MaterialGroup> TextureGroups;

	std::vector<std::shared_ptr<Texture>> texture;
	glm::mat4 GetMatrix();
	std::vector<glm::vec3> Vertices;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	Skeleton* m_Skeleton = nullptr;

private:
	std::vector<glm::ivec2> BoneIndices;
	std::vector<glm::vec2> BoneWeights;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec4> DiffuseVertexColor;
	std::vector<glm::vec4> SpecularVertexColor;
	std::vector<glm::vec3> TangentNormals;
	std::vector<glm::vec3> BiTangentNormals;
	std::vector<glm::vec2> TextureCoords;

	GLuint VertexBuffer;
	GLuint DiffuseVertexColorBuffer;
	GLuint SpecularVertexColorBuffer;
	GLuint NormalBuffer;
	GLuint TangentNormalsBuffer;
	GLuint BiTangentNormalsBuffer;
	GLuint TextureCoordBuffer;

	void CreateSkeleton(std::vector<std::tuple<std::string, glm::mat4>> &boneInfo, std::map<std::string, int> &boneNameMapping, aiNode* node, int parentID);
};

#endif // Model_h__