#pragma once
#ifndef ENTITYCOMPONENTMANAGER_HPP
#define ENTITYCOMPONENTMANAGER_HPP
#include <entt/entt.h>
#include <string>

namespace cave {

	

	class EntityComponentManager {
		
	public:
		
		static entt::registry m_Registry;
		static std::map<std::string, entt::entity> m_entities = {};
		
		void createEntity(std::string uniqueName);

		template<typename Component, typename... Args>
		void addComponent(std::string entityName, Args ...args) {
			entt:entity entity = m_entities[entityName];
			m_Registry.emplace_or_replace<Component>(entity, ...args);
		}





	};




}