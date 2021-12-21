#include "World.hpp"
namespace cave {
	
	World::World(Application& app):
		m_application(app),
		m_running(true),
		m_renderingManager()
	{
		RenderingManager::StartUp();
		EntityComponentManager::StartUp();
		AudioManager::StartUp();
		ScriptManager::StartUp();
		m_application.UserStartUp(*this);
		
	}
	
	void World::EndApplication() noexcept {
		m_running = false;
	}

	World::~World() {
		m_application.UserShutDown(*this);
		RenderingManager::m_context->closeApp();
	}
	
	float minimumFrameTime = 15.0f / 1000.0f;
	float averageFrameTime = 150.0f / 1000.0f;
	float renderingAccTime = 0;
	float renderingRefreshInterval = 1.0f / 60.0f;
	float audioAccTime = 0;
	float eventsAccTime = 0;
	void World::StartMainLoop() noexcept {
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
		while (m_running)
		{
			
			std::chrono::time_point<std::chrono::steady_clock> newTime = std::chrono::steady_clock::now();
			const auto frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			averageFrameTime = averageFrameTime * 0.9 + timeStep * 0.1;
			if(timeStep < minimumFrameTime){
				Sleep((minimumFrameTime - timeStep) * 1000);
			
			} else if (timeStep >= averageFrameTime*4) {
				timeStep = averageFrameTime * 4;
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
		EntityComponentManager::updateEntities(timeStep);
		
	}


}