#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP
#include "../Application.hpp"
#include "../Rendering/RenderingManager.hpp"

#include <memory>
#include <array>
#include <filesystem>
#include <string>

namespace cave {

	class Material;
	class World {
	public:
		friend class Engine;
		friend class caveTest;
		
		World(const World& world) = delete;
		World& operator=(const World& world) = delete;

		World(Application& app);
		~World();
		void StartMainLoop() noexcept;
		void Update(float timeStep) noexcept;

		Application& m_application;
		bool m_running;
		RenderingManager m_renderingManager;

		RenderingManager getRenderingManager();
				
	};

	

}
#endif