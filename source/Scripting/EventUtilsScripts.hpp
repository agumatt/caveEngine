#pragma once
#ifndef EVENTUTILSSCRIPTS_HPP
#define EVENTUTILSSCRIPTS_HPP
#include "../Utils/LibUtils.hpp"
#include "../Events/EventUtils.hpp"
#include <lua.hpp>

namespace cave {

	class EventUtilsScripts {
	public:
		EventUtilsScripts() = default;
		/**Contadores para ser usados desde un script lua.
		*/
		static std::map<std::string, int> multiPurposeCounters;
		/**Devuelve un vector con las entidades que poseen un skeletalMeshComponent a la vista de la camara.
		* Para ser usado en lua.
		*/
		static int lua_entitiesInSight(lua_State* L);
		/**Chequea si una entidad que poseen un skeletalMeshComponent tocó al jugador y devuelve su nombre.
		* Para ser usado en lua.
		*/
		static int lua_entityReachedPlayer(lua_State* L);
		/**Entrega los nombres de todas las entidades.
		* Para ser usado en lua.
		*/
		static int lua_getEntityNames(lua_State* L);
		/**Actualiza el estado de persecucion al jugador de una entidad.
		* Para ser usado en lua.
		*/
		static int lua_updateChasePlayer(lua_State* L);
		/**Detiene el estado de persecucion al jugador de una entidad.
		* Para ser usado en lua.
		*/
		static int lua_stopChasePlayer(lua_State* L);
		/*Devuelve el valor de un contador.
		*/
		static int lua_getCounterValue(lua_State* L);
		/**Setea el valor de un contador.
		*/
		static int lua_setCounterValue(lua_State* L);
		
		static void StartUp(lua_State* L);
	};

}




#endif

