#include "Button.h"

//An abstract class that assigns to each button
//in the menu
//And the different functions for each button realized by virtual			
//===============================================
Button::Button(const char buttonName[], sf::Vector2f Location, int sizeFont) :
	m_text(buttonName, Resources::instance().getArielFont()), m_pressedNow(false),
	m_defaultColor(sf::Color(255, 255, 255, 255)), m_color(sf::Color::Yellow),
	m_key(Resources::instance().getSpriteShit(), sf::Vector2f(Location.x - (sizeFont / 20), Location.y + (sizeFont / 20)), sizeFont/15), m_buttonOn(false)
{
	m_text.setPosition(sf::Vector2f(Location.x - (sizeFont/20), Location.y+ (sizeFont / 20)));
	m_text.setCharacterSize(sizeFont);
	m_text.setFillColor(m_defaultColor);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2+10, m_text.getGlobalBounds().height / 2);
}
//===============================================
void Button::setText(sf::Vector2f Location)
{
	m_text.setPosition(Location);
	m_text.setFillColor(m_defaultColor);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
}
//===============================================
void Button::drowButton(sf::RenderWindow* menuWindow)
{
	m_key.replaceTexture();
	m_key.drow(menuWindow);
	menuWindow->draw(m_text);
}
//===============================================
void Button::turnOnButton()
{
	if (!m_buttonOn)
	{
		m_clockOn.restart();
		m_key.updateMood(Mood::Bursts, false);
		m_buttonOn = true;
	}
}
//===============================================
//A function responsible for highlighting as open the cursor on it
void Button::highlightsButton(sf::ConvexShape& m_arrow)
{
	m_arrow.setPosition(m_text.getPosition().x + m_text.getGlobalBounds().width / 2 + 20,
		m_text.getPosition().y + m_text.getGlobalBounds().height / 2 - 20);

	m_pressedNow = true;
	m_text.setFillColor(m_color);

}
//===============================================
void Button::highlightsButton()
{
	m_pressedNow = true;
	m_text.setFillColor(m_color);
}
//===============================================
void Button::resetHighlightsButton()
{
	m_pressedNow = false;
	m_text.setFillColor(m_defaultColor);

}
//===============================================
bool Button::isPressedNow()
{
	return m_pressedNow;
}
//===============================================
bool Button::isButtonPressed(sf::Vector2f click)
{
	return (m_key.getGlobalBounds().contains(click));
}
//===============================================
sf::Vector2i Button::getBackClickPosition(sf::RenderWindow* menuWindow)const
{
	sf::Vector2i click;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		click = sf::Mouse::getPosition(*menuWindow);
	}
	return click;
}
//===============================================
void Button::HandleClosWindow(sf::RenderWindow* menuWindow) const
{
	for (auto event = sf::Event{}; menuWindow->pollEvent(event);)
		if (event.type == sf::Event::Closed)
			menuWindow->close();
}


