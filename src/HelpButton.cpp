#include "HelpButton.h"
#include "GameController.h"
//===============================================
HelpButton::HelpButton(std::function<void(sf::RenderWindow*)> drow) :
	Button("Help", sf::Vector2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 7, WINDOW_HEIGHT * 0.6), 28),
	m_drowFunk(drow),
	m_printing(HELP,
		Resources::instance().getArielFont(), 30), m_backButton()
{}
//===============================================
//void HelpButton::turnOnButton(/*GameController& game, GameBoard& board*/)
//{
//	m_clockOn.restart();
//	m_key.updateMood(Mood::Bursts, false);
//	m_buttonOn = true;
//}

void HelpButton::showContentButton(GameController& game, GameBoard& board)
{
	m_printing.setPosition(0, WINDOW_HEIGHT * 0.45);
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		while (board.getWindow()->isOpen() && !m_backButton.isBack())
		{
			board.getWindow()->clear();
			m_drowFunk(board.getWindow());
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