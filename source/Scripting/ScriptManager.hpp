#pragma once
#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP
#include "../Utils/Utils.hpp"
#include "../Utils/LibUtils.hpp"
#include "../EntityComponent/EntityComponentManager.hpp"
#include "../Events/EventManager.hpp"
#include "EventUtilsScripts.hpp"
namespace cave {

	class ScriptManager {
	public: 
		static lua_State* L;
		static bool CheckLua(lua_State* L, int r);
		static float getFieldNumber(const char* key, float* defaultValue = nullptr);
		static std::string getFieldString(const char* key, std::string* defaultValue = nullptr);
		static bool getFieldBoolean(const char* key, bool* defaultValue = nullptr);
		static caveVec3f getFieldVector(const char* key, caveVec3f* defaultValue = nullptr);
		static caveColour getFieldColour(const char* key, caveColour* defaultValue = nullptr);
		static caveQuat getFieldQuaternion(const char* key, caveQuat* defaultValue = nullptr);
		static void processEventsScript();
		static void processInitEntitiesScript();
		static void processLoadResourcesScript();
		static void processConfigEntitiesScript();
		static void processQueuedData();
		static void StartUp();
		static std::map<std::pair<std::string, std::string>, std::pair<bool, bool>> m_queuedAnimations; // (entity name, anim name), (enabled, isLooping)
	};



}

#endif