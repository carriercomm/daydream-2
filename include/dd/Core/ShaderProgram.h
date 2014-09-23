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

#ifndef ShaderProgram_h__
#define ShaderProgram_h__

#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "ResourceManager.h"

namespace dd
{

class Shader
{
public:
	static GLuint CompileShader(GLenum shaderType, std::string fileName);

	Shader(GLenum shaderType, std::string fileName);

	virtual ~Shader();

	GLuint Compile();

	GLenum GetType() const;
	std::string GetFileName() const;
	GLuint GetHandle() const;
	bool IsCompiled() const;

protected:
	GLenum m_ShaderType;
	std::string m_FileName;
	GLint m_ShaderHandle;
};

template <int SHADERTYPE>
class ShaderType : public Shader
{
public:
	ShaderType(std::string fileName)
		: Shader(SHADERTYPE, fileName) { }
};

class VertexShader : public ShaderType<GL_VERTEX_SHADER>
{
public:
	VertexShader(std::string fileName)
		: ShaderType(fileName) { }
};

class FragmentShader : public ShaderType<GL_FRAGMENT_SHADER>
{
public:
	FragmentShader(std::string fileName)
		: ShaderType(fileName) { }
};

class GeometryShader : public ShaderType<GL_GEOMETRY_SHADER>
{
public:
	GeometryShader(std::string fileName)
		: ShaderType(fileName) { }
};

class ShaderProgram : public Resource
{
public:
	ShaderProgram()
		: m_ShaderProgramHandle(0) 
	{ }
	ShaderProgram(std::string folderPath)
		: m_ShaderProgramHandle(0)
	{ }

	~ShaderProgram();

	void AddShader(std::shared_ptr<Shader> shader);
	void BindFragDataLocation(int colorNumber, std::string name);
	void Compile();
	GLuint Link();
	GLuint GetHandle();
	operator GLuint() const { return m_ShaderProgramHandle; }
	void Bind();
	void Unbind();

private:
	GLuint m_ShaderProgramHandle;
	std::vector<std::shared_ptr<Shader>> m_Shaders;

	void LoadFromFolder(std::string folderPath);
};

}

#endif // ShaderProgram_h__