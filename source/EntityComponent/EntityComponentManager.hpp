#pragma once
#ifndef ENTITYCOMPONENTMANAGER_HPP
#define ENTITYCOMPONENTMANAGER_HPP
#include "../Rendering/CameraComponent.hpp"
#include "../Rendering/SkeletalMeshComponent.hpp"
#include "../Rendering/TextComponent.hpp"
#include "../Audio/AudioSourceComponent.hpp"
#include "../Events/EventRegistryComponent.hpp"
#include "../../thirdParty/entt/entt.hpp"

namespace cave {
	
	/**Esta clase maneja el sistema de entidad componente.
	*
	*/
	class EntityComponentManager {
		
	public:
		
		static entt::registry m_Registry; /**< Maneja las entidades*/
		static std::map<std::string, entt::entity> m_entities; /**< Mapa que contiene las entidades y sus nombres unicos*/

		static void StartUp();/**< Inizializacion de elementos de la clase */
		
		static void createEntity(std::string uniqueName); /**< Crea una entidad con un nombre unico*/

		template<typename Component, typename... Args>
		static void addComponent(std::string entityName, Args&& ...args) { /**< Agrega un componente a una entidad*/
			m_Registry.emplace_or_replace<Component>(m_entities[entityName], std::forward<Args>(args)...);

		}
		
		template<typename Component>
		static Component& getComponent(std::string entityName) { /**< Recupera un componente de una entidad*/
			return m_Registry.get<Component>(m_entities[entityName]);
		}
		
		template<typename Component>
		static auto getEntityView() { /**< Genera una vista iterable de entidades que contienen cierto componente*/
			return m_Registry.view<Component>();
		}

		
		static void initEntities(); /**< Inicializa las entidades*/

		static void updateEntities(float timeStep); /**< Actualiza las entidades*/

		template<typename Component>
		static void deleteComponent(std::string entityName) { /**< Elimina un componente de una entidad*/
			entt::entity entity = m_entities[entityName];
			m_Registry.remove<Component>(entity);
		}

		static void deleteEntity(std::string entityName); /**< Elimina una entidad*/

		static std::string getEntityName(entt::entity entity); /**< Retorna el nombre asociado a la entidad*/
	};




}

#endif