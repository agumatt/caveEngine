#include "RenderingManager.hpp"


namespace cave {

	//RenderingManager

	RenderingManager::RenderingManager() {

		m_root = new Ogre::Root();
		
		//sceneManager represents the octree
		m_sceneManager = m_root->createSceneManager();
		
		m_camera = m_sceneManager->createCamera("mainCamera");

		//add camera to scene
		m_cameraNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		m_cameraNode->attachObject(m_camera);

	}
	RenderingManager::~RenderingManager() {
	}


	void RenderingManager::StartUp(OgreBites::CameraStyle cameraStyle) {
		try {
			if (!m_root->showConfigDialog(NULL)) {
				return;
			}
			//create render window
			m_window = m_root->initialise(true);

			

			//configure camera
			m_camera->setNearClipDistance(10);
			m_camera->setFarClipDistance(1000);
			if (cameraStyle == OgreBites::CameraStyle::CS_PLAYER) {

			}
			else {
				OgreBites::CameraMan cameraMan = OgreBites::CameraMan(m_cameraNode);
				cameraMan.setStyle(cameraStyle);
			}
			
			m_viewport = m_window->addViewport(m_camera);
			m_viewport->setClearEveryFrame(true);

			//set lighting
			m_sceneManager->setAmbientLight(Ogre::ColourValue::White);
		}
		catch(Ogre::Exception& ex){
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
	}

	RenderingManager::loadResourcesFolder(std::string path, std::string resourcesGroupName) {

		if (!Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroup(resourcesGroupName)) {
			Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup(resourcesGroupName);
		}
		Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(path, 'FileSystem', resourcesGroupName);
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(resourcesGroupName);
		Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup(resourcesGroupName);


	}

	void RenderingManager::addResourcesToScene(Model models[]) {
		for (const Model& model : models) {
			Ogre::SceneNode parentNode = NULL;
			if (model.m_parentNodeName == 'RootSceneNode') {
				parentNode = m_sceneManager->getRootSceneNode();
			}
			else {
				try {
					parentNode = m_sceneManager->getSceneNode(model.m_parentNodeName);
				}
				catch (Ogre::Exception& ex) {
					std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
				}
				Ogre::SceneNode newNode = parentNode->createChildSceneNode(model.m_nodeName);
				newNode.translate(model.m_initialTranslation);
				newNode.rotate(model.m_initialRotation);
				newNode.scale(model.m_initialScaling);
				Ogre::Entity newEntity = m_sceneManager->createEntity(model.meshName);
				newNode.attachObject(newEntity);

			}

		}
	}

	void RenderingManager::render() {
		m_root->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}

	//Model

	Model::Model(std::string meshName, std::string groupName, std::string nodeName, std::string parentNodeName = "RootSceneNode") {
		m_meshName = meshName;
		m_groupName = groupName;
		m_nodeName = nodeName;
		m_parentNodeName = parentNodeName;
		m_initialRotation = Ogre::Quaternion::IDENTITY;
		m_initialTranslation = Ogre::Vector3(0, 0, 0);
		m_initialScaling = Ogre::Vector3(1, 1, 1);
	}

	Model::~Model() {

	}

	void Model::setInitialRotation(Ogre::Quaternion initialRotation) {
		m_initialRotation = initialRotation;
	}
	void Model::setInitialTranslation(Ogre::Vector3 initialTranslation) {
		m_initialTranslation = initialTranslation;
	}
	void Model::setInitialScaling(Ogre::Vector3 initialScaling) {
		m_initialScaling = initialScaling;
	}
	void Model::setParentNodeName(std::string parentNodeName) {
		m_parentNodeName = parentNodeName;
	}


}