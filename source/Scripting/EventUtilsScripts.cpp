#include "EventUtilsScripts.hpp"
namespace cave {

	std::map<std::string, int> EventUtilsScripts::multiPurposeCounters = {};

	int EventUtilsScripts::lua_entitiesInSight(lua_State* L)
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


	int EventUtilsScripts::lua_entityReachedPlayer(lua_State* L)
	{
		std::string entityName = EventUtils::entityReachedPlayer();
		lua_newtable(L);
		if (entityName != "") {
			lua_pushnumber(L, 0);
			lua_pushstring(L, entityName.c_str());
			lua_settable(L, -3);
		}
		return 1; // Count of returned values
	}


	int EventUtilsScripts::lua_getEntityNames(lua_State* L) {
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

	int EventUtilsScripts::lua_updateChasePlayer(lua_State* L) {
		std::string entityName = lua_tostring(L, -1); //trigger entityName argument
		EventUtils::updateChasePlayer(entityName);
		return 0;

	}

	int EventUtilsScripts::lua_stopChasePlayer(lua_State* L) {
		std::string entityName = lua_tostring(L, -1); //trigger entityName argument
		EventUtils::stopChasePlayer(entityName);
		return 0;

	}

	int EventUtilsScripts::lua_getCounterValue(lua_State* L) {
		std::string key = lua_tostring(L, -1); //key argument
		int value = multiPurposeCounters[key];
		lua_pushnumber(L, value);
		return 1;
	}

	int EventUtilsScripts::lua_setCounterValue(lua_State* L) {
		int value = lua_tonumber(L, -1); //value argument
		std::string key = lua_tostring(L, -2); //key argument
		multiPurposeCounters[key] = value;
		return 0;
	}

	void EventUtilsScripts::StartUp(lua_State* L) {
		lua_register(L, "cpp_setCounterValue", lua_setCounterValue);
		lua_register(L, "cpp_getCounterValue", lua_getCounterValue);
		lua_register(L, "cpp_entitiesInSight", lua_entitiesInSight);
		lua_register(L, "cpp_entityReachedPlayer", lua_entityReachedPlayer);
		lua_register(L, "cpp_getEntityNames", lua_getEntityNames);
		lua_register(L, "cpp_updateChasePlayer", lua_updateChasePlayer);
		lua_register(L, "cpp_stopChasePlayer", lua_stopChasePlayer);
	}


}

