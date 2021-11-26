#include "TextComponent.hpp"


namespace cave {

	TextComponent::TextComponent(float positionLeft, float positionTop, float width, float height) {
		m_overlay = Overlay::Overlay();
		m_overlay.configureContainer(positionLeft, positionTop, width, height);
		m_initialized = false;
	}

	void TextComponent::configureTextContainer(float positionLeft, float positionTop, float width, float height) {
		m_overlay.configureContainer(positionLeft, positionTop, width, height);
	}

	void TextComponent::addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height) {
		m_overlay.addTextElement(textElementName, positionLeft, positionTop, width, height);
	}

	void TextComponent::configureTextElement(std::string& textElementName, int fontSize, std::string fontName, caveColour colour){
		Ogre::ColourValue ogreColour = Ogre::ColourValue(colour.r, colour.g, colour.b, colour.alpha);
		m_overlay.configureTextElement(textElementName, fontSize, fontName, ogreColour);
	}

	void TextComponent::displayText(std::string& textElementName, std::string& caption) {
		m_overlay.displayText(textElementName, caption);
	}

	void TextComponent::hideText(std::string& textElementName) {
		m_overlay.hideText(textElementName);
	}

}