#pragma once
#include "PlayerBaseBehavior.h"

//responsible for managing the player's behavior, what fish he is
//allowed to eat - inherited from the department-
//PlayerBaseBehavior - which is responsible for the player's behavior.

class eatM :public PlayerBaseBehavior
{
public:
	eatM() {};
	bool handleCollisione(SFish& SFish) ;
	bool handleCollisione(MFish& SFish) ;
	bool handleCollisione(LFish& SFish) ;
	void handleCollisione(SmartObject& smartObject, std::function<void(size_t, Score)> func) ;
	std::unique_ptr<PlayerBaseBehavior> increaseBehavior()override;
	std::unique_ptr<PlayerBaseBehavior> decreaseBehavior()override;
	bool isGrow(size_t score)override;
	bool isSmaller(size_t score)override;



private:

};
