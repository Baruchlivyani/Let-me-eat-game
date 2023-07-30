#pragma once
#include "LevelBase.h"

//responsible for the different stages of the game, 
//loading objects respectively and more - inherit from LevelBase.

class Level3 : public LevelBase, public Button
{
public:
	Level3();
	~Level3() = default;
	std::shared_ptr<LevelBase> copyMy() override;
	void showContentButton(GameController& game, GameBoard& board);


};
