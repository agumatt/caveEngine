#include "SkeletalMeshComponent.hpp"

namespace cave {

	SkeletalMeshComponent::SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string parentNodeName) {
		m_model = Model(meshFileName, nodeName, parentNodeName);
		m_initialized = false;
		m_moving = false;
		m_movementDirection = caveVec3f(0,0,0);
		m_animations = {};
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

	void SkeletalMeshComponent::addAnimation(std::string name, bool enabled, bool isLooping) {
		if (std::find(m_animations.begin(), m_animations.end(), name) != m_animations.end()) {
			std::cerr << "Animation name already registered!" << std::endl;
		}
		Ogre::SceneNode* node;
		try {
			node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		}
		catch (Ogre::Exception& ex) {
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
		Ogre::Entity* entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
		if (entity != nullptr) {
			Ogre::AnimationState* anim = entity->getAnimationState(name);
			m_animations.push_back(name);
			anim->setLoop(isLooping);
			anim->setEnabled(enabled);
		}
	}
	void SkeletalMeshComponent::setAnimationEnabled(std::string name, bool enabled) {
		if (std::find(m_animations.begin(), m_animations.end(), name) == m_animations.end()) {
			std::cerr << "Animation has not been not registered" << std::endl;
		}
		Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		Ogre::Entity* entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
		Ogre::AnimationState* anim = entity->getAnimationState(name);
		anim->setEnabled(enabled);
	}
	void SkeletalMeshComponent::setAnimIsLooping(std::string name, bool isLooping) {
		if (std::find(m_animations.begin(), m_animations.end(), name) == m_animations.end()) {
			std::cerr << "Animation has not been not registered" << std::endl;
		}
		Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		Ogre::Entity* entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
		Ogre::AnimationState* anim = entity->getAnimationState(name);
		anim->setLoop(isLooping);


	}
	bool SkeletalMeshComponent::getAnimationEnabled(std::string name) {
		if (std::find(m_animations.begin(), m_animations.end(), name) == m_animations.end()) {
			std::cerr << "Animation has not been not registered" << std::endl;
		}
		Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		Ogre::Entity* entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
		Ogre::AnimationState* anim = entity->getAnimationState(name);
		return anim->getEnabled();
		

	}
	bool SkeletalMeshComponent::getAnimIsLooping(std::string name) {
		if (std::find(m_animations.begin(), m_animations.end(), name) == m_animations.end()) {
			std::cerr << "Animation has not been not registered" << std::endl;
		}
		Ogre::SceneNode* node = RenderingManager::m_sceneManager->getSceneNode(m_model.m_nodeName);
		Ogre::Entity* entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
		Ogre::AnimationState* anim = entity->getAnimationState(name);
		return anim->getLoop();
	}

}
