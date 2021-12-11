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
		RenderingManager::StartUp();
		EntityComponentManager::StartUp();
		AudioManager::StartUp();
		ScriptManager::StartUp();
		m_application.UserStartUp(*this);
		
	}
	
	World::~World() {

	}
	
	float minimumFrameTime = 15.0f / 1000.0f;
	float maximumFrameTime = 0.3f;
	float renderingAccTime = 0;
	float renderingRefreshInterval = 1.0f / 60.0f;
	float audioAccTime = 0;
	float eventsAccTime = 0;
	void World::StartMainLoop() noexcept {
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
		std::cout << "MainLoop iniciado.";
		while (m_running)
		{
			std::chrono::time_point<std::chrono::steady_clock> newTime = std::chrono::steady_clock::now();
			const auto frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			if(timeStep < minimumFrameTime){
				Sleep((minimumFrameTime - timeStep) * 1000);
			
			} else if (timeStep >= maximumFrameTime) {
				timeStep = maximumFrameTime;
			}
			Update(timeStep);
		}		
	}

	void World::Update(float timeStep) noexcept
	{
		renderingAccTime += timeStep;
		audioAccTime += timeStep;
		eventsAccTime += timeStep;
		if (renderingAccTime >= renderingRefreshInterval) {
			RenderingManager::render();
			renderingAccTime = 0;
		}
		
		AudioManager::updateListenerData();		
		EventManager::processEvents(timeStep);
		
	}


}