#pragma once
#ifndef EVENTUTILSSCRIPTS_HPP
#define EVENTUTILSSCRIPTS_HPP
#include "../EntityComponent/EntityComponentManager.hpp"
#include "../Utils/LibUtils.hpp"
#include "../Events/EventUtils.hpp"
#include <lua.hpp>

namespace cave {

	struct EventUtilsScripts {

		int lua_entitiesInSight(lua_State* L)
		{
			std::vector<std::string> entitiesInSight = EventUtils::entitiesInSight();
			lua_newtable(L);
			for (int index = 0; index < entitiesInSight.size(); index++) {
				char* entityName = entitiesInSight[i].c_str();
				lua_pushnumber(L, index);
				lua_pushstring(L, entityName);
				lua_settable(L, -3);
			}
			return 1; // Count of returned values
		}

		lua_register(L, "cpp_entitiesInSight", lua_entitiesInSight);


		int lua_entityReachedPlayer(lua_State* L)
		{
			std::string entityName = EventUtils::entityReachedPlayer();
			lua_newtable(L);
			if (entityName != "") {
				lua_pushnumber(L, 0);
				lua_pushstring(L, entityName);
				lua_settable(L, -3);
			}
			return 1; // Count of returned values
		}

		lua_register(L, "cpp_entityReachedPlayer", lua_entityReachedPlayer);


		int lua_getEntityNames(lua_State* L) {
			std::vector<std::string> entityNames = EventUtils::getEntityNames();
			lua_newtable(L);
			for (int index = 0; index < entityNames.size(); index++) {
				char* entityName = entityNames[i].c_str();
				lua_pushnumber(L, index);
				lua_pushstring(L, entityName);
				lua_settable(L, -3);
			}
			return 1; // Count of returned values

		}
		lua_register(L, "cpp_getEntityNames", lua_getEntityNames);


		int lua_updateChasePlayer(lua_State* L) {
			std::string entityName = lua_tostring(-1); //trigger entityName argument
			EventUtils::updateChasePlayer(entityName);
			return 0;

		}

		lua_register(L, "cpp_updateChasePlayer", lua_updateChasePlayer);

		int lua_stopChasePlayer(lua_State* L) {
			std::string entityName = lua_tostring(-1); //trigger entityName argument
			EventUtils::stopChasePlayer(entityName);
			return 0;

		}

		lua_register(L, "cpp_stopChasePlayer", lua_stopChasePlayer);

	};

	




}




#endif

