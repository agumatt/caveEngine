#include "RenderingManager.hpp"
#include "../Utils/Utils.hpp"


namespace cave {
	
	struct SkeletalMeshComponent {

		Model model;
		bool initialized;

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");

		void setRotation(caveQuat rotation);
		void setTranslation(caveVec3f translation);
		void setScaling(caveVec3f scaling);
		void setParentNodeName(std::string parentNodeName);


	};




}