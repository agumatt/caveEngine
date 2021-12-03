#include <string>
#include <vector>

namespace cave {

	class EventManager {
		std::vector<std::string> m_activeEvents;

		EventManager();
		void handleActiveEvents();

	private:
		void handleEvent(void (*callback)() , std::string eventName);

		

	};


}