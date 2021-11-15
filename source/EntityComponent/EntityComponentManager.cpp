#include "EntityComponentManager.hpp"

namespace cave {

	entt::registry EntityComponentManager::m_Registry;
	std::map<std::string, entt::entity> EntityComponentManager::m_entities;

	void EntityComponentManager::StartUp() {
		m_entities = {};
	}

	void EntityComponentManager::createEntity(std::string uniqueName) {
		entt::entity entity = m_Registry.create();
		m_entities[uniqueName] = entity;
	}

	void EntityComponentManager::initEntities() {
		// SkeletalMeshComponents
		auto skeletalMeshEntitiesView = getEntityView<SkeletalMeshComponent>();
		for (auto entity : skeletalMeshEntitiesView) {
			SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
			if (!skeletalMeshComponent.m_initialized) {
				std::vector<Model> models = { skeletalMeshComponent.m_model };
				RenderingManager::addModelsToScene(models);
				skeletalMeshComponent.m_initialized = true;
			}			
		}
	}

	void EntityComponentManager::updateEntities() {
		// SkeletalMeshComponents
		auto skeletalMeshEntitiesView = getEntityView<SkeletalMeshComponent>();
		for (auto entity : skeletalMeshEntitiesView) {
			SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
			std::vector<Model> models = { skeletalMeshComponent.m_model };
			RenderingManager::updateModelsInScene(models);
		}
	}

}