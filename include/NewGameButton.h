#pragma once
#include "Button.h"
class GameController;
class NewGameButton : public Button
{
public:
	NewGameButton();
	void showContentButton(GameController& game,GameBoard& board)override;


};
