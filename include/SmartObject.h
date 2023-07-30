#pragma once
#include "GameObject.h"
//===============================================
class LFish;
class MFish;
class SFish;
class Shark;
class eatL;
class eatS;
class eatM;
class PlayerFish;
class RescueBubble;
//===============================================

//responsible for the smart game objects of
//any kind in general - inherits from the GameObject class.

class SmartObject : public GameObject
{
public:
	SmartObject(sf::Texture& texture, sf::Vector2f location);
	SmartObject(sf::Texture& texture, sf::Vector2f location, double_t size, Direction directionm);
	SmartObject() {};
	virtual void move() = 0;
	virtual void handleOutOfWorld(sf::Vector2u WindowSize) {};
	sf::FloatRect getAroundBounds() const;
	bool isCollisione(SmartObject& smartObject);
	bool isAroundCollisione(SmartObject& smartObject);
	virtual sf::FloatRect getMouthBounds() const;
	virtual void handleCollisione(SmartObject& smartObject) {};
	virtual void handleCollisione(LFish& smartObject) {};
	virtual void handleCollisione(Shark& smartObject) {};
	virtual void handleCollisione(MFish& smartObject) {};
	virtual void handleCollisione(SFish& smartObject) {};
	virtual void handleCollisione(RescueBubble& smartObject) {};
	virtual void handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func) {};
	virtual void handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func) {};
	virtual void handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func) {};
	virtual void handleCollisione(PlayerFish& player, std::function<sf::Vector2f()> func) {};
	virtual void ranAway(SmartObject& player) {};
	void victoryMood();
	void blink();
	sf::Vector2f getLocation() const;
	void setEat();
	bool isEaten();
	virtual void restart();

protected:
	sf::Clock m_clockBlink;
	sf::Clock m_clockDirection;
	int m_maxDirection;
	sf::FloatRect getSmallerBounds() const;
	bool m_isEaten;
	bool m_isEat;
};
