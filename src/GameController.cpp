#include "GameController.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "AnimationData.h"
//===============================================
GameController::GameController() :
	m_isPouse(false), m_startGame(true), m_exit(false)
{
	m_levels.push_back(std::make_shared<Level1>());
	m_levels.push_back(std::make_shared<Level2>());
	m_levels.push_back(std::make_shared<Level3>());
	m_levels.push_back(std::make_shared<Level4>());
	m_levels.push_back(std::make_shared<Level5>());
	m_levels.push_back(std::make_shared<Level6>());
}
//===============================================
//Start the game before the particular data in the
//current stage you are holding
//===============================================
void GameController::startGame(std::shared_ptr<LevelBase> selectLevel)
{
	singleLevelWasSelected(selectLevel);
	if (m_exit)
		return;
	for (auto& level : m_levels)
	{
		if (level->isFinish() || (selectLevel && level->numOfLevel() <= selectLevel->numOfLevel()))
			continue;

		ResetFailed(level);

		GameBoard board(level);
		if (m_startGame)
		{
			m_startGame = false;
			m_menu.openMenu(*this, board);
		}
		if (m_exit)
			return;
		runOnLevel(board);
	}
	m_exit = true;
}
//===============================================
//run on the game and make the moves And call 
//all the relevant departments that operate the game
//===============================================
void GameController::runOnLevel(GameBoard& board)
{
	Resources::instance().playingSound();
	board.viewManager();
	board.resetClocks();


	while (board.getWindow()->isOpen())
	{
		board.getWindow()->clear();
		board.print();
		eventManeger(board);
		if (!m_isPouse)
			board.moveObjects();
		board.replaceTexture();
		board.viewManager();
		board.outOfWorldManager();
		board.collisioneManager();
		board.eatenManager();
		m_goMenu.setPosition(board.getWindow());
		m_goMenu.drowButton(board.getWindow());
		m_goMenu.showContentButton(*this, board, m_menu);
		board.getWindow()->display();
		if (board.isVictory())
		{
			board.printVictory();
			break;
		}
		if (board.isLost())
			m_menu.openMenu(*this, board);
	}
}
//===============================================
//Handle various events that occur during the game
//===============================================
void GameController::eventManeger(GameBoard& board)
{
	for (auto event = sf::Event{}; board.getWindow()->pollEvent(event);)
	{
		switch (event.type)
		{

		case sf::Event::Closed:
			board.getWindow()->close();
			m_exit = true;
			break;

		case sf::Event::KeyPressed:
			isKeyPressed(event.key.code, board);
			break;

		case sf::Event::MouseMoved:
			if (m_goMenu.isButtonPressed(board.getWindow()->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))))
				m_goMenu.highlightsButton();
			else
				m_goMenu.resetHighlightsButton();
			break;


		case sf::Event::MouseButtonPressed:
			if (m_goMenu.isButtonPressed((board.getWindow()->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))))
				m_goMenu.turnOnButton();
			break;
		}
	}
}
//===============================================
void GameController::isKeyPressed(sf::Keyboard::Key code, GameBoard& board)
{
	switch (code)
	{
	case sf::Keyboard::Space:
		m_isPouse = !m_isPouse;
		board.resetClocks();
		break;
	}
}
//===============================================
std::vector<std::shared_ptr<LevelBase>>::iterator&& GameController::levelBeginVec()
{
	return m_levels.begin();
}
//===============================================
std::vector<std::shared_ptr<LevelBase>>::iterator&& GameController::levelEndVec()
{
	return m_levels.end();
}
//===============================================
void GameController::ResetFailed(std::shared_ptr<LevelBase>& level)
{
	level = level->copyMy();
	level->setStatus(Mood::unLocked);
}
//===============================================
void GameController::singleLevelWasSelected(std::shared_ptr<LevelBase>& selectLevel)
{
	if (selectLevel)
	{
		ResetFailed(selectLevel);
		GameBoard board(selectLevel);
		runOnLevel(board);
	}
}
//===============================================
void GameController::goExit(bool ToF)
{
	m_exit = ToF;
}
//===============================================
bool GameController::isExit()const
{
	return m_exit;
}
