#pragma once
#include "GameObject.h"

//responsible for the game objects designed for the purpose of adding 
//beauty to the game, inherits from class-
//GameObject - which is responsible for the general game objects.

class DecorativeObject : public GameObject
{
public:
	DecorativeObject(sf::Texture& texture, sf::Vector2f location, double_t size, Direction direction);
	DecorativeObject() {};
	virtual void move() = 0;
	virtual void handleOutOfWorld(sf::Vector2u WindowSize) {};


private:

};
