#include "ScriptManager.hpp"


namespace cave {
	lua_State* ScriptManager::L = luaL_newstate();

	bool CheckLua(lua_State* L, int r) {
		if (r != LUA_OK) {
			std::string errormsg = lua_tostring(L, -1);
			std::cout << errormsg << std::endl;
			return false
		}
		return true;
	}

	/* assume that table is on the stack top */
	float getFieldNumber(const char* key, float* defaultValue=nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_isnumber(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return defaultValue;
			}			
		}
		float result = (float)lua_tonumber(L, -1);
		lua_pop(L, -1);
		return result;
	}

	/* assume that table is on the stack top */
	std::string getFieldString(const char* key, std::string defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_isstring(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return defaultValue;
			}
		}			
		std::string result = std::string(lua_tostring(L, -1));
		lua_pop(L, -1);
		return result;
	}

	/* assume that table is on the stack top */
	std::string getFieldBoolean(const char* key, bool defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_isboolean(L,-1))
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return defaultValue;
			}
		bool result = (bool)lua_toboolean(L,-1);
		lua_pop(L, -1);
		return result;
	}
	caveVec3f getFieldVector(const char* key, caveVec3f* defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_istable(L, -1))
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return *defaultValue;
			}
		lua_getfield(L, -1, "z");
		lua_getfield(L, -1, "y");
		lua_getfield(L, -1, "x");
		if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3)) {
			std::cerr << "invalid parameter in entity creation" << std::endl;
		}				
		caveVec3f result = caveVec3f(x = lua_tonumber(L, -1), y = lua_tonumber(L, -2), z = lua_tonumber(L, -3));
		lua_pop(L, -1); // remove x
		lua_pop(L, -1); // remove y
		lua_pop(L, -1); // remove z
		lua_pop(L, -1); // remove vector
		return result;
	}

	caveColour getFieldColour(const char* key, caveColour* defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_istable(L, -1))
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return *defaultValue;
			}
		lua_getfield(L, -1, "alpha");
		lua_getfield(L, -1, "b");
		lua_getfield(L, -1, "g");
		lua_getfield(L, -1, "r");
		if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3) || !lua_isnumber(L, -4)) {
			std::cerr << "invalid parameter in entity creation" << std::endl;
		}
		caveColour result = caveColour(r = lua_tonumber(L, -1), g = lua_tonumber(L, -2), b = lua_tonumber(L, -3), alpha = lua_tonumber(L, -4));
		lua_pop(L, -1); // remove r
		lua_pop(L, -1); // remove g
		lua_pop(L, -1); // remove b
		lua_pop(L, -1); // remove alpha
		lua_pop(L, -1); // remove colour
		return result;
	}

	caveQuat getFieldQuaternion(const char* key, caveQuat* defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_istable(L, -1))
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return *defaultValue;
			}
		lua_getfield(L, -1, "w");
		lua_getfield(L, -1, "z");
		lua_getfield(L, -1, "y");
		lua_getfield(L, -1, "x");
		if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3) || !lua_isnumber(L, -4)) {
			std::cerr << "invalid parameter in entity creation" << std::endl;
		}
		caveQuat result = caveQuat(x = lua_tonumber(L, -1), y = lua_tonumber(L, -2), z = lua_tonumber(L, -3), w = lua_tonumber(L, -4));
		lua_pop(L, -1); // remove x
		lua_pop(L, -1); // remove y
		lua_pop(L, -1); // remove z
		lua_pop(L, -1); // remove w
		lua_pop(L, -1); // remove quaternion
		return result;

	}


	ScriptManager::processInitEntitiesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/InitEntitiesScript.lua"))) {
			lua_getglobal(L, "Entities");
			bool loadedAllEntities = false;
			int entityIndex = 0;
			if (lua_istable(L, -1)) {
				while (!loadedAllEntities) {
					lua_getfield(L, -1, entityIndex);
					if (lua_istable(L, -1)) {
						entityIndex += 1;
						// create entity
						std::string entityName = getFieldString("name");
						EntityComponentManager::createEntity(entityName);
						// add components
						// SkeletalMeshComponent
						lua_getfield(L, -1, "SkeletalMeshComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<SkeletalMeshComponent>(entityName, getFieldString("meshFileName"), getFieldString("nodeName"),
								getFieldString("parentNodeName", "RootSceneNode"));
						}
						lua_pop(L, -1); // remove component from stack
						// TextComponent
						lua_getfield(L, -1, "TextComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<TextComponent>(entityName, getFieldNumber("positionLeft"), getFieldNumber("positionTop"),
								getFieldNumber("width"), getFieldNumber("height"));
						}
						lua_pop(L, -1); // remove component from stack

						// AudioSourceComponent
						lua_getfield(L, -1, "AudioSourceComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<AudioSourceComponent>(entityName, getFieldNumber("volume"), getFieldNumber("pitch"), getFieldNumber("radius"),
								getFieldNumber("setLoop", true), getFieldNumber("position", &caveVec3f(0.0f, 0.0f, 0.0f)));
						}
						lua_pop(L, -1); // remove component from stack

						// CameraComponent
						lua_getfield(L, -1, "CameraComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<CameraComponent>(entityName, getFieldVector("position", &caveVec3f(0.0f, 0.0f, 0.0f)),
								getFieldVector("lookAt"), getFieldNumber("nearClipDistance", 1.0f), getFieldNumber("farClipDistance", 1000.0f));
						}
						lua_pop(L, -1); // remove component from stack
						// EventRegistryComponent
						lua_getfield(L, -1, "EventRegistryComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<EventRegistryComponent>(entityName);
						}
						lua_pop(L, -1); // remove component from stack
					}
					else {
						loadedAllEntities = true;
					}
					lua_pop(L, -1); // remove entity from stack
				}
			}

		}
	}

	ScriptManager::processConfigEntitiesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/ConfigEntitiesScript.lua"))) {
			lua_getglobal(L, "Entities");
			bool configuredAllEntities = false;
			int entityIndex = 0;
			if (lua_istable(L, -1)) {
				while (!configuredAllEntities) {
					lua_getfield(L, -1, entityIndex);
					if (lua_istable(L, -1)) {
						entityIndex += 1;
						std::string entityName = getFieldString("name");
						// configure components
						// SkeletalMeshComponent
						lua_getfield(L, -1, "SkeletalMeshComponent");
						if (lua_istable(L, -1)) {
							SkeletalMeshComponent& mesh = EntityComponentManager::getComponent<SkeletalMeshComponent>(entityName);
							// translation
							mesh.setTranslation(getFieldVector("translation", &caveVec3f(0.0f, 0.0f, 0.0f)));
							// rotation
							mesh.setRotation(getFieldQuaternion("rotation", &caveQuat(0.0f, 0.0f, 0.0f, 1.0f)));
							// scaling
							mesh.setScaling(getFieldVector("scaling", &caveVec3f(1.0f, 1.0f, 1.0f)));
						}
						lua_pop(L, -1); // remove component from stack
						// TextComponent
						lua_getfield(L, -1, "TextComponent");
						if (lua_istable(L, -1)) {
							TextComponent& text = EntityComponentManager::getComponent<TextComponent>(entityName);
							bool loadedAllTextElements = false;
							int textElementIndex = 0;
							while (!loadedAllTextElements) {
								lua_getfield(L, -1, textElementIndex);
								if (lua_istable(L, -1)) {
									textElementIndex += 1;
									std::string textElementName = getFieldString("name");
									text.addTextElement(textElementName, getFieldNumber("positionLeft"), getFieldNumber("positionTop"),
										getFieldNumber("width"), getFieldNumber("height"));
									text.configureTextElement(textElementName, getFieldNumber("fontSize"), getFieldString("fontName"), getFieldColour("textColour"));
									text.displayText(textElementName, getFieldString("caption"));
								}
								lua_pop(L, -1); // remove textElement from stack
							}
						}
						lua_pop(L, -1); // remove component from stack

						// AudioSourceComponent
						lua_getfield(L, -1, "AudioSourceComponent");
						if (lua_istable(L, -1)) {
							AudioSourceComponent& audio = EntityComponentManager::getComponent<AudioSourceComponent>(entityName);
							audio.play(getFieldString("audioClipName"));
						}
						lua_pop(L, -1); // remove component from stack

					}
					else {
						configuredAllEntities = true;
					}
					lua_pop(L, -1); // remove entity from stack
				}
			}

		}



	}

	ScriptManager::processLoadResourcesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/LoadResourcesScript.lua"))) {
			lua_getglobal(L, "Audio");
			bool loadedAllAudioEntries = false;
			int audioIndex = 0;
			if (lua_istable(L, -1)) {
				while (!loadedAllAudioEntries) {
					lua_getfield(L, -1, audioIndex);
					if (lua_istable(L, -1)) {
						AudioManager::loadSound(audioFilePath=getFieldString("audioFilePath"), uniqueName=getFieldString("uniqueName"));
					}
					else {
						loadedAllAudioEntries = true;
					}
					audioIndex += 1;
					lua_pop(L, -1); // remove audio entry from stack
				}
			}
			lua_pop(L, -1); // remove audio table from stack
			lua_getglobal(L, "ResourcesFolders");
			bool loadedAllResourcesFoldersEntries = false;
			int resourcesFoldersIndex = 0;
			if (lua_istable(L, -1)) {
				while (!loadedAllResourcesFoldersEntries) {
					lua_getfield(L, -1, resourcesFoldersIndex);
					if (lua_istable(L, -1)) {
						RenderingManager::loadResourcesFolder(getFieldString("folderPath"));
					}
					else {
						loadedAllResourcesFoldersEntries = true;
					}
					resourcesFoldersIndex += 1;
					lua_pop(L, -1); // remove resourceFolder entry from stack
				}
			}
			lua_pop(L, -1); // remove resourcesFolders table from stack
			lua_getglobal(L, "Fonts");
			bool loadedAllFontsEntries = false;
			int fontsIndex = 0;
			if (lua_istable(L, -1)) {
				while (!loadedAllFontsEntries) {
					lua_getfield(L, -1, fontsIndex);
					if (lua_istable(L, -1)) {
						RenderingManager::loadFont(fontName = getFieldString("uniqueName"), fontFileName = getFieldString("fontFileName"));
					}
					else {
						loadedAllFontsEntries = true;
					}
					fontsIndex += 1;
					lua_pop(L, -1); // remove font entry from stack
				}
			}
			lua_pop(L, -1); // remove fonts table from stack
		}
	}

	ScriptManager::processEventsScript() {
		lua_settop(L, 0);
	}

	ScriptManager::StartUp() {
		processLoadResourcesScript();
		processInitEntitiesScript();
		EntityComponentManager::initEntities();
		processConfigEntitiesScript();
		processEventsScript();
	}
}