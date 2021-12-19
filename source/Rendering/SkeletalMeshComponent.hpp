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
		std::vector<std::string> m_animations;

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string parentNodeName = "RootSceneNode");

		void setRotation(caveQuat rotation); /**< Setea rotacion asociada al componente (para nodo de scenegraph) */
		void setTranslation(caveVec3f translation);/**< Setea traslacion asociada al componente (para nodo de scenegraph)*/
		void setScaling(caveVec3f scaling);/**< Setea escalamiento asociada al componente (para nodo de scenegraph)*/
		void setParentNodeName(std::string parentNodeName);/**< Setea nombre del nodo padre asociado al componente (para nodo de scenegraph) */
		void moveMesh(caveVec3f velocity, float deltaTime);
		void addAnimation(std::string name, bool enabled, bool isLooping);
		void setAnimationEnabled(std::string name, bool enabled);
		void setAnimIsLooping(std::string name, bool isLooping);
		bool getAnimationEnabled(std::string name);
		bool getAnimIsLooping(std::string name);
		caveVec3f getMeshPosition();



	};




}

#endif