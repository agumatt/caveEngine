#include "World.hpp"
#include "../Core/RootDirectory.hpp"
#include <chrono>
namespace cave {
	
	World::World(Application& app):
		m_application(app),
		m_running(true),
		m_renderingManager()
	{
		std::cout << "World creado.";
		m_renderingManager.StartUp(OgreBites::CameraStyle::CS_FREELOOK);
		m_application.UserStartUp(*this);
		
	}
	
	World::~World() {

	}

	RenderingManager World::getRenderingManager() {
		return m_renderingManager;
	}
	

	void World::StartMainLoop() noexcept {
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
		std::cout << "MainLoop iniciado.";
		while (m_running)
		{
			std::chrono::time_point<std::chrono::steady_clock> newTime = std::chrono::steady_clock::now();
			const auto frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			Update(timeStep);
		}
		//m_eventManager.Publish(ApplicationEndEvent());
		
	}

	void World::Update(float timeStep) noexcept
	{
		//para lo que envía el usuario y lo que debe hacer el motor en cada ciclo
		m_renderingManager.render();
	}


}

