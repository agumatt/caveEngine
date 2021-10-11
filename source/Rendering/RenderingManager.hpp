#pragma once
#ifndef RENDERINGMANAGER_HPP
#define RENDERINGMANAGER_HPP
#include <Ogre.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreCameraMan.h>

namespace cave {

	class RenderingManager
	{

	public:
		Ogre::Root* m_root;
		Ogre::RenderWindow* m_window;
		Ogre::SceneManager* m_sceneManager;
		Ogre::Viewport* m_viewport;
		Ogre::Camera* m_camera;
		Ogre::SceneNode* m_cameraNode;
		//incluir arreglo de modelos, con path, transformaciones iniciales, nombre, etc.

		void loadModels();

		void loadTerrain();

		void StartUp(OgreBites::CameraStyle cameraStyle);

		void render();


	private:
		RenderingManager();
		~RenderingManager();



	};

}

#endif