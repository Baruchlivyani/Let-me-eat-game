#include "ContinueButton.h"
#include "GameController.h"
//===============================================
ContinueButton::ContinueButton() :
	Button("Continue", sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.66), 40)
{}
//===============================================
void ContinueButton::showContentButton(GameController& game, GameBoard& board)
{
	m_text.setCharacterSize(35);
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		m_buttonOn = false;
		board.getWindow()->close();
		std::shared_ptr<LevelBase> level = nullptr;
		game.startGame(level);

	}
}