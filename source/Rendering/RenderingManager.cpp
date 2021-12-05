#include "RenderingManager.hpp"


namespace cave {

	//RenderingManager
	Ogre::Root* RenderingManager::m_root;
	Ogre::RenderWindow* RenderingManager::m_window;
	Ogre::SceneManager* RenderingManager::m_sceneManager;
	Ogre::Viewport* RenderingManager::m_viewport;
	Ogre::Camera* RenderingManager::m_camera;
	Ogre::SceneNode* RenderingManager::m_cameraNode;
	OgreBites::ApplicationContext* RenderingManager::m_context;
	Ogre::OverlaySystem* RenderingManager::m_overlaySystem;
	std::string RenderingManager::m_resourcesGroupName;

	caveVec3f RenderingManager::getPlayerPosition() {
		Ogre::Vector3 pos = m_cameraNode->_getDerivedPosition();
		return caveVec3f(pos.x, pos.y, pos.z);
	}


	bool RenderingManager::keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
		{
			m_root->queueEndRendering();
			m_context->closeApp();
		}
		return true;
	}

	RenderingManager::RenderingManager() {
		m_context = new OgreBites::ApplicationContext("RenderingManager");
		m_context->initApp();
		m_window = nullptr;
		m_viewport = nullptr;
		m_root = nullptr;
		m_sceneManager = nullptr;
		m_cameraNode = nullptr;
		m_camera = nullptr;
		m_overlaySystem = nullptr;
		m_resourcesGroupName = "caveResourcesGroup";

		// register for input events
		m_context->addInputListener(this);

		//save root
		m_root = m_context->getRoot();

		//sceneManager represents the octree
		m_sceneManager = m_root->createSceneManager();
	}

	void RenderingManager::StartUp() {
		

		//init resources
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

		// register our scene with the RTSS
		Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(m_sceneManager);


		//add camera to scene
		m_camera = m_sceneManager->createCamera("mainCamera");
		m_cameraNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		m_cameraNode->attachObject(m_camera);


		try {
			//overlay system
			m_overlaySystem = m_context->getOverlaySystem();
			m_sceneManager->addRenderQueueListener(m_overlaySystem);

			//get render window
			m_window = m_context->getRenderWindow();


			m_viewport = m_window->addViewport(m_camera);
			m_viewport->setClearEveryFrame(true);
			//set lighting
			m_sceneManager->setAmbientLight(Ogre::ColourValue::White);
		}
		catch(Ogre::Exception& ex){
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
	}


	void RenderingManager::loadResourcesFolder(std::string path) {
		Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(path, "FileSystem", m_resourcesGroupName);
	}

	void RenderingManager::loadFont(std::string fontName, std::string fontFileName) {
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(m_resourcesGroupName);
		std::cout << "HOLA1" << std::endl;
		try {
			Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup(m_resourcesGroupName);
		}
		catch (Ogre::Exception& ex) {
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
		Ogre::FontPtr fontPtr = Ogre::FontManager::getSingleton().getByName(fontName, m_resourcesGroupName);
		//fontPtr->setTrueTypeSize(50);
		std::cout << "LOADING FONT" << std::endl;
		try {
			fontPtr->load();
		}
		catch (Ogre::Exception& ex) {
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
		std::cout << "FONT LOADED" << std::endl;
	}


	void RenderingManager::addModelsToScene(std::vector<Model> &models) {
		for (unsigned int i = 0; i < models.size(); i = i + 1) {
			Model model = models[i];
			Ogre::ResourceGroupManager::getSingletonPtr()->declareResource(model.m_meshFileName, "Mesh", m_resourcesGroupName);
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(m_resourcesGroupName);
			std::cout << "Cargando modelo: " << model.m_meshFileName;
			std::cout << "Nodo padre: " << model.m_parentNodeName;
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
			
			newNode->translate(model.m_translation);
			newNode->rotate(model.m_rotation);
			newNode->scale(model.m_scaling);
			newNode->setInheritOrientation(model.m_inheritRotation);
			newNode->setInheritScale(model.m_inheritScale);
			Ogre::Entity* newEntity = m_sceneManager->createEntity(model.m_meshFileName);
			newNode->attachObject(newEntity);

		}
	}

	void RenderingManager::updateModelsInScene(std::vector<Model>& models) {
		for (unsigned int i = 0; i < models.size(); i = i + 1) {
			Model model = models[i];
			Ogre::SceneNode* node = nullptr;
			Ogre::SceneNode* newParentNode = nullptr;
			try {
				node = m_sceneManager->getSceneNode(model.m_nodeName);
				newParentNode = m_sceneManager->getSceneNode(model.m_parentNodeName);
			}
			catch(Ogre::Exception& ex) {
				std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
			}
			node->getParentSceneNode()->removeChild(node);
			newParentNode->addChild(node);
			node->setInheritOrientation(model.m_inheritRotation);
			node->setInheritScale(model.m_inheritScale);
			
			node->translate(model.m_translation);
			node->rotate(model.m_rotation);
			node->scale(model.m_scaling);		
		}

	}

	
	void RenderingManager::render() {
		m_root->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}


	void RenderingManager::configureCamera(caveVec3f position, caveVec3f lookAt, float nearClipDistance, float farClipDistance) {
		//config camera
		Ogre::Vector3 ogrePos = Ogre::Vector3(position.x, position.y, position.z);
		Ogre::Vector3 ogreLookAt = Ogre::Vector3(lookAt.x, lookAt.y, lookAt.z);
		m_camera->setAutoAspectRatio(true);
		m_camera->setNearClipDistance(nearClipDistance);
		m_camera->setFarClipDistance(farClipDistance);
		m_cameraNode->setPosition(ogrePos);
		m_cameraNode->lookAt(ogreLookAt, Ogre::Node::TS_PARENT);
		//create cameraMan
		OgreBites::CameraMan* cameraMan = new OgreBites::CameraMan(m_cameraNode);
		cameraMan->setStyle(OgreBites::CameraStyle::CS_FREELOOK);
		cameraMan->setTopSpeed(60);
		//cameraMan.setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0.3), 15);
		m_context->addInputListener(cameraMan);
	}
	
	
	//Model

	Model::Model(std::string meshFileName, std::string nodeName, std::string parentNodeName) {
		m_meshFileName = meshFileName;
		m_groupName = RenderingManager::m_resourcesGroupName;
		m_nodeName = nodeName;
		m_parentNodeName = parentNodeName;
		m_rotation = Ogre::Quaternion::IDENTITY;
		m_translation = Ogre::Vector3(0, 0, 0);
		m_scaling = Ogre::Vector3(1, 1, 1);
		m_inheritScale = false;
		m_inheritRotation = false;
	}
	Model::Model() {

	}

	void Model::setRotation(Ogre::Quaternion rotation) {
		m_rotation = rotation;
	}
	void Model::setTranslation(Ogre::Vector3 translation) {
		m_translation = translation;
	}
	void Model::setScaling(Ogre::Vector3 scaling) {
		m_scaling = scaling;
	}
	void Model::setParentNodeName(std::string parentNodeName) {
		m_parentNodeName = parentNodeName;
	}

	void Model::setTransformInheritance(bool inheritScale, bool inheritRotation) {
		m_inheritScale = inheritScale;
		m_inheritRotation = inheritRotation;
	}

	//Container
	int Container::m_count = 0;
	Container::Container() {
		std::string containerName = "container" + std::to_string(m_count);
		std::string overlayName = "overlay" + std::to_string(m_count);
		m_id = m_count;
		auto overlayManager = Ogre::OverlayManager::getSingletonPtr();
		m_overlay = overlayManager->create(overlayName);
		m_count = m_count + 1;
		std::cout << "CONTAINER COUNT: " << m_count;
		m_containerName = containerName;
		m_textElements = {};
		m_overlayManager = Ogre::OverlayManager::getSingletonPtr();
		m_container = static_cast<Ogre::OverlayContainer*>(
			m_overlayManager->createOverlayElement("Panel", m_containerName)
			);
		m_container->setMetricsMode(Ogre::GMM_RELATIVE);
		m_container->setPosition(0, 0);
		m_container->setDimensions(1.0f, 1.0f);
		m_overlay->add2D(m_container);
		
	}

	void Container::configureContainer(float positionLeft, float positionTop, float width, float height) {
		m_container->setPosition(positionLeft, positionTop);
		m_container->setDimensions(width, height);
	}

	void Container::displayText(std::string& textElementName, std::string& caption) {
		m_overlay->show();
		std::string textElementNameWid = std::to_string(m_id) + "_" + textElementName;
		auto textElement = m_textElements[textElementNameWid];
		textElement->setCaption(caption);
	}

	void Container::hideTextContainer() {
		m_overlay->hide();
	}

	void Container::addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height) {
		std::string textElementNameWid = std::to_string(m_id) + "_" + textElementName;
		if (m_textElements.count(textElementNameWid) == 0) {
			Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*> (m_overlayManager->createOverlayElement("TextArea", textElementNameWid));
			textArea->setPosition(positionLeft, positionTop);
			textArea->setDimensions(width, height);
			textArea->setMetricsMode(Ogre::GMM_RELATIVE);
			m_container->addChild(textArea);
			m_textElements[textElementNameWid] = textArea;
		}			
	}

	void Container::configureTextElement(std::string& textElementName, float fontSize, std::string fontName, Ogre::ColourValue colour) {
		std::string textElementNameWid = std::to_string(m_id) + "_" + textElementName;
		Ogre::TextAreaOverlayElement* textElement = m_textElements[textElementNameWid];
		std::cout << "text size: " << textElement->getCharHeight();
		textElement->setCharHeight(fontSize);
		std::cout << "text size: " << textElement->getCharHeight();
		textElement->setFontName(fontName);
		textElement->setColour(colour);
	}



}