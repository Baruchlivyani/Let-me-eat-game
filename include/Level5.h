#pragma once
#include "LevelBase.h"


//responsible for the different stages of the game, 
//loading objects respectively and more - inherit from LevelBase.

class Level5 : public LevelBase, public Button
{
public:
	std::shared_ptr<LevelBase> copyMy() override;
	Level5();
	~Level5() = default;
	void showContentButton(GameController& game, GameBoard& board);



};
