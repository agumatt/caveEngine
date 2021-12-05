#pragma once
#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP
#include <lua.hpp>
#include <string>
#include "../Core/Log.hpp"
#include <iostream>
#include "../Utils/Utils.hpp"
#include "../EntityComponent/EntityComponentManager.hpp"
namespace cave {

	class ScriptManager {

		static lua_State* L;
		static void processEventScript();
		static void processInitEntitiesScript();
		static void processLoadResourcesScript();
		static void processConfigEntitiesScript();
		static void StartUp();


	};



}

#endif