#include "SkeletalMeshComponent.hpp"

namespace cave {

	SkeletalMeshComponent::SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName, std::string parentNodeName) {
		Model = Model(meshFileName, nodeName, groupName, parentNodeName);
	}
	SkeletalMeshComponent::setInitialRotation(caveQuat initialRotation) {
		model.setInitialRotation(Ogre::Quaternion(initialRotation.fW, initialRotation.fX, initialRotation.fY, initialRotation.fZ));
	}
	SkeletalMeshComponent::setInitialTranslation(caveVec3f initialTranslation) {
		model.setInitialTranslation(Ogre::Vector3(initialTranslation.x, initialTranslation.y, initialTranslation.z));
	}
	SkeletalMeshComponent::setInitialScaling(caveVec3f initialScaling) {
		model.setInitialScaling(Ogre::Vector3(initialScaling.x, initialScaling.y, initialScaling.z));
	}
	SkeletalMeshComponent::setParentNodeName(std::string parentNodeName) {
		model.setParentNodeName(parentNodeName);
	}



}
