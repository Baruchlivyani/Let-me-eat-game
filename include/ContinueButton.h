#pragma once
#include "Button.h"

class ContinueButton : public Button
{

public:
	ContinueButton();
	void showContentButton(GameController& game, GameBoard& board) override;

private:

};

