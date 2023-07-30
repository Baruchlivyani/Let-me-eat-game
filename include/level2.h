#pragma once
#include "LevelBase.h"

//responsible for the different stages of the game, 
//loading objects respectively and more - inherit from LevelBase.

class Level2 : public LevelBase, public Button
{
public:
	Level2();
	std::shared_ptr<LevelBase> copyMy() override;
	~Level2() = default;
	void showContentButton(GameController& game, GameBoard& board);
	size_t numOfLevel() const override;

};
