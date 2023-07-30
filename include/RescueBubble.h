#pragma once
#include "SmartObject.h"

//responsible for the rescue bubbles in the game -
//inherits from the SmartObject class.

class RescueBubble : public SmartObject
{

public:
	RescueBubble(sf::Texture& texture, sf::Vector2f location, double_t size);

	void randDirection();
	void move() override;
	std::vector<details> initAnimationData();
	void handleCollisione(SmartObject& smartObject) override;
	void handleCollisione(PlayerFish& player, std::function<sf::Vector2f()> func) override;
	sf::FloatRect getGlobalBounds();
	void burstBubble();
	void restart() override;
	void handleOutOfWorld(sf::Vector2u windowSize);

private:
	std::function<sf::Vector2f()> m_getPlayerLcocation;
	bool m_isProtector;

};
