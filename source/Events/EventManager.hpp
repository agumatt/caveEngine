#pragma once
#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#include "../Utils/LibUtils.hpp"


namespace cave {

	class EventManager {

	public:
		/**Mapa con los nombres de los eventos activos y las entidades que los gatillaron
		*/
		static std::map<std::string, std::vector<std::string>> m_activeEvents;
		/**Tiempo minimo que debe transcurrir entre dos activaciones consecutivas de un mismo evento
		*/
		static std::map<std::string, float> m_eventTimeOuts;
		/**Tiempo transcurrido desde la llamada de cada evento
		*/
		static std::map<std::string, float> m_eventElapsedTime;
		/**Mapa con los nombres de los eventos y las funciones que retornan
		* la o las entidades gatillantes
		*/
		static std::map<std::string, std::vector<std::function<std::vector<std::string> ()>>> m_eventTriggers;
		/**Mapa con los nombres de los eventos y las funciones asociadas a cada uno
		*/
		static std::map<std::string, std::vector<std::function<void (std::string)>>> m_eventCallbacks;
		EventManager();
		static void processEvents(float deltaTime);

	private:
		/**Procesa los eventos gatillados.
		*/
		static void handleActiveEvents();
		/**Checkea si un evento ha sido gatillado para activarlo.
		*/
		static void checkForEventTriggers(float deltaTime);
		

	};


}

#endif