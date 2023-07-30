#include "GoMenuButton.h"
#include "GameController.h"
//===============================================
GoMenuButton::GoMenuButton() :
	Button("Menu", sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50), 15)
{
	m_defaultColor = (sf::Color::Yellow);
	m_color = (sf::Color::Red);
}
//===============================================
void GoMenuButton::showContentButton(GameController& game, GameBoard& board, Menu& menu)
{
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		m_buttonOn = false;
		menu.openMenu(game, board);
	}
}

void GoMenuButton::setPosition(sf::RenderWindow* m_gameWindow)
{
	m_text.setOrigin(m_text.getGlobalBounds().width / 2+10, m_text.getGlobalBounds().height / 2+10);
	m_text.setCharacterSize(18);

	auto topLeft = sf::Vector2f(m_gameWindow->getView().getCenter().x - m_gameWindow->getView().getSize().x / 2,
		m_gameWindow->getView().getCenter().y - m_gameWindow->getView().getSize().y / 2);
	m_text.setPosition(topLeft + m_gameWindow->getView().getSize() - sf::Vector2f(20, 20));
	m_key.setPosition(topLeft + m_gameWindow->getView().getSize() - sf::Vector2f(20, 20));
}