#include "Input.hpp"
#include <OIS.h>
#include "../Core/Common.hpp"
#include "../Core/Log.hpp"
namespace cave
{
	Input::Input(Ogre::RenderWindow* window) {
		m_window = window;
	}
	Input::StartUp() {
		size_t windowHnd = 0;
		m_window->getCustomAttribute("WINDOW", &windowHnd);
		std::string windowHandleAsString = "";
		std::ostringstream windowHndStr;
		windowHndStr << windowHnd;
		windowHandleAsString = windowHndStr.str();
		OIS::ParamList lSpecialParameters;
		lSpecialParameters.insert(std::make_pair(std::string("WINDOW"), windowHandleAsString));
		im = OIS::InputManager::createInputSystem(lSpecialParameters);
		keyboard = static_cast<OIS::Keyboard*>(im->createInputObject(OIS::OISKeyboard, false));
		mouse = static_cast<OIS::Mouse*>(im->createInputObject(OIS::OISMouse, false));

	}
}