#pragma once
#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP
#include "RenderingManager.hpp"


namespace cave {

	/**Componente que representa un cuadro de texto renderizable.
*
*/
	struct TextComponent {

	private:
		Container m_container;

	public:

		bool m_initialized;/**< Indica si el componente fue inicializado */

		TextComponent(float positionLeft, float positionTop, float width, float height);

		void configureTextContainer(float positionLeft, float positionTop, float width, float height);/**<Configura tamanño y posicion del subcontenedor */

		void addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height);/**<Agrega elemento de texto al overlay */

		void configureTextElement(std::string& textElementName, float fontSize, std::string fontName, caveColour colour);/**<Configura elemento de texto seteando la fuente, su tamaño y color */
		
		void displayText(std::string& textElementName, std::string& caption);

		void hideText(std::string& textElementName);


	};




}

#endif