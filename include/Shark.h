#pragma once
#include "EnemyFish.h"

//responsible for the shark, its operation, movement - its algorithm,
//and things related to it - inherits from the EnemyFish class.

class Shark : public EnemyFish
{
public:
	Shark(sf::Texture& texture, sf::Vector2f location, double_t size, 
		std::function<sf::Vector2f()> playerLocationFunc, float_t speedPerSecond);
	void handleCollisione(SmartObject& smartObject) override;
	void move() override;
	void ranAway(SmartObject& player) override;


private:
	sf::Vector2f chasingFish() ;
	sf::Clock m_clockChase;
	sf::Clock m_clockTimeChase;
	std::vector<details> initAnimationData();
	std::function<sf::Vector2f()> m_playerLocationFunc;
	float_t m_speedPerSecond;
};
