#include "SkeletalMeshComponent.hpp"

namespace cave {

	SkeletalMeshComponent::SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string parentNodeName) {
		m_model = Model(meshFileName, nodeName, parentNodeName);
		m_initialized = false;
		m_moving = false;
		m_movementDirection = caveVec3f(0,0,0);
		float m_speed = 60.0f;
	}
	void SkeletalMeshComponent::setRotation(caveQuat rotation) {
		m_model.setRotation(Ogre::Quaternion(rotation.w, rotation.x, rotation.y, rotation.z));
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

	caveVec3f SkeletalMeshComponent::getMeshPosition() {
		Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		Ogre::Vector3f ogrePos = node->_getDerivedPosition();
		return caveVec3f(ogrePos.x, ogrePos.y, ogrePos.z);
	}

	void SkeletalMeshComponent::moveMesh(caveVec3f velocity, float deltaTime) {
		Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		Ogre::Vector3f currentPos = node->_getDerivedPosition();
		Ogre::Vector3f deltaPos = Ogre::Vector3f(velocity.x, velocity.y, velocity.z) * deltaTime;
		Ogre::Vector3f newPos = currentPos + deltaPos;
		Ogre::SceneNode* parentNode = node->getParentSceneNode();
		//find where the node would end up in parent's local space
		Ogre::Vector3f localPos = parentNode->convertWorldToLocalPosition(newPos);
		setTranslation(caveVec3f(localPos.x, localPos.y, localPos.z));
	}

}
