#include "RenderingManager.hpp"


namespace cave {

	//RenderingManager

	RenderingManager::RenderingManager(){
		m_context = new OgreBites::ApplicationContext("RenderingManager");
		m_window = nullptr;
		m_viewport = nullptr;
		m_root = nullptr;
		m_sceneManager = nullptr;
		m_cameraNode = nullptr;
		m_camera = nullptr;
		m_context->initApp();
		//m_overlaySystem = nullptr;

		// register for input events
		m_context->addInputListener(this);

		//save root
		m_root = m_context->getRoot();

		//sceneManager represents the octree
		m_sceneManager = m_root->createSceneManager();

		//init resources
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

		// register our scene with the RTSS
		Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		shadergen->addSceneManager(m_sceneManager);


		//add camera to scene
		m_camera = m_sceneManager->createCamera("mainCamera");
		m_cameraNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		m_cameraNode->attachObject(m_camera);

		//overlay
		//Ogre::OverlaySystem* m_overlaySystem = new Ogre::OverlaySystem();
		//m_sceneManager->addRenderQueueListener(m_overlaySystem);


	}
	RenderingManager::~RenderingManager() {
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


	void RenderingManager::StartUp() {
		try {
			std::cout << "RenderingManager startUp init.";
			//get render window
			m_window = m_context->getRenderWindow();


			m_viewport = m_window->addViewport(m_camera);
			m_viewport->setClearEveryFrame(true);
			//set lighting
			m_sceneManager->setAmbientLight(Ogre::ColourValue::White);

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

	void RenderingManager::configureTextResources(std::vector<Font>& fonts) {
		for (unsigned int i = 0; i < fonts.size(); i = i + 1) {
			Font font = fonts[i];
			Ogre::FontPtr fontPtr = Ogre::FontManager::getSingleton().create(font.m_fontName, font.m_groupName);
			fontPtr->setType(font.m_fontType);
			fontPtr->setSource(font.m_fontFileName);		
		}	
	};

	void RenderingManager::addResourcesToScene(std::vector<Model> &models) {
		for (unsigned int i = 0; i < models.size(); i = i + 1) {
			Model model = models[i];
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
			newNode->translate(model.m_initialTranslation);
			newNode->rotate(model.m_initialRotation);
			newNode->scale(model.m_initialScaling);
			Ogre::Entity* newEntity = m_sceneManager->createEntity(model.m_meshFileName);
			newNode->attachObject(newEntity);

		}
	}

	void RenderingManager::drawText(Overlay& overlay, std::string& textElementName, std::string& caption) {
		auto textElement = overlay.m_textElements[textElementName];
		textElement->setCaption(caption);
		overlay.m_overlay->show();
	}

	
	void RenderingManager::render() {
		m_root->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}


	void RenderingManager::configureCamera(Ogre::Vector3 position, Ogre::Vector3 lookAt, OgreBites::CameraStyle cameraStyle, float nearClipDistance, float farClipDistance) {
		//config camera
		m_camera->setAutoAspectRatio(true);
		m_camera->setNearClipDistance(nearClipDistance);
		m_camera->setFarClipDistance(farClipDistance);
		m_cameraNode->setPosition(position);
		m_cameraNode->lookAt(lookAt, Ogre::Node::TS_PARENT);
		//create cameraMan
		OgreBites::CameraMan* cameraMan = new OgreBites::CameraMan(m_cameraNode);
		cameraMan->setStyle(cameraStyle);
		cameraMan->setTopSpeed(60);
		//cameraMan.setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0.3), 15);
		m_context->addInputListener(cameraMan);
	}
	
	
	//Model

	Model::Model(std::string meshFileName, std::string nodeName, std::string groupName, std::string parentNodeName) {
		m_meshFileName = meshFileName;
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


	//Font
	Font::Font(std::string fontName, std::string fontFileName, std::string groupName, Ogre::FontType fontType) {
		m_fontName = fontName;
		m_fontFileName = fontFileName;
		m_groupName = groupName;
		m_fontType = fontType;
	}
	Font::~Font() {	}

	//Overlay
	Overlay::Overlay(std::string containerName, std::string overlayName) {
		m_overlayName= overlayName;
		m_containerName = containerName;
		m_textElements = {};
		m_overlayManager = Ogre::OverlayManager::getSingletonPtr();
		m_overlay = m_overlayManager->create(m_overlayName);
		m_container = static_cast<Ogre::OverlayContainer*>(
			m_overlayManager->createOverlayElement("Panel", m_containerName)
			);
		m_container->setMetricsMode(Ogre::GMM_RELATIVE);
		m_overlay->add2D(m_container);
		
	}

	void Overlay::configureContainer(float positionLeft, float positionTop, float width, float height) {
		m_container->setPosition(positionLeft, positionTop);
		m_container->setDimensions(width, height);
	}

	void Overlay::addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height) {
		
		Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*> (m_overlayManager->createOverlayElement("TextArea", textElementName));
		textArea->setPosition(positionLeft, positionTop);
		textArea->setDimensions(width, height);;
		m_container->addChild(textArea);
		m_textElements[textElementName] = textArea;
	}

	void Overlay::configureTextElement(std::string& textElementName, int fontSize, std::string fontName, Ogre::ColourValue colour) {
		Ogre::TextAreaOverlayElement* textElement = m_textElements[textElementName];
		textElement->setCharHeight(fontSize);
		textElement->setFontName(fontName);
	}



}