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
#include "../Utils/LibUtils.hpp"
#include "../Utils/Utils.hpp"
#include "../Core/Log.hpp"

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

		Model() = default;
		Model(std::string meshFileName, std::string nodeName, std::string parentNodeName = "RootSceneNode");
	};


	/**Representa un plano contenedor sobre el que se dibujara texto.
		*
		*/
	class Container {
	public:
		static int m_count;
		std::string m_containerName;/**<Nombre del subcontenedor */
		Ogre::Overlay* m_overlay;/**< overlay de ogre */
		Ogre::OverlayContainer* m_container;/**<overlay container de ogre */
		Ogre::OverlayManager* m_overlayManager;
		int m_id;
		std::map<std::string, Ogre::TextAreaOverlayElement*> m_textElements;/**< Mapa que asocia los textElements del overlay a un nombre unico */
		
		void displayText(std::string& textElementName, std::string& caption);

		void hideTextContainer();

		void configureContainer(float positionLeft, float positionTop, float width, float height);/**<Configura tamanño y posicion del subcontenedor */

		void addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height);/**<Agrega elemento de texto al overlay */

		void configureTextElement(std::string& textElementName, float fontSize, std::string fontName, Ogre::ColourValue colour);/**<Configura elemento de texto seteando la fuente, su tamaño y color */

		Container();
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
		static Ogre::OverlaySystem* m_overlaySystem;
		static std::string m_resourcesGroupName;

		static caveVec3f getPlayerPosition();/**< Retorna la posicion del nodo que contiene la camara*/

		static void loadResourcesFolder(std::string path);/**< Carga recursos de la carpeta especificada */

		static void addModelsToScene(std::vector<Model> &models);/**< Agrega modelos a la escena */

		static void updateModelsInScene(std::vector<Model>& models);/**< Actualiza los modelos de la escena */


		/**Agrega una fuente de texto a Ogre 		
		* 
		*/
		static void loadFont(std::string fontName, std::string fontFileName);

		/**Setea los valores de la camara
		*
		*/
		static void configureCamera(caveVec3f position, caveVec3f lookAt, float nearClipDistance=1, float farClipDistance=1000);

		static void setUpCamera(caveVec3f position, caveVec3f lookAt, float nearClipDistance = 1, float farClipDistance = 1000);

		static void StartUp();/**< Inizializacion de elementos de la clase */

		bool keyPressed(const OgreBites::KeyboardEvent& evt);/**< Indica si una tecla fue presionada */

		static void render(); /**< Renderiza la escena */
		
		RenderingManager();



	};

	class RenderingUtils {

	public:
		RenderingUtils() = default;
		static void createPlane(caveVec3f upVector, caveVec3f position, std::string nodeName,float tilesX, float tilesY, float width, float height, std::string materialName);

	};

}


#endif