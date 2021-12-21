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
		/**Chequea si hubo errores al utilizar lua.
		*/
		static bool CheckLua(lua_State* L, int r);
		/**Entrega un valor numerico extraido de una tabla de lua.
		*/
		static float getFieldNumber(const char* key, float* defaultValue = nullptr);
		/**Entrega un string extraido de una tabla de lua.
		*/
		static std::string getFieldString(const char* key, std::string* defaultValue = nullptr);
		/**Entrega un booleano extraido de una tabla de lua.
		*/
		static bool getFieldBoolean(const char* key, bool* defaultValue = nullptr);
		/**Entrega un vector (x,y,z) extraido de una tabla de lua.
		*/
		static caveVec3f getFieldVector(const char* key, caveVec3f* defaultValue = nullptr);
		/**Entrega un color (r,g,b,a) extraido de una tabla de lua.
		*/
		static caveColour getFieldColour(const char* key, caveColour* defaultValue = nullptr);
		/**Entrega un cuaternion (w,x,y,z) extraido de una tabla de lua.
		*/
		static caveQuat getFieldQuaternion(const char* key, caveQuat* defaultValue = nullptr);
		/**Procesa el script de eventos.
		*/
		static void processEventsScript();
		/**Procesa el script de inicializacion de entidades.
		*/
		static void processInitEntitiesScript();
		/**Procesa el script de carga de recursos.
		*/
		static void processLoadResourcesScript();
		/**Procesa el script de configuracion de entidades.
		*/
		static void processConfigEntitiesScript();
		/**Procesa los datos que hayan quedado pendientes luego de procesar todos los scripts.
		*/
		static void processQueuedData();
		static void StartUp();
		/**Guarda informacion de las animaciones que deben ser asociadas a las entidades segun lo indicado en el script de config. de entidades.
		*/
		static std::map<std::pair<std::string, std::string>, std::pair<bool, bool>> m_queuedAnimations; // (entity name, anim name), (enabled, isLooping)
	};



}

#endif