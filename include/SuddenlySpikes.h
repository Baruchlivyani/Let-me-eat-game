#pragma once
#include "SmartObject.h"

class SuddenlySpikes : public SmartObject
{
public:
	SuddenlySpikes(sf::Texture& texture, sf::Vector2f location, double_t size);
	void handleCollisione(SmartObject& smartObject) override;
	void handleOutOfWorld(sf::Vector2u WindowSize) override;
	void move() override;
	void handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func) override;
	void handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func) override;
	void handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func) override;

private:
	std::vector<details> initAnimationData();
};

