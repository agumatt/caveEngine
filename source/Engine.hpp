#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>
#include "World/World.hpp"
#include "Application.hpp"
namespace cave {
	class Engine
	{
	public:
		Engine(Application& app) : m_world(app) {}
		~Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		/*
		* Funcion que comienza el main loop del motor.
		*/
		void StartMainLoop() noexcept {
			std::cout << "Engine StartMainLoop";
			m_world.StartMainLoop();
		}
	private:
		World m_world;
	};
}

#endif