#include "OptionsButton.h"
#include "GameController.h"
//===============================================
OptionsButton::OptionsButton(std::function<void(sf::RenderWindow*)> drow) :
	Button("Options", sf::Vector2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - WINDOW_HEIGHT / 10), 40),
	m_drowFunk(drow), m_backButton()
{}
//===============================================
//void HelpButton::turnOnButton(/*GameController& game, GameBoard& board*/)
//{
//	m_clockOn.restart();
//	m_key.updateMood(Mood::Bursts, false);
//	m_buttonOn = true;
//}

void OptionsButton::showContentButton(GameController& game, GameBoard& board)
{
	m_text.setOrigin(m_text.getGlobalBounds().width / 2 + 17, m_text.getGlobalBounds().height / 2);
	m_printing.setPosition(0, WINDOW_HEIGHT * 0.45);
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		m_buttonOn = false;
		while (board.getWindow()->isOpen() && !m_backButton.isBack())
		{
			board.getWindow()->clear();
			m_drowFunk(board.getWindow());
			board.getWindow()->draw(m_printing);
			m_backButton.drowButton(board.getWindow());

			std::for_each(game.levelBeginVec(), game.levelEndVec(), [&game, &board, this](auto& item)
				{
					Button* ptr = dynamic_cast<Button*>(item.get());
			if (ptr)
			{
				ptr->drowButton(board.getWindow());
				if (ptr->isButtonPressed(sf::Vector2f(getBackClickPosition(board.getWindow()))) &&
					item->getStatus() == Mood::unLocked)
					ptr->turnOnButton();
				ptr->showContentButton(game, board);
			}
			item->drowButtons(board.getWindow());
			item->drowIcon(board.getWindow());

				});
			board.getWindow()->display();
			if (m_backButton.isButtonPressed(sf::Vector2f(getBackClickPosition(board.getWindow()))))
				m_backButton.turnOnButton();
			HandleClosWindow(board.getWindow());
		}
	}
}