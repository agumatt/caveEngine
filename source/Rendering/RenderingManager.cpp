#include "RenderingManager.hpp"


namespace cave {

	//RenderingManager

	RenderingManager::RenderingManager(): OgreBites::ApplicationContext("RenderingManager"){
		m_window = nullptr;
		m_viewport = nullptr;
		m_root = nullptr;
		m_sceneManager = nullptr;
		m_cameraNode = nullptr;
		m_camera = nullptr;
		initApp();

	}
	RenderingManager::~RenderingManager() {
	}

	//! [key_handler]
	bool RenderingManager::keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		std::cout << "pressed SOMETHING";
		if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
		{
			getRoot()->queueEndRendering();
			closeApp();
		}
		return true;
	}
	//! [key_handler]


	void RenderingManager::setup() {
		OgreBites::ApplicationContext::setup();
		// register for input events
		m_root = getRoot();

		// register for input events
		addInputListener(this);

		//sceneManager represents the octree
		m_sceneManager = m_root->createSceneManager();

		//init resourceGroupManager
		//Ogre::ResourceGroupManager::ResourceGroupManager();
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

		// register our scene with the RTSS
		Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(m_sceneManager);


		//add camera to scene
		m_camera = m_sceneManager->createCamera("mainCamera");
		m_cameraNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		m_cameraNode->attachObject(m_camera);
	}

	void RenderingManager::StartUp(OgreBites::CameraStyle cameraStyle) {
		try {
			std::cout << "RenderingManager startUp init.";
			//get render window
			m_window = getRenderWindow();


			//configure camera
			m_camera->setNearClipDistance(5);
			m_camera->setAutoAspectRatio(true);


			//if (cameraStyle == OgreBites::CameraStyle::CS_PLAYER) {
			//}
			//else {
			//	OgreBites::CameraMan cameraMan = OgreBites::CameraMan(m_cameraNode);
		//		cameraMan.setStyle(cameraStyle);
			//}

			m_viewport = m_window->addViewport(m_camera);
			m_viewport->setClearEveryFrame(true);
			//set lighting
			//m_sceneManager->setAmbientLight(Ogre::ColourValue::White);
			Ogre::Light* light = m_sceneManager->createLight("MainLight");
			Ogre::SceneNode* lightNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
			lightNode->setPosition(0, 10, 15);
			lightNode->attachObject(light);

			std::cout << "RenderingManager startUp finished.";
		}
		catch(Ogre::Exception& ex){
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
	}


	void RenderingManager::loadResourcesFolder(std::string path, std::string resourcesGroupName) {

		Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(path, "FileSystem", resourcesGroupName);
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(resourcesGroupName);
		Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup(resourcesGroupName);


	}

	void RenderingManager::addResourcesToScene(std::vector<Model> &models) {
		for (unsigned int i = 0; i < models.size(); i = i + 1) {
			Model model = models[i];
			std::cout << "Cargando modelo: " << model.m_meshName;
			Ogre::SceneNode* parentNode = NULL;
			if (model.m_parentNodeName == "RootSceneNode") {
				parentNode = m_sceneManager->getRootSceneNode();
			}
			else {
				try {
					parentNode = m_sceneManager->getSceneNode(model.m_parentNodeName);
				}
				catch (Ogre::Exception& ex) {
					std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
				}
			}
			Ogre::SceneNode* newNode = parentNode->createChildSceneNode(model.m_nodeName);
			newNode->translate(model.m_initialTranslation);
			newNode->rotate(model.m_initialRotation);
			newNode->scale(model.m_initialScaling);
			Ogre::Entity* newEntity = m_sceneManager->createEntity(model.m_meshName);
			newNode->attachObject(newEntity);

		}
	}

	
	void RenderingManager::render() {
		m_root->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}


	void RenderingManager::configureCamera(Ogre::Vector3 position, Ogre::Vector3 lookAt, float nearClipDistance, float farClipDistance) {
		m_camera->setNearClipDistance(nearClipDistance);
		m_camera->setFarClipDistance(farClipDistance);
		m_cameraNode->setPosition(position);
		m_cameraNode->lookAt(lookAt, Ogre::Node::TS_PARENT);
	}

	//Model

	Model::Model(std::string meshName, std::string groupName, std::string nodeName, std::string parentNodeName) {
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