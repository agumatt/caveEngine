#pragma once
#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#include "../Utils/LibUtils.hpp"


namespace cave {

	class EventManager {
		/**Mapa que asocia los eventos con las entidades (por nombre)
		*		que los gatillaron
		*/
		static std::map<std::string, std::vector<std::string>> m_activeEvents;

		EventManager();
		static void handleActiveEvents();


	private:
		void handleScriptedEvent( std::string eventName);


	};


}

#endif