#include "ScriptManager.hpp"

namespace cave {


	lua_State* ScriptManager::L = luaL_newstate();
	

	bool ScriptManager::CheckLua(lua_State* L, int r) {
		if (r != LUA_OK) {
			std::string errormsg = lua_tostring(L, -1);
			std::cout << errormsg << std::endl;
			return false;
		};
		return true;
	}

	/* assume that table is on the stack top */
	float ScriptManager::getFieldNumber(const char* key, float* defaultValue) {
		lua_getfield(L, -1, key);
		if (!lua_isnumber(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				lua_pop(L, 1);
				return *defaultValue;
			}			
		}
		float result = (float)lua_tonumber(L, -1);
		lua_pop(L, 1);
		return result;
	}

	/* assume that table is on the stack top */
	std::string ScriptManager::getFieldString(const char* key, std::string* defaultValue) {
		lua_getfield(L, -1, key);
		if (!lua_isstring(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				lua_pop(L, 1);
				return *defaultValue;
			}
		}
		std::string result = std::string(lua_tostring(L, -1));
		lua_pop(L, 1);
		return result;
	}

	/* assume that table is on the stack top */
	bool ScriptManager::getFieldBoolean(const char* key, bool* defaultValue) {
		lua_getfield(L, -1, key);
		if (!lua_isboolean(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				lua_pop(L, 1);
				return *defaultValue;
			}
		}
		bool result = (bool)lua_toboolean(L,-1);
		lua_pop(L, 1);
		return result;
	}
	caveVec3f ScriptManager::getFieldVector(const char* key, caveVec3f* defaultValue) {
		lua_getfield(L, -1, key);
		if (!lua_istable(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				lua_pop(L, 1);
				return *defaultValue;
			}
		}
		lua_getfield(L, -1, "z");
		lua_getfield(L, -2, "y");
		lua_getfield(L, -3, "x");
		if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3)) {
			std::cerr << "invalid parameter in entity creation" << std::endl;
		}		
		caveVec3f result = caveVec3f(lua_tonumber(L, -1), lua_tonumber(L, -2), lua_tonumber(L, -3));
		lua_pop(L, 1); // remove x
		lua_pop(L, 1); // remove y
		lua_pop(L, 1); // remove z
		lua_pop(L, 1); // remove vector
		return result;
	}

	caveColour ScriptManager::getFieldColour(const char* key, caveColour* defaultValue) {
		lua_getfield(L, -1, key);
		if (!lua_istable(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				lua_pop(L, 1);
				return *defaultValue;
			}
		}
		lua_getfield(L, -1, "alpha");
		lua_getfield(L, -2, "b");
		lua_getfield(L, -3, "g");
		lua_getfield(L, -4, "r");
		if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3) || !lua_isnumber(L, -4)) {
			std::cerr << "invalid parameter in entity creation" << std::endl;
		}
		caveColour result = caveColour(lua_tonumber(L, -1), lua_tonumber(L, -2),  lua_tonumber(L, -3), lua_tonumber(L, -4));
		lua_pop(L, 1); // remove r
		lua_pop(L, 1); // remove g
		lua_pop(L, 1); // remove b
		lua_pop(L, 1); // remove alpha
		lua_pop(L, 1); // remove colour
		return result;
	}

	caveQuat ScriptManager::getFieldQuaternion(const char* key, caveQuat* defaultValue) {
		lua_getfield(L, -1, key);
		if (!lua_istable(L, -1)) {
			if (defaultValue == nullptr) {
				std::cerr << "invalid parameter in entity creation" << std::endl;
			}
			else {
				lua_pop(L, 1);
				return *defaultValue;
			}
		}
		lua_getfield(L, -1, "w");
		lua_getfield(L, -2, "z");
		lua_getfield(L, -3, "y");
		lua_getfield(L, -4, "x");
		if (!lua_isnumber(L, -1) || !lua_isnumber(L, -2) || !lua_isnumber(L, -3) || !lua_isnumber(L, -4)) {
			std::cerr << "invalid parameter in entity creation" << std::endl;
		}
		caveQuat result = caveQuat(lua_tonumber(L, -1), lua_tonumber(L, -2), lua_tonumber(L, -3), lua_tonumber(L, -4));
		lua_pop(L, 1); // remove x
		lua_pop(L, 1); // remove y
		lua_pop(L, 1); // remove z
		lua_pop(L, 1); // remove w
		lua_pop(L, 1); // remove quaternion
		return result;

	}


	void ScriptManager::processLoadResourcesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/LoadResourcesScript.lua"))) {
			lua_getglobal(L, "ResourcesFolders");
			bool loadedAllResourcesFoldersEntries = false;
			int resourcesFoldersIndex = 1;
			if (lua_istable(L, -1)) {
				while (!loadedAllResourcesFoldersEntries) {
					lua_geti(L, -1, resourcesFoldersIndex);
					if (lua_istable(L, -1)) {
						RenderingManager::loadResourcesFolder(getFieldString("folderPath"));
					}
					else {
						loadedAllResourcesFoldersEntries = true;
					}
					resourcesFoldersIndex += 1;
					lua_pop(L, 1); // remove resourceFolder entry from stack
				}
			}
			lua_pop(L, 1); // remove resourcesFolders table from stack
			lua_getglobal(L, "Audio");
			bool loadedAllAudioEntries = false;
			int audioIndex = 1;
			if (lua_istable(L, -1)) {
				while (!loadedAllAudioEntries) {
					lua_geti(L, -1, audioIndex);
					if (lua_istable(L, -1)) {
						AudioManager::loadSound(getFieldString("audioFilePath"), getFieldString("uniqueName"));
					}
					else {
						loadedAllAudioEntries = true;
					}
					audioIndex += 1;
					lua_pop(L, 1); // remove audio entry from stack
				}
			}
			lua_pop(L, 1); // remove audio table from stack
			lua_getglobal(L, "Fonts");
			bool loadedAllFontsEntries = false;
			int fontsIndex = 1;
			if (lua_istable(L, -1)) {
				while (!loadedAllFontsEntries) {
					lua_geti(L, -1, fontsIndex);
					if (lua_istable(L, -1)) {
						RenderingManager::loadFont(getFieldString("uniqueName"), getFieldString("fontFileName"));
					}
					else {
						loadedAllFontsEntries = true;
					}
					fontsIndex += 1;
					lua_pop(L, 1); // remove font entry from stack
				}
			}
			lua_pop(L, 1); // remove fonts table from stack
		}
	}

	void ScriptManager::processInitEntitiesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/InitEntitiesScript.lua"))) {
			bool addedCameraComponent = false;
			lua_getglobal(L, "Entities");
			bool loadedAllEntities = false;
			int entityIndex = 1;
			if (lua_istable(L, -1)) {
				while (!loadedAllEntities) {
					lua_geti(L, -1, entityIndex);
					if (lua_istable(L, -1)) {
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
							//auto skeletalMeshComponent = EntityComponentManager::getComponent<SkeletalMeshComponent>(entityName);
							//std::vector<Model> models = { skeletalMeshComponent.m_model };
							//RenderingManager::addModelsToScene(models);
							//skeletalMeshComponent.m_initialized = true;
						}
						lua_pop(L, 1); // remove component from stack
						// TextComponent
						lua_getfield(L, -1, "TextComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<TextComponent>(entityName, getFieldNumber("positionLeft"), getFieldNumber("positionTop"),
								getFieldNumber("width"), getFieldNumber("height"));
						}
						lua_pop(L, 1); // remove component from stack

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
						lua_pop(L, 1); // remove component from stack

						// CameraComponent
						lua_getfield(L, -1, "CameraComponent");
						if (lua_istable(L, -1)) {
							if (!addedCameraComponent) {
								float defaultNearClipDistance = 1.0f;
								float defaultFarClipDistance = 10000.0f;
								caveVec3f camPosition = getFieldVector("position", &caveVec3f(0.0f, 0.0f, 0.0f));
								caveVec3f camLookAt = getFieldVector("lookAt");
								float camNearClipDistance = getFieldNumber("nearClipDistance", &defaultNearClipDistance);
								float camFarClipDistance = getFieldNumber("farClipDistance", &defaultFarClipDistance);
								EntityComponentManager::addComponent<CameraComponent>(entityName, camPosition, camLookAt, camNearClipDistance, camFarClipDistance);
							}
							else {
								std::cerr << "only one camera component is allowed!!" << std::endl;
							}
							

						}
						lua_pop(L, 1); // remove component from stack
						// EventRegistryComponent
						lua_getfield(L, -1, "EventRegistryComponent");
						if (lua_istable(L, -1)) {
							EntityComponentManager::addComponent<EventRegistryComponent>(entityName);
						}
						lua_pop(L, 1); // remove component from stack
					}
					else {
						loadedAllEntities = true;
					}
					lua_pop(L, 1); // remove entity from stack
					entityIndex += 1;
				}
			}

		}
	}

	void ScriptManager::processConfigEntitiesScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/ConfigEntitiesScript.lua"))) {
			lua_getglobal(L, "Entities");
			bool configuredAllEntities = false;
			int entityIndex = 1;
			if (lua_istable(L, -1)) {
				std::cout << "hola1" << std::endl;
				while (!configuredAllEntities) {
					lua_geti(L, -1, entityIndex);
					if (lua_istable(L, -1)) {
						std::cout << "hola2" << std::endl;
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
							//animations
							lua_getfield(L, -1, "animations");
							if (lua_istable(L, -1)) {
								lua_pushnil(L);  // first key
								while (lua_next(L, -2) != 0) {
									if (lua_istable(L, -1)) {
										std::string name = getFieldString("name");
										bool enabledDefault = true;
										bool isLoopingDefault = true;
										bool enabled = getFieldBoolean("enabled", &enabledDefault);
										bool isLooping = getFieldBoolean("isLooping", &isLoopingDefault);
										std::cout << name << std::endl;
										mesh.addAnimation(name, enabled, isLooping);						
									}									
									// removes 'value'; keeps 'key' for next iteration
									lua_pop(L, 1);
								}
							}
							lua_pop(L, 1); // remove animations table from stack
						}
						lua_pop(L, 1); // remove component from stack
						// TextComponent
						lua_getfield(L, -1, "TextComponent");
						if (lua_istable(L, -1)) {
							TextComponent& text = EntityComponentManager::getComponent<TextComponent>(entityName);
							bool loadedAllTextElements = false;
							int textElementIndex = 1;
							while (!loadedAllTextElements) {
								lua_geti(L, -1, textElementIndex);
								if (lua_istable(L, -1)) {
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
								else {
									loadedAllTextElements = true;
								}
								lua_pop(L, 1); // remove textElement from stack
								textElementIndex += 1;
							}
						}
						lua_pop(L, 1); // remove component from stack

						// AudioSourceComponent
						lua_getfield(L, -1, "AudioSourceComponent");
						if (lua_istable(L, -1)) {
							AudioSourceComponent& audio = EntityComponentManager::getComponent<AudioSourceComponent>(entityName);
							std::string audioClipName = getFieldString("audioClipName");
							audio.play(audioClipName);
						}
						lua_pop(L, 1); // remove component from stack

					}
					else {
						configuredAllEntities = true;
					}
					lua_pop(L, 1); // remove entity from stack
					entityIndex += 1;
				}
			}

		}

	}



	

	void ScriptManager::processEventsScript() {
		lua_settop(L, 0);
		if (CheckLua(L, luaL_dofile(L, "Scripts/EventsScript.lua"))) {
			lua_getglobal(L, "enableScriptedEvents");
			bool enableScriptedEvents = true;
			if (lua_isboolean(L, -1)) {
				enableScriptedEvents = lua_toboolean(L, -1);
			}
			lua_pop(L, 1);
			if (enableScriptedEvents) {
				lua_getglobal(L, "Events");
				if (lua_istable(L, -1)) {
					lua_pushnil(L);  // first key
					while (lua_next(L, -2) != 0) {
						if (lua_istable(L, -1)) {
							std::string eventName = getFieldString("name");
							float defaultTimeOut = 0.0f;
							float eventTimeOut = getFieldNumber("timeOut", &defaultTimeOut);
							EventManager::m_eventTimeOuts.emplace(std::make_pair(eventName, eventTimeOut));
							EventManager::m_eventElapsedTime.emplace(std::make_pair(eventName, eventTimeOut));
						}
						// removes 'value'; keeps 'key' for next iteration
						lua_pop(L, 1);
					}
				}
				lua_pop(L, 1); // remove table from stack
				lua_getglobal(L, "EventsPerEntity");
				if (lua_istable(L, -1)) {
					lua_pushnil(L);  // first key
					while (lua_next(L, -2) != 0)
					{
						// uses 'key' (at index -2) and 'value' (at index -1)
						std::string entityName = lua_tostring(L, -2);
						auto evRegComp = EntityComponentManager::getComponent<EventRegistryComponent>(entityName);
						// get events
						if (lua_istable(L, -1)) {
							lua_pushnil(L);  // first key
							while (lua_next(L, -2) != 0) {
								std::string eventToAdd = lua_tostring(L, -1);
								evRegComp.addEvent(eventToAdd);
								// removes 'value'; keeps 'key' for next iteration
								lua_pop(L, 1);
							}
						}
						// removes 'value'; keeps 'key' for next iteration
						lua_pop(L, 1);
					}
				}
				lua_pop(L, 1); // remove table from stack
				lua_getglobal(L, "EventTriggers");
				if (lua_istable(L, -1)) {
					lua_pushnil(L);  // first key
					while (lua_next(L, -2) != 0) // iterar sobre eventos
					{
						// uses 'key' (at index -2) and 'value' (at index -1)
						if (lua_istable(L, -1)) {
							std::string eventName = lua_tostring(L, -2);
							lua_pushnil(L);  // first key
							while (lua_next(L, -2) != 0) {  // iterar sobre triggers
								if (lua_isfunction(L, -1)) {
									int regInd = luaL_ref(L, LUA_REGISTRYINDEX);
									std::function<std::vector<std::string>()> trigger = [&regInd]() -> std::vector<std::string> {
										std::vector<std::string> triggerEntities = {};
										lua_rawgeti(L, LUA_REGISTRYINDEX, regInd);
										if (CheckLua(L, lua_pcall(L, 0, 1, 0))) {
											if (lua_istable(L, -1)) {
												lua_pushnil(L);  // first key
												while (lua_next(L, -2) != 0) {
													std::string triggerEntity = lua_tostring(L, -1);
													triggerEntities.push_back(triggerEntity);
													// removes 'value'; keeps 'key' for next iteration
													lua_pop(L, 1);
												}
											}
										}
										else {
											std::cerr << "Error al crear la funcion trigger" << std::endl;
										}
										return triggerEntities;
									};
									if (EventManager::m_eventTriggers.find(eventName) == EventManager::m_eventTriggers.end()) {
										EventManager::m_eventTriggers[eventName] = { trigger };
									}
									else {
										EventManager::m_eventTriggers[eventName].push_back(trigger);
									}
								}
								else {
									lua_pop(L, 1);
								}
							}
						}
						// removes 'value'; keeps 'key' for next iteration
						lua_pop(L, 1);
					}
				}
				lua_pop(L, 1); // remove table from stack

				lua_getglobal(L, "EventReactions");
				if (lua_istable(L, -1)) {
					lua_pushnil(L);  // first key
					while (lua_next(L, -2) != 0) // iterate over events
					{
						std::string eventName = lua_tostring(L, -2);
						std::vector<std::string> affectedEntities = {};
						// affected entities
						lua_getfield(L, -1, "targetEntitiesByName");
						if (lua_istable(L, -1)) {
							lua_pushnil(L);
							while (lua_next(L, -2) != 0) { // iterate over target entities
								affectedEntities.push_back(std::string(lua_tostring(L, -1)));
								// removes 'value'; keeps 'key' for next iteration
								lua_pop(L, 1);
							}
						}
						lua_pop(L, 1); // remove table from stack
						// affect trigger entity
						bool defaultAffectTriggerEntity = false;
						bool affectTriggerEntity = getFieldBoolean("affectTriggerEntity", &defaultAffectTriggerEntity);
						// callback
						lua_getfield(L, -1, "callback");
						if (lua_isfunction(L, -1)) {
							int regInd = luaL_ref(L, LUA_REGISTRYINDEX);
							std::function<void(std::string)> callback = [&regInd](std::string triggerEntity) {
								lua_rawgeti(L, LUA_REGISTRYINDEX, regInd);
								lua_pushstring(L, triggerEntity.c_str());
								if (CheckLua(L, lua_pcall(L, 1, 0, 0))) {
								}
								else {
									std::cerr << "Error al crear la funcion de callback" << std::endl;
								}

							};
							if (EventManager::m_eventCallbacks.find(eventName) == EventManager::m_eventCallbacks.end()) {
								EventManager::m_eventCallbacks[eventName] = { callback };
							}
							else {
								EventManager::m_eventCallbacks[eventName].push_back(callback);
							}
						}
						else {
							lua_pop(L, 1);
						}

						// modifiersByComponent
						lua_getfield(L, -1, "modifiersByComponent");
						if (lua_istable(L, -1)) {
							lua_pushnil(L);
							while (lua_next(L, -2) != 0) { // iterate over components;
								std::string component = lua_tostring(L, -2);
								if (component == "TextComponent") {
									if (lua_isfunction(L, -1)) {
										std::cout << "E" << std::endl;
										int regInd = luaL_ref(L, LUA_REGISTRYINDEX);
										std::function<void(std::string)> modifier = [&affectedEntities, &affectTriggerEntity, &regInd](std::string triggerEntity) {
											std::vector<std::string> entVec = std::vector(affectedEntities);
											if (std::find(entVec.begin(), entVec.end(), triggerEntity) == entVec.end()) {
												if (affectTriggerEntity) {
													entVec.push_back(triggerEntity);
												}
											}
											lua_rawgeti(L, LUA_REGISTRYINDEX, regInd);
											if (CheckLua(L, lua_pcall(L, 0, 1, 0))) {
												if (lua_istable(L, -1)) {
													lua_pushnil(L);  // first key
													while (lua_next(L, -2) != 0) { // iterate over text elements
														if (lua_istable(L, -1)) {
															for (auto entityName : entVec) {
																TextComponent& text = EntityComponentManager::getComponent<TextComponent>(entityName);
																std::string textElementName = getFieldString("name");
																float textElFontSize = getFieldNumber("fontSize");
																std::string textElFontName = getFieldString("fontName");
																caveColour textElTextColour = getFieldColour("textColour");
																std::string caption = getFieldString("caption");
																text.configureTextElement(textElementName, textElFontSize, textElFontName, textElTextColour);
																text.displayText(textElementName, caption);
															}

														}
														// removes 'value'; keeps 'key' for next iteration
														lua_pop(L, 1);
													}
												}
											}
											else {
												std::cerr << "Error al crear la funcion modificadora" << std::endl;
											}

										};
										if (EventManager::m_eventCallbacks.find(eventName) == EventManager::m_eventCallbacks.end()) {
											EventManager::m_eventCallbacks[eventName] = { modifier };
										}
										else {
											EventManager::m_eventCallbacks[eventName].push_back(modifier);
										}
									}
									else {
										lua_pop(L, 1);
									}
								}
								else if (component == "SkeletalMeshComponent") {}
								else if (component == "CameraComponent") {}
								else if (component == "AudioSourceComponent") {}
								else {
									lua_pop(L, 1);
								}
							}
						}
						lua_pop(L, 1); // remove modifiersByComponent table
						lua_pop(L, 1); // remove event table
					}
				}
				lua_pop(L, 1); // remove table from stack
			}			
			}

	}

	void ScriptManager::StartUp() {
		luaL_openlibs(L);
		EventUtilsScripts::StartUp(L);
		processLoadResourcesScript();
		processInitEntitiesScript();
		processConfigEntitiesScript();
		EntityComponentManager::initEntities();
		processEventsScript();
	}
}