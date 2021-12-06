#pragma once
#ifndef EVENTUTILS_HPP
#define EVENTUTILS_HPP
#include "../EntityComponent/EntityComponentManager.hpp"

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




	};

}

#endif