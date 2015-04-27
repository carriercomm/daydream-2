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
#include "Core/Renderer.h"

void dd::Renderer::Initialize()
{
	// Initialize GLFW
	if (!glfwInit()) {
		LOG_ERROR("GLFW: Initialization failed");
		exit(EXIT_FAILURE);
	}

	// Create a window
	GLFWmonitor* monitor = nullptr;
	if (m_Fullscreen) {
		monitor = glfwGetPrimaryMonitor();
	}
	glfwWindowHint(GLFW_SAMPLES, 8);
	m_Window = glfwCreateWindow(m_Resolution.Width, m_Resolution.Height, "daydream", monitor, nullptr);
	if (!m_Window) {
		LOG_ERROR("GLFW: Failed to create window");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_Window);

	// GL version info
	glGetIntegerv(GL_MAJOR_VERSION, &m_GLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &m_GLVersion[1]);
	m_GLVendor = (GLchar*)glGetString(GL_VENDOR);
	std::stringstream ss;
	ss << m_GLVendor << " OpenGL " << m_GLVersion[0] << "." << m_GLVersion[1];
#ifdef DEBUG
	ss << " DEBUG";
#endif
	LOG_INFO(ss.str().c_str());
	glfwSetWindowTitle(m_Window, ss.str().c_str());

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		LOG_ERROR("GLEW: Initialization failed");
		exit(EXIT_FAILURE);
	}

	// Create default camera
	m_DefaultCamera = std::unique_ptr<dd::Camera>(new dd::Camera((float)m_Resolution.Width / m_Resolution.Height, 45.f, 0.01f, 5000.f));
	m_DefaultCamera->SetPosition(glm::vec3(0, 0, 0));
	if (m_Camera == nullptr) {
		m_Camera = m_DefaultCamera.get();
	}

	glfwSwapInterval(m_VSYNC);

	LoadShaders();
	CreateBuffers();

	m_CurrentScreenBuffer = m_tFinal;
}
void dd::Renderer::LoadShaders()
{
	/*
		Deferred rendering
	*/

	// Pass #1: Fill G-buffers
	m_spDeferred1 = ResourceManager::Load<ShaderProgram>("Shaders/Deferred/1/");
	m_spDeferred1->BindFragDataLocation(0, "GDiffuse");
	m_spDeferred1->BindFragDataLocation(1, "GPosition");
	m_spDeferred1->BindFragDataLocation(2, "GNormal");
	m_spDeferred1->BindFragDataLocation(3, "GSpecular");
	m_spDeferred1->Link();

	// Pass #2: Lighting
	m_spDeferred2 = ResourceManager::Load<ShaderProgram>("Shaders/Deferred/2/");
	//glBindFragDataLocation(m_SPDeferred2, 0, "FragmentLighting");
	m_spDeferred2->Link();

	// Pass #3: Combining into final image
	m_spDeferred3 = ResourceManager::Load<ShaderProgram>("Shaders/Deferred/3/");
	m_spDeferred3->Link();

	/*
		Forward rendering
	*/

	m_spForward = ResourceManager::Load<ShaderProgram>("Shaders/Forward/");
	m_spForward->Link();

	/*
		Screen draw
	*/

	m_spScreen = ResourceManager::Load<ShaderProgram>("Shaders/Screen/");
	m_spScreen->Link();
}

void dd::Renderer::CreateBuffers()
{
	m_UnitQuad = CreateQuad();
	m_UnitSphere = ResourceManager::Load<Model>("Models/Core/UnitSphere.obj");

	glGenRenderbuffers(1, &m_rbDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Resolution.Width, m_Resolution.Height);

	// Generate G-buffer textures
	glGenTextures(1, &m_GDiffuse);
	glBindTexture(GL_TEXTURE_2D, m_GDiffuse);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Resolution.Width, m_Resolution.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenTextures(1, &m_GPosition);
	glBindTexture(GL_TEXTURE_2D, m_GPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, m_Resolution.Width, m_Resolution.Height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenTextures(1, &m_GNormal);
	glBindTexture(GL_TEXTURE_2D, m_GNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, m_Resolution.Width, m_Resolution.Height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenTextures(1, &m_GSpecular);
	glBindTexture(GL_TEXTURE_2D, m_GSpecular);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Resolution.Width, m_Resolution.Height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Create first pass framebuffer
	glGenFramebuffers(1, &m_fbDeferred1);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbDeferred1);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbDepthBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_GDiffuse, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_GPosition, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_GNormal, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_GSpecular, 0);
	GLenum firstPassDrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, firstPassDrawBuffers);
	if (GLenum fbStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG_ERROR("m_fbDeferred1 incomplete: 0x%x\n", fbStatus);
		exit(EXIT_FAILURE);
	}

	// Generate lighting texture
	glGenTextures(1, &m_tLighting);
	glBindTexture(GL_TEXTURE_2D, m_tLighting);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Resolution.Width, m_Resolution.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Create second pass framebuffer
	glGenFramebuffers(1, &m_fbDeferred2);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbDeferred2);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tLighting, 0);
	GLenum secondPassDrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, secondPassDrawBuffers);
	if (GLenum fbStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG_ERROR("m_fbDeferred2 incomplete: 0x%x\n", fbStatus);
		exit(EXIT_FAILURE);
	}

	// Generate final deferred texture
	glGenTextures(1, &m_tFinal);
	glBindTexture(GL_TEXTURE_2D, m_tFinal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Resolution.Width, m_Resolution.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Create third pass framebuffer
	glGenFramebuffers(1, &m_fbDeferred3);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbDeferred3);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbDepthBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tFinal, 0);
	GLenum thirdPassDrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, thirdPassDrawBuffers);
	if (GLenum fbStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG_ERROR("m_fbDeferred3 incomplete: 0x%x\n", fbStatus);
		exit(EXIT_FAILURE);
	}
}

