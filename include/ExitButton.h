#pragma once
#include "Button.h"
class GameController;
class ExitButton : public Button
{
public:
	ExitButton();
	void showContentButton(GameController& game, GameBoard& board)override;


private:
	sf::Text m_printing;

};
