#include "NewGameButton.h"
#include "GameController.h"
#include "LevelBase.h"
//===============================================
NewGameButton::NewGameButton() :
	Button(" New\nGame", sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2- WINDOW_HEIGHT / 10), 40)/*,
	m_runOnLevel(runOnLevel)*/
{}
//===============================================
//void NewGameButton::turnOnButton(/*GameController& game, GameBoard& board*/)
//{
//	//game.runOnLevel(board);
//	m_clockOn.restart();
//	m_key.updateMood(Mood::Bursts, false);
//	m_buttonOn = true;
//}

void NewGameButton::showContentButton(GameController& game, GameBoard& board)
{
	if (m_buttonOn && m_clockOn.getElapsedTime().asSeconds() > REPLACE_DUTTON_TIME)
	{
		m_buttonOn = false;
		std::for_each(game.levelBeginVec(), game.levelEndVec(), [/*this*/](auto& i)
			{
				i->setFinish(false);
				i->setFails(true);
			});

		board.getWindow()->close();
		std::shared_ptr<LevelBase> level = nullptr;
		game.startGame(level);
		//game.runOnLevel(board);
	}		
}