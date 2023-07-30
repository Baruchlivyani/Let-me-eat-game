#include "CreditButton.h"
#include "GameBoard.h"
//===============================================
CreditButton::CreditButton(std::function<void(sf::RenderWindow*)> drow) :
	Button("Credit", sf::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT * 0.6), 28),
	m_drowFunc(drow),
	m_printing("PROGRAMMERS:\n\nMeir Shuvax,  "       "    Baruch Leviani.",
		Resources::instance().getArielFont(), 50),
	m_sprite(Resources::instance().getProgrammersTexture()),
	m_backButton()
{
	m_printing.setPosition(sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 3));
	m_sprite.setPosition(sf::Vector2f(0, 0));

}
//===============================================
void CreditButton::showContentButton(GameController& game, GameBoard& board)
{
	m_text.setOrigin(m_text.getGlobalBounds().width / 2 + 8, m_text.getGlobalBounds().height / 2);
	m_text.setCharacterSize(25);
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		while (board.getWindow()->isOpen() && !m_backButton.isBack())
		{
			board.getWindow()->clear();
			m_drowFunc(board.getWindow());
			board.getWindow()->draw(m_sprite);
			board.getWindow()->draw(m_printing);
			m_backButton.drowButton(board.getWindow());
			board.getWindow()->display();
			if (m_backButton.isButtonPressed(sf::Vector2f(getBackClickPosition(board.getWindow()))))
				m_backButton.turnOnButton();
			HandleClosWindow(board.getWindow());

		}
		m_buttonOn = false;
	}
}