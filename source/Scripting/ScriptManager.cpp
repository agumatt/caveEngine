#include "ScriptManager.hpp"


namespace cave {
	lua_State* L = luaL_newstate();

	bool CheckLua(lua_State* L, int r) {
		if (r != LUA_OK) {
			std::string errormsg = lua_tostring(L, -1);
			std::cout << errormsg << std::endl;
			return false;
		};
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
				return *defaultValue;
			}			
		}
		float result = (float)lua_tonumber(L, -1);
		lua_pop(L, -1);
		return result;
	}

	/* assume that table is on the stack top */
	std::string getFieldString(const char* key, std::string* defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_isstring(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return *defaultValue;
			}
		}			
		std::string result = std::string(lua_tostring(L, -1));
		lua_pop(L, -1);
		return result;
	}

	/* assume that table is on the stack top */
	bool getFieldBoolean(const char* key, bool* defaultValue = nullptr) {
		lua_getfield(L, -1, key);
		if (!lua_isboolean(L,-1))
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				return *defaultValue;
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
		caveVec3f result = caveVec3f(lua_tonumber(L, -1), lua_tonumber(L, -2), lua_tonumber(L, -3));
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
		caveColour result = caveColour(lua_tonumber(L, -1), lua_tonumber(L, -2),  lua_tonumber(L, -3), lua_tonumber(L, -4));
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
		caveQuat result = caveQuat(lua_tonumber(L, -1), lua_tonumber(L, -2), lua_tonumber(L, -3), lua_tonumber(L, -4));
		lua_pop(L, -1); // remove x
		lua_pop(L, -1); // remove y
		lua_pop(L, -1); // remove z
		lua_pop(L, -1); // remove w
		lua_pop(L, -1); // remove quaternion
		return result;

	}


	void ScriptManager::processInitEntitiesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/InitEntitiesScript.lua"))) {
			lua_getglobal(L, "Entities");
			bool loadedAllEntities = false;
			int entityIndex = 0;
			if (lua_istable(L, -1)) {
				while (!loadedAllEntities) {
					lua_pushnumber(L, entityIndex);
					lua_gettable(L, -2);
					if (lua_istable(L, -1)) {
						entityIndex += 1;
						// create entity
						std::string entityName = getFieldString("name");
						EntityComponentManager::createEntity(entityName);
						// add components
						// SkeletalMeshComponent
						lua_getfield(L, -1, "SkeletalMeshComponent");
						if (lua_istable(L, -1)) {
							std::string defaultParentNodeName = "RootSceneNode";
							std::string meshFileName = getFieldString("meshFileName");
							std::string meshNodeName = getFieldString("nodeName");
							std::string meshParentNodeName = getFieldString("parentNodeName", &defaultParentNodeName);
							EntityComponentManager::addComponent<SkeletalMeshComponent>(entityName, meshFileName, meshNodeName,meshParentNodeName);
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
							bool defaultSetLoop = true;
							float audioVolume = getFieldNumber("volume");
							float audioPitch = getFieldNumber("pitch");
							float audioRadius = getFieldNumber("radius");
							bool audioSetLoop = getFieldBoolean("setLoop", &defaultSetLoop);
							caveVec3f audioPos = getFieldVector("position", &caveVec3f(0.0f, 0.0f, 0.0f));
							EntityComponentManager::addComponent<AudioSourceComponent>(entityName,audioVolume, audioPitch, audioRadius, audioSetLoop, audioPos);
						}
						lua_pop(L, -1); // remove component from stack

						// CameraComponent
						lua_getfield(L, -1, "CameraComponent");
						if (lua_istable(L, -1)) {
							float defaultNearClipDistance = 1.0f;
							float defaultFarClipDistance = 1.0f;
							caveVec3f camPosition = getFieldVector("position", &caveVec3f(0.0f, 0.0f, 0.0f));
							caveVec3f camLookAt = getFieldVector("lookAt");
							float camNearClipDistance = getFieldNumber("nearClipDistance", &defaultNearClipDistance);
							float camFarClipDistance = getFieldNumber("farClipDistance", &defaultFarClipDistance);
							EntityComponentManager::addComponent<CameraComponent>(entityName, camPosition, camLookAt, camNearClipDistance, camFarClipDistance);
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

	void ScriptManager::processConfigEntitiesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/ConfigEntitiesScript.lua"))) {
			lua_getglobal(L, "Entities");
			bool configuredAllEntities = false;
			int entityIndex = 0;
			if (lua_istable(L, -1)) {
				while (!configuredAllEntities) {
					lua_pushnumber(L, entityIndex);
					lua_gettable(L, -2);
					if (lua_istable(L, -1)) {
						entityIndex += 1;
						std::string entityName = getFieldString("name");
						// configure components
						// SkeletalMeshComponent
						lua_getfield(L, -1, "SkeletalMeshComponent");
						if (lua_istable(L, -1)) {
							SkeletalMeshComponent& mesh = EntityComponentManager::getComponent<SkeletalMeshComponent>(entityName);
							// translation
							caveVec3f meshTranslation = getFieldVector("translation", &caveVec3f(0.0f, 0.0f, 0.0f));
							mesh.setTranslation(meshTranslation);
							// rotation
							caveQuat meshRotation = getFieldQuaternion("rotation", &caveQuat(0.0f, 0.0f, 0.0f, 1.0f));
							mesh.setRotation(meshRotation);
							// scaling
							caveVec3f meshScaling = getFieldVector("scaling", &caveVec3f(1.0f, 1.0f, 1.0f));
							mesh.setScaling(meshScaling);
						}
						lua_pop(L, -1); // remove component from stack
						// TextComponent
						lua_getfield(L, -1, "TextComponent");
						if (lua_istable(L, -1)) {
							TextComponent& text = EntityComponentManager::getComponent<TextComponent>(entityName);
							bool loadedAllTextElements = false;
							int textElementIndex = 0;
							while (!loadedAllTextElements) {
								lua_pushnumber(L, textElementIndex);
								lua_gettable(L, -2);
								if (lua_istable(L, -1)) {
									textElementIndex += 1;
									std::string textElementName = getFieldString("name");
									float textElPositionLeft = getFieldNumber("positionLeft");
									float textElPositionTop = getFieldNumber("positionTop");
									float textElWidth = getFieldNumber("width");
									float textElHeight = getFieldNumber("height");
									float textElFontSize = getFieldNumber("fontSize");
									std::string textElFontName = getFieldString("fontName");
									caveColour textElTextColour = getFieldColour("textColour");
									std::string caption = getFieldString("caption");
									text.addTextElement(textElementName, textElPositionLeft, textElPositionTop, textElWidth, textElHeight);
									text.configureTextElement(textElementName, textElFontSize, textElFontName, textElTextColour);
									text.displayText(textElementName, caption);
								}
								lua_pop(L, -1); // remove textElement from stack
							}
						}
						lua_pop(L, -1); // remove component from stack

						// AudioSourceComponent
						lua_getfield(L, -1, "AudioSourceComponent");
						if (lua_istable(L, -1)) {
							AudioSourceComponent& audio = EntityComponentManager::getComponent<AudioSourceComponent>(entityName);
							std::string audioClipName = getFieldString("audioClipName");
							audio.play(audioClipName);
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

	void ScriptManager::processLoadResourcesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/LoadResourcesScript.lua"))) {
			lua_getglobal(L, "Audio");
			bool loadedAllAudioEntries = false;
			int audioIndex = 0;
			if (lua_istable(L, -1)) {
				while (!loadedAllAudioEntries) {
					lua_pushnumber(L, audioIndex);
					lua_gettable(L, -2);
					if (lua_istable(L, -1)) {
						AudioManager::loadSound(getFieldString("audioFilePath"), getFieldString("uniqueName"));
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
					lua_pushnumber(L, resourcesFoldersIndex);
					lua_gettable(L, -2);
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
					lua_pushnumber(L, fontsIndex);
					lua_gettable(L, -2);
					if (lua_istable(L, -1)) {
						RenderingManager::loadFont(getFieldString("uniqueName"), getFieldString("fontFileName"));
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

	void ScriptManager::processEventsScript() {
		lua_settop(L, 0);
	}

	void ScriptManager::StartUp() {
		processLoadResourcesScript();
		processInitEntitiesScript();
		EntityComponentManager::initEntities();
		processConfigEntitiesScript();
		processEventsScript();
	}
}