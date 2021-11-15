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
		Ogre::Quaternion m_rotation;
		Ogre::Vector3 m_translation;
		Ogre::Vector3 m_scaling;
		bool m_inheritScale;
		bool m_inheritRotation;

		void setRotation(Ogre::Quaternion rotation);
		void setTranslation(Ogre::Vector3 translation);
		void setScaling(Ogre::Vector3 scaling);
		void setParentNodeName(std::string parentNodeName);
		void setTransformInheritance(bool inheritScale, bool inheritRotation);

		Model();
		Model(std::string meshFileName, std::string nodeName,std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");
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
		static Ogre::Root* m_root;
		static Ogre::RenderWindow* m_window;
		static Ogre::SceneManager* m_sceneManager;
		static Ogre::Viewport* m_viewport;
		static Ogre::Camera* m_camera;
		static Ogre::SceneNode* m_cameraNode;
		static OgreBites::ApplicationContext* m_context;
		//Ogre::OverlaySystem* m_overlaySystem;
		//incluir arreglo de modelos, con path, transformaciones iniciales, nombre, etc.

		static void loadResourcesFolder(std::string path, std::string resourcesGroupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		static void addModelsToScene(std::vector<Model> &models);

		static void updateModelsInScene(std::vector<Model>& models);

		static void configureTextResources(std::vector<Font>& fonts);

		static void configureCamera(caveVec3f position, caveVec3f lookAt, OgreBites::CameraStyle cameraStyle= OgreBites::CameraStyle::CS_ORBIT, float nearClipDistance=1, float farClipDistance=1000);

		static void StartUp();

		static bool keyPressed(const OgreBites::KeyboardEvent& evt);

		static void render();

		static void drawText(Overlay& overlay, std::string& textElementName, std::string& caption);
		
		RenderingManager();



	};

}


#endif