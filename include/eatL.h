#pragma once
#include "PlayerBaseBehavior.h"

//responsible for managing the player's behavior, what fish he is
//allowed to eat - inherited from the department-
//PlayerBaseBehavior - which is responsible for the player's behavior.


class eatL :public PlayerBaseBehavior
{
public:
	eatL() {};
	bool handleCollisione(SFish& SFish) override;
	bool handleCollisione(MFish& SFish) override;
	bool handleCollisione(LFish& SFish) override;
    void handleCollisione(SmartObject& smartObject, std::function<void(size_t, Score)> func) override;
	std::unique_ptr<PlayerBaseBehavior> decreaseBehavior() override;
	bool isSmaller(size_t score) override;


private:

};
