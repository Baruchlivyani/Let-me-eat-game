#include "ExitButton.h"
#include "GameBoard.h"
#include "GameController.h"
//===============================================
ExitButton::ExitButton() :
	Button("EXIT", sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50), 30)
{}
//===============================================
void ExitButton::showContentButton(GameController& game, GameBoard& board)
{
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		m_buttonOn = false;
		board.getWindow()->close();
		game.goExit(true);
		std::shared_ptr<LevelBase> level = nullptr;
		game.startGame(level);
	}
}