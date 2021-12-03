#include "TextComponent.hpp"


namespace cave {

	TextComponent::TextComponent(float positionLeft, float positionTop, float width, float height) {
		m_container.configureContainer(positionLeft, positionTop, width, height);
		m_initialized = false;
	}

	void TextComponent::configureTextContainer(float positionLeft, float positionTop, float width, float height) {
		m_container.configureContainer(positionLeft, positionTop, width, height);
	}

	void TextComponent::addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height) {
		m_container.addTextElement(textElementName, positionLeft, positionTop, width, height);
	}

	void TextComponent::configureTextElement(std::string& textElementName, float fontSize, std::string fontName, caveColour colour){
		Ogre::ColourValue ogreColour = Ogre::ColourValue(colour.r, colour.g, colour.b, colour.alpha);
		m_container.configureTextElement(textElementName, fontSize, fontName, ogreColour);
	}

	void TextComponent::displayText(std::string& textElementName, std::string& caption) {
		m_container.displayText(textElementName, caption);
	}

	void TextComponent::hideTextContainer() {
		m_container.hideTextContainer();
	}

}