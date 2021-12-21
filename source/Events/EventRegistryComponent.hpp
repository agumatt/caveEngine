#pragma once
#ifndef EVENTREGISTRYCOMPONENT_HPP
#define EVENTREGISTRYCOMPONENT_HPP
#include "../Utils/LibUtils.hpp"

namespace cave {

	struct EventRegistryComponent {
		std::vector<std::string> m_events;/**< Vector con los eventos asociados al componente */

		bool containsEvent(std::string event); /**< Indica si el componente posee un evento */

		void addEvent(std::string event); /**< Agrega un evento al contenedor */

		void removeEvent(std::string event); /**< Elimina un evento del contenedor */

		EventRegistryComponent();
	};



}

#endif