#pragma once
#ifndef EVENTREGISTRYCOMPONENT_HPP
#define EVENTREGISTRYCOMPONENT_HPP
#include "../Utils/LibUtils.hpp"

namespace cave {

	struct EventRegistryComponent {
		std::vector<std::string> m_events;

		bool containsEvent(std::string event);

		void addEvent(std::string event);

		void removeEvent(std::string event);

		EventRegistryComponent();
	};



}

#endif