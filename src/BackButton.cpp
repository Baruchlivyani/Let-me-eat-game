#include "BackButton.h"
//===============================================
BackButton::BackButton() :
	Button("Back", sf::Vector2f(WINDOW_WIDTH -50, WINDOW_HEIGHT -50), 30)
{}
//===============================================
bool BackButton::isBack()
{
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		m_buttonOn = false;
		return true;
	}

	return false;
}