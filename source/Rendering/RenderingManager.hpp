#pragma once
#ifndef RENDERINGMANAGER_HPP
#define RENDERINGMANAGER_HPP
#include <Ogre.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreCameraMan.h>
#include <OgreWindowEventUtilities.h>
#include <iostream>

namespace cave {


	class Model {
	
	public:
		std::string m_meshName;
		std::string m_nodeName;
		std::string m_parentNodeName;
		std::string m_groupName; //to associate with other models
		Ogre::Quaternion m_initialRotation;
		Ogre::Vector3 m_initialTranslation;
		Ogre::Vector3 m_initialScaling;

		void setInitialRotation(Ogre::Quaternion initialRotation);
		void setInitialTranslation(Ogre::Vector3 initialTranslation);
		void setInitialScaling(Ogre::Vector3 initialScaling);
		void setParentNodeName(std::string parentNodeName);

		Model(std::string meshName, std::string groupName, std::string nodeName, std::string parentNodeName = "RootSceneNode");
		~Model();
	};

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

		void loadResourcesFolder(std::string path, std::string resourcesGroupName);

		void addResourcesToScene(Model* models[]);

		void StartUp(OgreBites::CameraStyle cameraStyle);

		void render();

		RenderingManager();
		~RenderingManager();



	};

}


#endif