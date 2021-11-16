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

	/**Esta clase representa un modelo a renderizar.
*
*/
	class Model {
	
	public:
		std::string m_meshFileName; /**< Path del archivo de la malla */
		std::string m_nodeName;/**< Nombre del nodo en el scene graph */
		std::string m_parentNodeName;/**< Nombre del nodo padre en el scene graph */
		std::string m_groupName; /**< Nombre del grupo de recursos de Ogre al que estara asociada la malla*/
		Ogre::Quaternion m_rotation;/**< Vector de rotacion que se asocia al nodo */
		Ogre::Vector3 m_translation;/**< Vector de traslacion que se asocia al nodo */
		Ogre::Vector3 m_scaling;/**< Vector de escalamiento que se asocia al nodo */
		bool m_inheritScale;/**<Setea si el nodo hereda la escala del nodo padre */
		bool m_inheritRotation;/**<Setea si el nodo hereda la rotacion del nodo padre */

		void setRotation(Ogre::Quaternion rotation);/**<Setea la rotacion del nodo */
		void setTranslation(Ogre::Vector3 translation);/**<Setea la traslacion del nodo */
		void setScaling(Ogre::Vector3 scaling);/**<Setea el escalamiento del nodo */
		void setParentNodeName(std::string parentNodeName);/**<Setea el nombre del nodo padre en el scene graph */
		void setTransformInheritance(bool inheritScale, bool inheritRotation);/**<Setea si el nodo hereda las transformaciones nodo padre */

		Model();
		Model(std::string meshFileName, std::string nodeName,std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");
	};

	/**Esta clase representa una fuente de texto.
		*
		*/
	class Font {
		public:
		std::string m_fontName;/**<Nombre de la fuente */
		std::string m_fontFileName;/**<Path de la fuente */
		Ogre::FontType m_fontType;/**<Tipo de la fuente */
		std::string m_groupName;/**< Nombre del grupo de recursos de Ogre al que estara asociada la fuente*/

		Font(std::string fontName, std::string fontFileName, 
			std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::FontType fontType = Ogre::FT_TRUETYPE);
		~Font();
	};

	/**Representa un plano contenedor sobre el que se dibujara texto.
		*
		*/
	class Overlay {
	public:
		std::string m_overlayName;/**<Nombre del overlay */
		std::string m_containerName;/**<Nombre del subcontenedor */
		std::string m_type;
		Ogre::OverlayManager* m_overlayManager;/**<Overlay manager de ogre */
		Ogre::Overlay* m_overlay;/**< overlay de ogre */
		Ogre::OverlayContainer* m_container;/**<overlay container de ogre */
		std::map<std::string, Ogre::TextAreaOverlayElement*> m_textElements;/**< Mapa que asocia los textElements del overlay a un nombre unico */
		
		
		void configureContainer(float positionLeft, float positionTop, float width, float height);/**<Configura tamanño y posicion del subcontenedor */

		void addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height);/**<Agrega elemento de texto al overlay */

		void configureTextElement(std::string& textElementName, int fontSize, std::string fontName, Ogre::ColourValue colour);/**<Configura elemento de texto seteando la fuente, su tamaño y color */

		Overlay(std::string containerName, std::string overlayName = "overlay");
		~Overlay();
	};

	/**Esta clase maneja el sistema de rendering del engine.
*
*/
	class RenderingManager: OgreBites::InputListener
	{

	public:
		static Ogre::Root* m_root;/**< Raiz de ogre */
		static Ogre::RenderWindow* m_window; /**< Ventana de ogre */
		static Ogre::SceneManager* m_sceneManager;/**< SceneManager de ogre */
		static Ogre::Viewport* m_viewport;/**< Viewport de ogre */
		static Ogre::Camera* m_camera; /**< Camara de ogre */
		static Ogre::SceneNode* m_cameraNode; /**< Nodo asociado a la camara */
		static OgreBites::ApplicationContext* m_context;/**< Contexto de ogre */
		//Ogre::OverlaySystem* m_overlaySystem;

		static caveVec3f getPlayerPosition();/**< Retorna la posicion del nodo que contiene la camara*/

		static void loadResourcesFolder(std::string path, std::string resourcesGroupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);/**< Carga recursos de la carpeta especificada */

		static void addModelsToScene(std::vector<Model> &models);/**< Agrega modelos a la escena */

		static void updateModelsInScene(std::vector<Model>& models);/**< Actualiza los modelos de la escena */

		static void configureTextResources(std::vector<Font>& fonts); /**< Setea las propiedades de las fuentes de texto en Ogre */

		/**Setea los valores de la camara
		*
		*/
		static void configureCamera(caveVec3f position, caveVec3f lookAt, OgreBites::CameraStyle cameraStyle= OgreBites::CameraStyle::CS_ORBIT, float nearClipDistance=1, float farClipDistance=1000);

		static void StartUp();/**< Inizializacion de elementos de la clase */

		static bool keyPressed(const OgreBites::KeyboardEvent& evt);/**< Indica si una tecla fue presionada */

		static void render(); /**< Renderiza la escena */

		static void drawText(Overlay& overlay, std::string& textElementName, std::string& caption); /**< Muestra el texto caption indicado en la escena utilizando un contenedor*/
		
		RenderingManager();



	};

}


#endif