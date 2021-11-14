#include "SkeletalMeshComponent.hpp"

namespace cave {

	SkeletalMeshComponent::SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName, std::string parentNodeName) {
		Model = Model(meshFileName, nodeName, groupName, parentNodeName);
		initialized = false;
	}
	SkeletalMeshComponent::setRotation(caveQuat rotation) {
		model.setRotation(Ogre::Quaternion(rotation.fW, rotation.fX, rotation.fY, rotation.fZ));
	}
	SkeletalMeshComponent::setTranslation(caveVec3f translation) {
		model.setTranslation(Ogre::Vector3(translation.x, translation.y, translation.z));
	}
	SkeletalMeshComponent::setScaling(caveVec3f scaling) {
		model.setScaling(Ogre::Vector3(scaling.x, scaling.y, scaling.z));
	}
	SkeletalMeshComponent::setParentNodeName(std::string parentNodeName) {
		model.setParentNodeName(parentNodeName);
	}



}
