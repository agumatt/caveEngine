#pragma once
#ifndef EVENTUTILSSCRIPTS_HPP
#define EVENTUTILSSCRIPTS_HPP
#include "../EntityComponent/EntityComponentManager.hpp"
#include "../Utils/LibUtils.hpp"
#include "../Events/EventUtils.hpp"
#include <lua.hpp>

namespace cave {

	struct EventUtilsScripts {

		static int lua_entitiesInSight(lua_State* L)
		{
			std::vector<std::string> entitiesInSight = EventUtils::entitiesInSight();
			lua_newtable(L);
			for (int index = 0; index < entitiesInSight.size(); index++) {
				const char* entityName = entitiesInSight[index].c_str();
				lua_pushnumber(L, index);
				lua_pushstring(L, entityName);
				lua_settable(L, -3);
			}
			return 1; // Count of returned values
		}


		static int lua_entityReachedPlayer(lua_State* L)
		{
			const char* entityName = EventUtils::entityReachedPlayer().c_str();
			lua_newtable(L);
			if (entityName != "") {
				lua_pushnumber(L, 0);
				lua_pushstring(L, entityName);
				lua_settable(L, -3);
			}
			return 1; // Count of returned values
		}

		
		static int lua_getEntityNames(lua_State* L) {
			std::vector<std::string> entityNames = EventUtils::getEntityNames();
			lua_newtable(L);
			for (int index = 0; index < entityNames.size(); index++) {
				const char* entityName = entityNames[index].c_str();
				lua_pushnumber(L, index);
				lua_pushstring(L, entityName);
				lua_settable(L, -3);
			}
			return 1; // Count of returned values

		}

		static int lua_updateChasePlayer(lua_State* L) {
			std::string entityName = lua_tostring(L, -1); //trigger entityName argument
			EventUtils::updateChasePlayer(entityName);
			return 0;

		}

		static int lua_stopChasePlayer(lua_State* L) {
			std::string entityName = lua_tostring(L, -1); //trigger entityName argument
			EventUtils::stopChasePlayer(entityName);
			return 0;

		}

	};

	




}




#endif

