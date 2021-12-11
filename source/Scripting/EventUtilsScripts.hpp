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
		static std::map<std::string, int> multiPurposeCounters;

		static int lua_entitiesInSight(lua_State* L);

		static int lua_entityReachedPlayer(lua_State* L);
		
		static int lua_getEntityNames(lua_State* L);

		static int lua_updateChasePlayer(lua_State* L);

		static int lua_stopChasePlayer(lua_State* L);

		static int lua_getCounterValue(lua_State* L);

		static int lua_setCounterValue(lua_State* L);
		
		static void StartUp(lua_State* L);
	};

}




#endif

