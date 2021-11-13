#include "EntityComponentManager.hpp"

namespace cave {

	EntityComponentManager::createEntity(std::string uniqueName) {
		entt::entity entity = m_Registry.create();
		m_entities[uniqueName] = entity;
	}

}