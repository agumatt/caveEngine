#pragma once
#ifndef SKELETALMESHCOMPONENT_HPP
#define SKELETALMESHCOMPONENT_HPP
#include "RenderingManager.hpp"


namespace cave {
	
	/**Componente que representa una modelo renderizable (y animable).
*
*/
	struct SkeletalMeshComponent {

		Model m_model; /**< Modelo asociado al componente */
		bool m_initialized;/**< Indica si el componente fue inicializado */

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, std::string parentNodeName = "RootSceneNode");

		void setRotation(caveQuat rotation); /**< Setea rotacion asociada al componente (para nodo de scenegraph) */
		void setTranslation(caveVec3f translation);/**< Setea traslacion asociada al componente (para nodo de scenegraph)*/
		void setScaling(caveVec3f scaling);/**< Setea escalamiento asociada al componente (para nodo de scenegraph)*/
		void setParentNodeName(std::string parentNodeName);/**< Setea nombre del nodo padre asociado al componente (para nodo de scenegraph) */


	};




}

#endif