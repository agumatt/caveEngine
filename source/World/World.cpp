#include "World.hpp"
#include "../Core/Config.hpp"
#include "../Core/RootDirectory.hpp"
#include <chrono>
namespace cave {
	
	World::World(Application& app)
	{
	
	}
	
	World::~World() {

	}

	

	void World::StartMainLoop() noexcept {
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
		
		while (!m_window.ShouldClose() && !m_shouldClose)
		{
			std::chrono::time_point<std::chrono::steady_clock> newTime = std::chrono::steady_clock::now();
			const auto frameTime = newTime - startTime;
			startTime = newTime;
			float timeStep = std::chrono::duration_cast<std::chrono::duration<float>>(frameTime).count();
			Update(timeStep);
		}
		m_eventManager.Publish(ApplicationEndEvent());
		
	}

	void World::Update(float timeStep) noexcept
	{
		
	}


}

