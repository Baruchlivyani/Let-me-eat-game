#pragma once
#include "DecorativeObject.h"

class Victory :public DecorativeObject
{
public:
	Victory(sf::Texture& texture, sf::Vector2f location, double_t size, Mood mood);
	void move() override;
	sf::FloatRect getGlobalBounds();
	sf::Clock& getVictoryClock();
	void setPosition(sf::RenderWindow* m_gameWindow);

private:
	sf::Clock m_victoryClock;
	std::vector<details> initAnimationData();
};




