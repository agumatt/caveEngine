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


	};



}

