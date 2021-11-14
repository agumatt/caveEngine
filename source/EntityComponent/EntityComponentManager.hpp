#pragma once
#ifndef ENTITYCOMPONENTMANAGER_HPP
#define ENTITYCOMPONENTMANAGER_HPP
#include <entt/entt.h>
#include <string>
#include "../Rendering/RenderingManager.hpp"
#include "../Rendering/SkeletalMeshComponent.hpp"
#include "../Audio/AudioSourceComponent.hpp"

namespace cave {

	

	class EntityComponentManager {
		
	public:
		
		static entt::registry m_Registry;
		static std::map<std::string, entt::entity> m_entities = {};
		
		static void createEntity(std::string uniqueName);

		template<typename Component, typename... Args>
		static void addComponent(std::string entityName, Args ...args) {
			entt:entity entity = m_entities[entityName];
			m_Registry.emplace_or_replace<Component>(entity, ...args);

		}
		
		template<typename Component>
		static Component getComponent(std::string entityName) {
			entt::entity entity = m_entities[entityName];
			return m_Registry.get_or_emplace<Component>(entity);
		}
		
		template<typename Component>
		static auto getEntityView() {
			return m_Registry.view<Component>();
		}

		
		static void initEntities();

		static void updateEntities();

	};




}