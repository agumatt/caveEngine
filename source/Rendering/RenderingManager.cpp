#include "RenderingManager.hpp"
#include <iostream>


namespace cave {

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
		}
		catch(Ogre::Exception &ex){
			std::cerr << "An exception ocurred: " << ex.getDescription() << std::endl;
		}
	}


	void RenderingManager::render() {

	}

}