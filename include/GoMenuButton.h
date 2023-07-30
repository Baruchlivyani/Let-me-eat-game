#pragma once
#include "Button.h"
#include "Menu.h"
class GameController;

class GoMenuButton : public Button
{
public:
	GoMenuButton();
	void showContentButton(GameController& game, GameBoard& board, Menu& menu);
	void setPosition(sf::RenderWindow* m_gameWindow);


private:
	sf::Text m_printing;

};
