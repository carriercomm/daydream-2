#include <string>
#include <sstream>

#include "ResourceManager.h"
#include "OBJ.h"
#include "Model.h"
#include "Texture.h"
#include "EventBroker.h"
#include "RenderQueue.h"
#include "Renderer.h"
#include "InputManager.h"

class Engine
{
public:
	Engine(int argc, char* argv[])
	{
		m_EventBroker = std::make_shared<EventBroker>();
		
		m_Renderer = std::make_shared<Renderer>();
		m_Renderer->SetFullscreen(false);
		m_Renderer->SetResolution(Rectangle(0, 0, 1920, 1080));
		m_Renderer->Initialize();

		m_InputManager = std::make_shared<InputManager>(m_Renderer->GetWindow(), m_EventBroker);

		//m_World = std::make_shared<World>(m_EventBroker, m_ResourceManager);
		//m_World->Initialize();

		m_LastTime = glfwGetTime();
	}

	bool Running() const { return !glfwWindowShouldClose(m_Renderer->GetWindow()); }

	void Tick()
	{
		double currentTime = glfwGetTime();
		double dt = currentTime - m_LastTime;
		m_LastTime = currentTime;

		// Update input
		m_InputManager->Update(dt);

		//m_World->Update(dt);

		// Render scene
		m_Renderer->Swap();
		
		// Swap event queues
		m_EventBroker->Clear();

		glfwPollEvents();
	}

private:
	std::shared_ptr<ResourceManager> m_ResourceManager;
	std::shared_ptr<EventBroker> m_EventBroker;
	std::shared_ptr<Renderer> m_Renderer;
	std::shared_ptr<InputManager> m_InputManager;
	//std::shared_ptr<World> m_World;

	double m_LastTime;
};