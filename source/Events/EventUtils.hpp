#pragma once
#ifndef EVENTUTILS_HPP
#define EVENTUTILS_HPP
#include "../EntityComponent/EntityComponentManager.hpp"
#include "../Utils/LibUtils.hpp"

namespace cave {



	struct EventUtils {


		static std::vector<std::string> entitiesInSight() {
			std::vector<std::string> entitiesInSight = {};
			auto skeletalMeshEntitiesView = EntityComponentManager::getEntityView<SkeletalMeshComponent>();
			for (auto entity : skeletalMeshEntitiesView) {
				SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
				Model model = skeletalMeshComponent.m_model;
				Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(model.m_nodeName);
				Ogre::Entity* ogreEntity = (Ogre::Entity*)node->getAttachedObject(0);
				Ogre::Sphere boundingSphere = ogreEntity->getWorldBoundingSphere();
				bool isInSight = RenderingManager::m_camera->isVisible(boundingSphere);
				if (isInSight) {
					entitiesInSight.push_back(EntityComponentManager::getEntityName(entity));
				}
			}
			return entitiesInSight;
		}

		static std::string entityReachedPlayer() {
			auto skeletalMeshEntitiesView = EntityComponentManager::getEntityView<SkeletalMeshComponent>();
			for (auto entity : skeletalMeshEntitiesView) {
				SkeletalMeshComponent& skeletalMeshComponent = skeletalMeshEntitiesView.get<SkeletalMeshComponent>(entity);
				Model model = skeletalMeshComponent.m_model;
				Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(model.m_nodeName);
				Ogre::Entity* ogreEntity = (Ogre::Entity*)node->getAttachedObject(0);
				Ogre::Sphere boundingSphere = ogreEntity->getWorldBoundingSphere();
				caveVec3f playerPos = RenderingManager::getPlayerPosition();
				if (boundingSphere.intersects(Ogre::Vector3f(playerPos.x, playerPos.y, playerPos.z))) {
					return EntityComponentManager::getEntityName(entity);
				}
			}
			return "";
		}

		static void updateChasePlayer(std::string entityName) {
			entt::entity entity = EntityComponentManager::m_entities[entityName];
			if (EntityComponentManager::m_Registry.all_of<SkeletalMeshComponent>(entity)) {
				SkeletalMeshComponent& skeletalMeshComponent = EntityComponentManager::m_Registry.get<SkeletalMeshComponent>(entity);
				caveVec3f playerPos = RenderingManager::getPlayerPosition();
				caveVec3f entityPos = skeletalMeshComponent.getMeshPosition();
				Ogre::Vector3f ogreNewDir = Ogre::Vector3f(playerPos.x - entityPos.x, playerPos.y - entityPos.y, playerPos.z - entityPos.z);
				ogreNewDir.normalise();
				caveVec3f newDir = caveVec3f(ogreNewDir.x, ogreNewDir.y, ogreNewDir.z);
				skeletalMeshComponent.m_moving = true;
				skeletalMeshComponent.m_movementDirection = newDir;
			}
			
		}

		static void stopChasePlayer(std::string entityName) {
			entt::entity entity = EntityComponentManager::m_entities[entityName];
			if (EntityComponentManager::m_Registry.all_of<SkeletalMeshComponent>(entity)) {
				SkeletalMeshComponent& skeletalMeshComponent = EntityComponentManager::m_Registry.get<SkeletalMeshComponent>(entity);
				skeletalMeshComponent.m_moving = true;
			}


		}

		static std::vector<std::string> getEntityNames() {
			std::vector<std::string> names = {};
			auto entities = EntityComponentManager::m_entities;
			for (auto& [key, value] : entities) {
				names.push_back(key);
			}
			return names;
		}





	};

}

#endif