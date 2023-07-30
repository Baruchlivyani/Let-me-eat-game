#pragma once

#include "Resources.h"
#include "Button.h"
#include <memory>
#include "Define.h"
#include "Level5.h"
//===============================================
class GameController;
class GameBoard;
//===============================================
//responsible for managing the game menu, printing it,
//and things related to it.
//The role of this department is to manage the game menu,
//and make sure that the actions are performed according to the player's click


class Menu
{
public:
	Menu();
	void openMenu(GameController& Game, GameBoard& board);
	void drow(sf::RenderWindow* menuWindow);

private:
	void setButtons();
	void moveBackground(sf::RenderWindow* menuWindow);
	void drowMenu(GameController& game, GameBoard& board);
	void isMouseMoved(const sf::Event& event);
	void isMousReleased(GameController& game, const sf::Event& event, GameBoard& board);
	void isKeyPressed(GameController& game, const sf::Event& event, GameBoard& board);
	//Moves the cursor backand forth
	void isUpPressed();
	//Moves the cursor backand forth
	void isDownPressed();
	void flashingArrow();
	void resetfirstbutton();
	std::vector <std::unique_ptr<Button>> m_buttons;
	sf::ConvexShape m_arrow;
	sf::Clock m_arrowClock;
	sf::Sprite m_background;
	bool m_closeMenu;
	Level5 m_fishBackground;
};