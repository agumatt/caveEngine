#include "EntityComponentManager.hpp"

namespace cave {

	void EntityComponentManager::createEntity(std::string uniqueName) {
		entt::entity entity = m_Registry.create();
		m_entities[uniqueName] = entity;
	}

	void EntityComponentManager::initEntities() {
		// SkeletalMeshComponents
		auto skeletalMeshEntitiesView = getEntityView<SkeletalMeshComponent>();
		for (auto entity : skeletalMeshEntitiesView) {
			SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
			if (!skeletalMeshComponent.initialized) {
				RenderingManager::addModelsToScene({ skeletalMeshComponent.model });
				skeletalMeshComponent.initialized = true;
			}			
		}
	}

	void EntityComponentManager::updateEntities() {
		// SkeletalMeshComponents
		auto skeletalMeshEntitiesView = getEntityView<SkeletalMeshComponent>();
		for (auto entity : skeletalMeshEntitiesView) {
			SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
			RenderingManager::updateModelsInScene({ skeletalMeshComponent.model });
		}
	}

}