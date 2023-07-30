#pragma once
#include "Menu.h"
#include "LevelBase.h"
#include "GameBoard.h"
#include <vector>
#include "Victory.h"
//responsible for managing the game, its operation,
//transferring stages, calls to other departments, and more.

class GameController
{
public:
	GameController();
	~GameController() = default;
	void startGame(std::shared_ptr<LevelBase> selectLevel);
	void runOnLevel(GameBoard& board);
	void eventManeger(GameBoard& board);
	void isKeyPressed(sf::Keyboard::Key code, GameBoard& board);
	std::vector<std::shared_ptr<LevelBase>>::iterator&& levelBeginVec();
	std::vector<std::shared_ptr<LevelBase>>::iterator&& levelEndVec();
	bool isExit()const;
	void goExit(bool ToF);



private:
	void ResetFailed(std::shared_ptr<LevelBase>& level);
	void singleLevelWasSelected(std::shared_ptr<LevelBase>& level);
	std::vector<std::shared_ptr<LevelBase>> m_levels;
	Menu m_menu;
	bool m_isPouse;
	bool m_startGame;
	GoMenuButton m_goMenu;
	bool m_exit;
};

