#pragma once
#ifndef RENDERINGMANAGER_HPP
#define RENDERINGMANAGER_HPP
#include <Ogre.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreCameraMan.h>
#include <OgreWindowEventUtilities.h>
#include <OgreApplicationContext.h>
#include <OgreFont.h>
#include <OgreFontManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreTextAreaOverlayElement.h>
#include "../Utils/Utils.hpp"
#include <iostream>
#include <map>

namespace cave {

	class Model {
	
	public:
		std::string m_meshFileName;
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

		Model(std::string meshFileName, std::string nodeName,std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");
		~Model();
	};

	class Font {
		public:
		std::string m_fontName;
		std::string m_fontFileName;
		Ogre::FontType m_fontType;
		std::string m_groupName;

		Font(std::string fontName, std::string fontFileName, 
			std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::FontType fontType = Ogre::FT_TRUETYPE);
		~Font();
	};


	class Overlay {
	public:
		std::string m_overlayName;
		std::string m_containerName;
		std::string m_type;
		Ogre::OverlayManager* m_overlayManager;
		Ogre::Overlay* m_overlay;
		Ogre::OverlayContainer* m_container;
		std::map<std::string, Ogre::TextAreaOverlayElement*> m_textElements;
		
		
		void configureContainer(float positionLeft, float positionTop, float width, float height);

		void addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height);

		void configureTextElement(std::string& textElementName, int fontSize, std::string fontName, Ogre::ColourValue colour);

		Overlay(std::string containerName, std::string overlayName = "overlay");
		~Overlay();
	};


	class RenderingManager: OgreBites::InputListener
	{

	public:
		Ogre::Root* m_root;
		Ogre::RenderWindow* m_window;
		Ogre::SceneManager* m_sceneManager;
		Ogre::Viewport* m_viewport;
		Ogre::Camera* m_camera;
		Ogre::SceneNode* m_cameraNode;
		OgreBites::ApplicationContext* m_context;
		//Ogre::OverlaySystem* m_overlaySystem;
		//incluir arreglo de modelos, con path, transformaciones iniciales, nombre, etc.

		void loadResourcesFolder(std::string path, std::string resourcesGroupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		void addResourcesToScene(std::vector<Model> &models);

		void configureTextResources(std::vector<Font>& fonts);

		void configureCamera(Ogre::Vector3 position, Ogre::Vector3 lookAt, OgreBites::CameraStyle cameraStyle= OgreBites::CameraStyle::CS_ORBIT, float nearClipDistance=1, float farClipDistance=1000);

		void StartUp();

		bool keyPressed(const OgreBites::KeyboardEvent& evt);

		void render();

		void drawText(Overlay& overlay, std::string& textElementName, std::string& caption);
		
		RenderingManager();
		~RenderingManager();



	};

}


#endif