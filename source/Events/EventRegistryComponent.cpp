#include "EventRegistryComponent.hpp"

namespace cave {


	EventRegistryComponent::EventRegistryComponent() {
		m_events = {};
	}
	bool EventRegistryComponent::containsEvent(std::string event) {
		if (std::find(m_events.begin(), m_events.end(), event) != m_events.end()) {
			return true;
		}
		return false;
	}
	void EventRegistryComponent::addEvent(std::string event) {
		if (!containsEvent(event)) {
			m_events.push_back(event);
		}
	}

	void EventRegistryComponent::removeEvent(std::string event) {
		if (containsEvent(event)) {
			std::remove(m_events.begin(), m_events.end(), event);
		}
	}



}