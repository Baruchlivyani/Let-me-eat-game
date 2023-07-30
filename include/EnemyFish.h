#pragma once
#include "SmartObject.h"

//responsible for the various player enemies and implementing 
//the functions related to all of them - inherits from the
//SmartObject class.

class EnemyFish : public SmartObject
{

public:
	EnemyFish(sf::Texture& texture, sf::Vector2f location , double_t size, Direction direction);
	void randDirection();
	virtual void move() override;
	virtual void handleCollisione(SmartObject& smartObject) {};
	virtual void handleCollisione(eatS& smartObject, std::function<void(size_t)> func) {};
	virtual void handleCollisione(eatM& smartObject, std::function<void(size_t)> func) {};
	virtual void handleCollisione(eatL& smartObject, std::function<void(size_t)> func) {};
	void handleOutOfWorld(sf::Vector2u windowSize) override;	
	void ranAway(SmartObject& player) override {};

	
protected:
	size_t m_fishValue;
	bool m_isRun;

};

