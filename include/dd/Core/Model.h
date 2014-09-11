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

#include "ResourceManager.h"
#include "Texture.h"
#include "OBJ.h"

class Model : public Resource
{
public:
	Model(std::shared_ptr<ResourceManager> resourceManager, OBJ &obj, bool average);

	struct TextureGroup
	{
		std::shared_ptr<::Texture> Texture;
		std::shared_ptr<::Texture> NormalMap;
		std::shared_ptr<::Texture> SpecularMap;
		unsigned int StartIndex;
		unsigned int EndIndex;
	};

	GLuint VAO;
	std::vector<TextureGroup> TextureGroups;

	std::vector<std::shared_ptr<Texture>> texture;
	glm::mat4 GetMatrix();
	std::vector<glm::vec3> Vertices;

private:

	std::vector<glm::vec3> Normals;
	std::vector<glm::vec3> TangentNormals;
	std::vector<glm::vec3> BiTangentNormals;
	std::vector<glm::vec2> TextureCoords;

	GLuint VertexBuffer;
	GLuint NormalBuffer;
	GLuint TangentNormalsBuffer;
	GLuint BiTangentNormalsBuffer;
	GLuint TextureCoordBuffer;

	bool Loadobj(
	    const char* path,
	    std::vector <glm::vec3> &out_vertices,
	    std::vector <glm::vec3> &out_normals,
	    std::vector <glm::vec2> &out_TextureCoords
	);

	void CreateBuffers(
	    std::vector<glm::vec3> _Vertices,
		std::vector<glm::vec3> _Normals,
		std::vector<glm::vec3> _Tangents,
		std::vector<glm::vec3> _BiTangents,
	    std::vector<glm::vec2>_TextureCoords
	);

	void CreateTangents();
	bool IsNear(float v1, float v2);
	void getSimilarVertexIndex();

};
#endif // Model_h__