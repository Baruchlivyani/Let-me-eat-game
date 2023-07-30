#pragma once
#include "LevelBase.h"


//responsible for the different stages of the game, 
//loading objects respectively and more - inherit from LevelBase.

class Level1 : public LevelBase , public Button
{
public:
	Level1();
	~Level1() = default;
	std::shared_ptr<LevelBase> copyMy() override;
	void showContentButton(GameController& game, GameBoard& board);
	void drowButtons(sf::RenderWindow* menuWindow)override;
	size_t numOfLevel() const override;
	
private:
	
};
