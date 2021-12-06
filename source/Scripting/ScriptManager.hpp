#pragma once
#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP
#include <lua.hpp>
#include "../Core/Log.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/LibUtils.hpp"
#include "../EntityComponent/EntityComponentManager.hpp"
namespace cave {

	class ScriptManager {
	public: 
		static void processEventsScript();
		static void processInitEntitiesScript();
		static void processLoadResourcesScript();
		static void processConfigEntitiesScript();
		static void StartUp();


	};



}

#endif