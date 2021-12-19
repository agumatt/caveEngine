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

	void EntityComponentManager::updateEntities(float timeStep) {
		// SkeletalMeshComponents
		auto skeletalMeshEntitiesView = getEntityView<SkeletalMeshComponent>();
		for (auto entity : skeletalMeshEntitiesView) {
			SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
			std::vector<Model> models = { skeletalMeshComponent.m_model };
			// update mesh position
			if (skeletalMeshComponent.m_moving) {
				caveVec3f dir = skeletalMeshComponent.m_movementDirection;
				float speed = skeletalMeshComponent.m_speed;
				caveVec3f velocity = caveVec3f(speed * dir.x, speed * dir.y, speed * dir.z);
				skeletalMeshComponent.moveMesh(velocity, timeStep);
			}
			RenderingManager::updateModelsInScene(models);
			// update animations
			Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(models[0].m_nodeName);
			Ogre::Entity* ogreEntity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
			if (skeletalMeshComponent.m_animations.size() > 0) {
			}
			for (std::string name : skeletalMeshComponent.m_animations) {
				Ogre::AnimationState* anim = ogreEntity->getAnimationState(name);
				if (anim->getEnabled()) {
					anim->addTime(timeStep);
				}				
			}
			// update audio source position
			bool hasAudio = m_Registry.all_of<AudioSourceComponent>(entity);
			if (hasAudio) {
				AudioSourceComponent& audioSourceComponent = m_Registry.get<AudioSourceComponent>(entity);
				Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(skeletalMeshComponent.m_model.m_nodeName);
				Ogre::Vector3f ogrePos = node->_getDerivedPosition();
				audioSourceComponent.setPosition(caveVec3f(ogrePos.x, ogrePos.y, ogrePos.z));
			}		
			
		}
	}

	void EntityComponentManager::deleteEntity(std::string entityName) {
		entt::entity entity = m_entities[entityName];
		m_Registry.destroy(entity);
		m_entities.erase(entityName);
	}

	std::string EntityComponentManager::getEntityName(entt::entity entity) {
		for (auto const& [key, val] : m_entities)
		{
			if (m_entities[key] == entity) {
				return key;
			}
		}
		std::cerr << "No existe un nombre asociado a la entidad"<<std::endl;
	}

}