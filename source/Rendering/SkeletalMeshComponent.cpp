#include "SkeletalMeshComponent.hpp"

namespace cave {

	SkeletalMeshComponent::SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName, std::string parentNodeName) {
		m_model = Model(meshFileName, nodeName, groupName, parentNodeName);
		m_initialized = false;
	}
	void SkeletalMeshComponent::setRotation(caveQuat rotation) {
		m_model.setRotation(Ogre::Quaternion(rotation.fW, rotation.fX, rotation.fY, rotation.fZ));
	}
	void SkeletalMeshComponent::setTranslation(caveVec3f translation) {
		m_model.setTranslation(Ogre::Vector3(translation.x, translation.y, translation.z));
	}
	void SkeletalMeshComponent::setScaling(caveVec3f scaling) {
		m_model.setScaling(Ogre::Vector3(scaling.x, scaling.y, scaling.z));
	}
	void SkeletalMeshComponent::setParentNodeName(std::string parentNodeName) {
		m_model.setParentNodeName(parentNodeName);
	}



}