void dd::Renderer::Draw(RenderQueueCollection& rq)
{
	DrawDeferred(rq.Deferred, rq.Lights);
	DrawForward(rq.Forward, rq.Lights);

	// Finally: Draw the deferred+forward combined texture to the screen
	glCullFace(GL_BACK);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	m_spScreen->Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_CurrentScreenBuffer);
	glBindVertexArray(m_UnitQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(m_Window);

	DebugKeys();
}

void dd::Renderer::DrawDeferred(RenderQueue &objects, RenderQueue &lights)
{
	// Pass #1: Fill G-buffers
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbDeferred1);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_spDeferred1->Bind();
	DrawScene(objects, *m_spDeferred1);

	// Pass #2: Lighting
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbDeferred2);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	m_spDeferred2->Bind();
	DrawLightSpheres(lights);

	// Pass #3: Combine into final deferred image
	glCullFace(GL_BACK);
	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbDeferred3);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	m_spDeferred3->Bind();
	glUniform3fv(glGetUniformLocation(*m_spDeferred3, "La"), 1, glm::value_ptr(glm::vec3(0.3f)));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_GDiffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_tLighting);
	glBindVertexArray(m_UnitQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void dd::Renderer::DrawForward(RenderQueue &objects, RenderQueue &lights)
{
	// Forward-render semi-transparent objects on top of the current framebuffer
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	m_spForward->Bind();
	DrawScene(objects, *m_spForward);
}

void dd::Renderer::DrawScene(RenderQueue &objects, ShaderProgram &program)
{
	GLuint shaderProgramHandle = program;

	glm::mat4 viewMatrix = m_Camera->ViewMatrix();
	glm::mat4 PV = m_Camera->ProjectionMatrix() * viewMatrix;
	glm::mat4 MVP;

	for (auto &job : objects) {
		auto modelJob = std::dynamic_pointer_cast<ModelJob>(job);
		if (modelJob) {
			glm::mat4 modelMatrix = modelJob->ModelMatrix;
			MVP = PV * modelMatrix;
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "M"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "V"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

			glUniform1f(glGetUniformLocation(shaderProgramHandle, "MaterialShininess"), modelJob->Shininess);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, modelJob->DiffuseTexture);
			if (modelJob->NormalTexture != 0) {
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, modelJob->NormalTexture);
			}
			if (modelJob->SpecularTexture != 0) {
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, modelJob->SpecularTexture);
			}

			glBindVertexArray(modelJob->VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelJob->ElementBuffer);
			glDrawElementsBaseVertex(GL_TRIANGLES, modelJob->EndIndex - modelJob->StartIndex + 1, GL_UNSIGNED_INT, 0, modelJob->StartIndex);
		}
	}
}

void dd::Renderer::DrawLightSpheres(RenderQueue &lights)
{
	GLuint shaderProgramHandle = *m_spDeferred2;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_GPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_GNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_GSpecular);

	glm::mat4 projectionMatrix = m_Camera->ProjectionMatrix();
	glm::mat4 viewMatrix = m_Camera->ViewMatrix();
	glm::mat4 PV = projectionMatrix * viewMatrix;
	glm::mat4 MVP;

	for (auto &job : lights) {
		auto pointLightJob = std::dynamic_pointer_cast<PointLightJob>(job);
		if (pointLightJob) {
			glm::mat4 modelMatrix = glm::translate(pointLightJob->Position) * glm::scale(glm::vec3(pointLightJob->Radius * 2.f));
			MVP = PV * modelMatrix;
			glUniform2fv(glGetUniformLocation(shaderProgramHandle, "ViewportSize"), 1, glm::value_ptr(glm::vec2(m_Resolution.Width, m_Resolution.Height)));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "M"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "V"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgramHandle, "P"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			glUniform3fv(glGetUniformLocation(shaderProgramHandle, "LightPosition"), 1, glm::value_ptr(pointLightJob->Position));
			glUniform1f(glGetUniformLocation(shaderProgramHandle, "LightRadius"), pointLightJob->Radius);
			glUniform3fv(glGetUniformLocation(shaderProgramHandle, "LightDiffuse"), 1, glm::value_ptr(pointLightJob->DiffuseColor));
			glUniform3fv(glGetUniformLocation(shaderProgramHandle, "LightSpecular"), 1, glm::value_ptr(pointLightJob->SpecularColor));

			glBindVertexArray(m_UnitSphere->VAO);
			glDrawArrays(GL_TRIANGLES, 0, m_UnitSphere->m_Vertices.size());
		}
	}
}

GLuint dd::Renderer::CreateQuad()
{
	float quadVertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,

		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	float quadTexCoords[] =
	{
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};
	GLuint vbo[2], vao;
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), quadVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(float), quadTexCoords, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

void dd::Renderer::DebugKeys()
{
	if (glfwGetKey(m_Window, GLFW_KEY_F1)) {
		m_CurrentScreenBuffer = m_tFinal;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_F2)) {
		m_CurrentScreenBuffer = m_GDiffuse;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_F3)) {
		m_CurrentScreenBuffer = m_GPosition;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_F4)) {
		m_CurrentScreenBuffer = m_GNormal;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_F5)) {
		m_CurrentScreenBuffer = m_GSpecular;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_F6)) {
		m_CurrentScreenBuffer = m_tLighting;
	}
}
