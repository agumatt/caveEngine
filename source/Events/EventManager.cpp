#include "EventManager.hpp"

namespace cave {
	std::map<std::string, std::vector<std::string>> EventManager::m_activeEvents = {};
	std::map<std::string, float> EventManager::m_eventTimeOuts = {};
	std::map<std::string, std::vector<std::function<std::vector<std::string>()>>> EventManager::m_eventTriggers = {};
	std::map<std::string, std::vector<std::function<void(std::string)>>> EventManager::m_eventCallbacks = {};
	std::map<std::string, float> EventManager::m_eventElapsedTime = {};
	
	EventManager::EventManager() {
	}

	void EventManager::handleActiveEvents() {
		for (auto& pair : m_activeEvents) {
			std::string eventName = pair.first;
			auto triggerEntities = pair.second;
			auto callbacks = m_eventCallbacks[eventName];
			for (auto& entityName : triggerEntities) {
				for (auto& callback : callbacks) {
					callback(entityName);
				}
			}
		}
		m_activeEvents = {};
	}

	void EventManager::checkForEventTriggers(float deltaTime) {
		for (auto& pair:m_eventTriggers) {
			std::string eventName = pair.first;
			auto triggers = pair.second;
			m_eventElapsedTime[eventName] += deltaTime;
			for (auto& trigger : triggers) {
				if (m_eventElapsedTime[eventName]>=m_eventTimeOuts[eventName]) {
					auto triggerEntities = trigger();
					std::vector<std::string> triggerEntity = {};
					if (triggerEntities.size() > 0) {
						triggerEntity.push_back(triggerEntities[0]); // escogemos solo una entidad como gatillante
					}
					if (EventManager::m_activeEvents.find(eventName) == EventManager::m_activeEvents.end()) {
						EventManager::m_activeEvents[eventName] = triggerEntity;
					}
					else {
						auto vec = EventManager::m_activeEvents[eventName];
						for (auto& entity : triggerEntity) {
							if (std::find(vec.begin(), vec.end(), eventName) == vec.end()) {
								vec.push_back(entity);
							}
						}
					}
					m_eventElapsedTime[eventName] = 0.0f;
				}
				
			}
		}
	}

	void EventManager::processEvents(float deltaTime) {
		checkForEventTriggers(deltaTime);
		handleActiveEvents();
	}

}