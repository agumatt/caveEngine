#include "RenderingManager.hpp"
#include "../Utils/Utils.hpp"


namespace cave {
	
	struct SkeletalMeshComponent {

		Model model;

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");

		void setInitialRotation(caveQuat initialRotation);
		void setInitialTranslation(caveVec3f initialTranslation);
		void setInitialScaling(caveVec3f initialScaling);
		void setParentNodeName(std::string parentNodeName);


	};




}