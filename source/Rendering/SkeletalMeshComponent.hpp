#pragma once
#ifndef SKELETALMESHCOMPONENT_HPP
#define SKELETALMESHCOMPONENT_HPP
#include "RenderingManager.hpp"


namespace cave {
	
	struct SkeletalMeshComponent {

		Model m_model;
		bool m_initialized;

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");

		void setRotation(caveQuat rotation);
		void setTranslation(caveVec3f translation);
		void setScaling(caveVec3f scaling);
		void setParentNodeName(std::string parentNodeName);


	};




}

#endif