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
		bool m_moving;/**< Indica si la malla se esta moviendo */
		caveVec3f m_movementDirection;
		float m_speed;

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string parentNodeName = "RootSceneNode");

		void setRotation(caveQuat rotation); /**< Setea rotacion asociada al componente (para nodo de scenegraph) */
		void setTranslation(caveVec3f translation);/**< Setea traslacion asociada al componente (para nodo de scenegraph)*/
		void setScaling(caveVec3f scaling);/**< Setea escalamiento asociada al componente (para nodo de scenegraph)*/
		void setParentNodeName(std::string parentNodeName);/**< Setea nombre del nodo padre asociado al componente (para nodo de scenegraph) */
		void moveMesh(caveVec3f velocity, float deltaTime);
		caveVec3f getMeshPosition();


	};




}

#endif