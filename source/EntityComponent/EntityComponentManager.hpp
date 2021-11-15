#pragma once
#ifndef ENTITYCOMPONENTMANAGER_HPP
#define ENTITYCOMPONENTMANAGER_HPP
#include "../../thirdParty/entt/entt.hpp"
#include <string>
#include "../Rendering/RenderingManager.hpp"
#include "../Rendering/SkeletalMeshComponent.hpp"
#include "../Audio/AudioSourceComponent.hpp"

namespace cave {
	

	class EntityComponentManager {
		
	public:
		
		static entt::registry m_Registry;
		static std::map<std::string, entt::entity> m_entities;

		static void StartUp();
		
		static void createEntity(std::string uniqueName);

		template<typename Component, typename... Args>
		static void addComponent(std::string entityName, Args&& ...args) {
			m_Registry.emplace_or_replace<Component>(m_entities[entityName], std::forward<Args>(args)...);

		}
		
		template<typename Component>
		static Component& getComponent(std::string entityName) {
			return m_Registry.get<Component>(m_entities[entityName]);
		}
		
		template<typename Component>
		static auto getEntityView() {
			return m_Registry.view<Component>();
		}

		
		static void initEntities();

		static void updateEntities();

		template<typename Component>
		static void deleteComponent(std::string entityName) {
			entt::entity entity = m_entities[entityName];
			m_Registry.remove<Component>(entity);
		}

		static void deleteEntity(std::string entityName);

	};




}

#endif