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
		caveVec3f m_movementDirection;/**< Indica la direccion en la que se mueve la malla */
		float m_speed/**< Indica la rapidez de la malla */;
		std::vector<std::string> m_animations/**< Contiene los nombres de las animaciones asociados a la malla */;

		SkeletalMeshComponent(std::string meshFileName, std::string nodeName, std::string parentNodeName = "RootSceneNode");

		void setRotation(caveQuat rotation); /**< Setea rotacion asociada al componente (para nodo de scenegraph) */
		void setTranslation(caveVec3f translation);/**< Setea traslacion asociada al componente (para nodo de scenegraph)*/
		void setScaling(caveVec3f scaling);/**< Setea escalamiento asociada al componente (para nodo de scenegraph)*/
		void setParentNodeName(std::string parentNodeName);/**< Setea nombre del nodo padre asociado al componente (para nodo de scenegraph) */
		void moveMesh(caveVec3f velocity, float deltaTime);/**< Mueve la malla usando el vector de velocidad entregado */
		void addAnimation(std::string name, bool enabled, bool isLooping);/**< Agrega una animacion previamente cargada como recurso */
		void setAnimationEnabled(std::string name, bool enabled);/**< Activa o desactiva una animacion por nombre */
		void setAnimIsLooping(std::string name, bool isLooping);/**< Indica si la animacion esta en un loop */
		bool getAnimationEnabled(std::string name);/**< Indica si la animacion esta activada */
		bool getAnimIsLooping(std::string name);/**< Indica si la animacion esta en loop*/
		caveVec3f getMeshPosition();/**< Entrega la posicion global de la malla asociada */



	};




}

#endif