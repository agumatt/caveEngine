#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP
#include "../Application.hpp"

#include <memory>
#include <array>
#include <filesystem>
#include <string>

namespace Mona {

	class Material;
	class World {
	public:
		friend class Engine;
		friend class MonaTest;
		
		World(const World& world) = delete;
		World& operator=(const World& world) = delete;
		

	private:
		World(Application& app);
		~World();
		void StartMainLoop() noexcept;
		void Update(float timeStep) noexcept;

		Application& m_application;
				
	};

	

}
#endif