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

#include "PrecompiledHeader.h"
#include "Core/ShaderProgram.h"

GLuint Shader::CompileShader(GLenum shaderType, std::string fileName)
{
	LOG_INFO("Compiling shader \"%s\"", fileName.c_str());

	std::string shaderFile;
	std::ifstream in(fileName, std::ios::in);
	if (!in)
	{
		LOG_ERROR("Error: Failed to open shader file \"%s\"", fileName.c_str());
		return 0;
	}
	in.seekg(0, std::ios::end);
	shaderFile.resize((int)in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&shaderFile[0], shaderFile.size());
	in.close();

	GLuint shader = glCreateShader(shaderType);
	if(GLERROR("glCreateShader"))
		return 0;

	const GLchar* shaderFiles = shaderFile.c_str();
	const GLint length = shaderFile.length();
	glShaderSource(shader, 1, &shaderFiles, &length);
	if(GLERROR("glShaderSource"))
		return 0;

	glCompileShader(shader);

	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		LOG_ERROR("Shader compilation failed");
		GLsizei infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infolog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infolog);
		LOG_ERROR(infolog);
		delete[] infolog;
	}

	if(GLERROR("glCompileShader"))
		return 0;

	return shader;
}

Shader::Shader(GLenum shaderType, std::string fileName) : m_ShaderType(shaderType), m_FileName(fileName)
{
	m_ShaderHandle = 0;
}

Shader::~Shader()
{
	if (m_ShaderHandle != 0)
	{
		glDeleteShader(m_ShaderHandle);
	}
}

GLuint Shader::Compile()
{
	m_ShaderHandle = CompileShader(m_ShaderType, m_FileName);
	return m_ShaderHandle;
}

GLenum Shader::GetType() const
{
	return m_ShaderType;
}

std::string Shader::GetFileName() const
{
	return m_FileName;
}

GLuint Shader::GetHandle() const
{
	return m_ShaderHandle;
}

bool Shader::IsCompiled() const
{
	return m_ShaderHandle != 0;
}

ShaderProgram::~ShaderProgram()
{
	if (m_ShaderProgramHandle != 0)
	{
		glDeleteProgram(m_ShaderProgramHandle);
	}
}

void ShaderProgram::AddShader(std::shared_ptr<Shader> shader)
{
	m_Shaders.push_back(shader);
}

void ShaderProgram::Compile()
{
	if (m_ShaderProgramHandle == 0)
	{
		m_ShaderProgramHandle = glCreateProgram();
	}

	for (auto &shader : m_Shaders)
	{
		if (!shader->IsCompiled())
		{
			shader->Compile();
		}
	}
}

GLuint ShaderProgram::Link()
{
	if (m_Shaders.size() == 0)
	{
		LOG_ERROR("Failed to link shader program: No shaders bound");
		return 0;
	}

	LOG_INFO("Linking shader program");

	for (auto &shader : m_Shaders)
	{
		glAttachShader(m_ShaderProgramHandle, shader->GetHandle());
	}
	glLinkProgram(m_ShaderProgramHandle);
	if (GLERROR("glLinkProgram"))
		return 0;
	m_Shaders.clear();

	return m_ShaderProgramHandle;
}

GLuint ShaderProgram::GetHandle()
{
	return m_ShaderProgramHandle;
}

void ShaderProgram::Bind()
{
	if (m_ShaderProgramHandle == 0)
		return;

	glUseProgram(m_ShaderProgramHandle);
}

void ShaderProgram::Unbind()
{
	glActiveShaderProgram(0, 0);
}

void ShaderProgram::LoadFromFolder(std::string folderPath)
{
	auto path = boost::filesystem::path(folderPath);

	if (!boost::filesystem::is_directory(path))
	{
		LOG_ERROR("Failed to load shader program: \"%s\" is not a directory", folderPath.c_str());
		return;
	}

	for (auto it = boost::filesystem::directory_iterator(path); it != boost::filesystem::directory_iterator(); it++)
	{
		std::string filename = it->path().filename().string();
		if (filename == "Vertex.glsl")
		{
			AddShader(std::shared_ptr<Shader>(new VertexShader(filename)));
		}
		else if (filename == "Fragment.glsl")
		{
			AddShader(std::shared_ptr<Shader>(new FragmentShader(filename)));

		}
		else if (filename == "Geometry.glsl")
		{
			AddShader(std::shared_ptr<Shader>(new GeometryShader(filename)));
		}
	}
}

void ShaderProgram::BindFragDataLocation(int colorNumber, std::string name)
{
	if (m_ShaderProgramHandle == 0)
		return;

	glBindFragDataLocation(m_ShaderProgramHandle, colorNumber, name.c_str());
}
