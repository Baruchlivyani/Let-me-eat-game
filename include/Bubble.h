#pragma once
#include "DecorativeObject.h"

//is responsible for the various bubbles that move during the game, and their management inherits
//from the DecorativeObject class.

class Bubble : public DecorativeObject
{
public:
	Bubble(sf::Texture& texture, sf::Vector2f location, double_t size) ;
	void move() override;
	void handleOutOfWorld(sf::Vector2u windowSize) override;
	sf::FloatRect getGlobalBounds();



private:
	std::vector<details> initAnimationData();
};



