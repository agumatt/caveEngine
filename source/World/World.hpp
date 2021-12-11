#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP
#include "../Application.hpp"
#include "../Rendering/RenderingManager.hpp"
#include "../EntityComponent/EntityComponentManager.hpp"
#include "../Audio/AudioManager.hpp"
#include "../Scripting/ScriptManager.hpp"
#include "../Events/EventUtils.hpp"
#include "../Events/EventManager.hpp"
#include "../Core/RootDirectory.hpp"

namespace cave {

	class World {
	public:
		friend class Engine;
		
		World(const World& world) = delete;
		World& operator=(const World& world) = delete;

		World(Application& app);
		~World();
		void StartMainLoop() noexcept;
		void Update(float timeStep) noexcept;

		Application& m_application;
		bool m_running;
		RenderingManager m_renderingManager;
				
	};

	

}
#endif