#pragma once
#include "EnemyFish.h"

//responsible for the different fish in the game, their collision
//management and more - inherit from the EnemyFish class.

class MFish :public EnemyFish
{
public:
	MFish(sf::Texture& texture, sf::Vector2f location, double_t size);
	void handleCollisione(SmartObject& smartObject) override;
	void handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func) override;																 
	void handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func) override;																 
	void handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func) override;

private:
	std::vector<details> initAnimationData();
};

