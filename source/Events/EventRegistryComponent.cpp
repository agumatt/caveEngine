#include "EventRegistryComponent.hpp"

namespace cave {


	EventRegistryComponent::EventRegistryComponent() {
		m_events = {};
	}
	EventRegistryComponent::containsEvent(std::string event) {
		if (std::find(m_events.begin(), m_events.end(), event) != m_events.end()) {
			return true;
		}
		return false;
	}
	EventRegistryComponent::addEvent(std::string event) {
		if (!containsEvent(event)) {
			m_events.push_back(event);
		}
	}

	EventRegistryComponent::removeEvent(std::string event) {
		if (containsEvent(event)) {
			std::remove(m_events.begin(), m_events.end(), event);
		}
	}



}