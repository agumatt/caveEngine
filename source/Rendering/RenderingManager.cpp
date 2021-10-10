#include RenderingManager.h


namespace cave {

	RenderingManager::RenderingManager() {

		m_root = new Ogre::Root();
		if (!root.showConfigDialog()) {
			return -1;
		}
		//create render window
		m_window = m_root.initialize(true);
		//sceneManager represents the octtree
		m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC);
		
		m_camera = sceneManager->createCamera("mainCamera");
		//add camera to scene
		cameraNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		cameraNode->attachObject(m_camera);

		m_viewport = m_window->addViewport(m_camera);
	}
	RenderingManager::~RenderingManager() {
	}


	void RenderingManager::setUpScene() {
		
		
		//configure camera
		m_camera->setNearClipDistance(10);
		m_camera->setFarClipDistance(1000);

		m_viewport->setClearEveryFrame(true);
	}

}