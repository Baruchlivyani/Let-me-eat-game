#pragma once
#include "SmartObject.h"
#include <memory.h>
#include "PlayerBaseBehavior.h"

//responsible for the player, its operation, conflict management, and
//things related to it - inherits from the SmartObject class.

class PlayerFish : public SmartObject
{
public:
	PlayerFish(sf::Texture& texture, sf::Vector2f location, double_t size);
	PlayerFish() {};
	sf::Vector2f getLastLocation() const;
	void handleOutOfWorld(sf::Vector2u WindowSize) override;
	void setProtectedOff(std::function<void()> burstBubbleFunc);
	void handleCollisione(Shark& smartObject) override;
	void handleCollisione(LFish& smartObject) override;
	void handleCollisione(MFish& smartObject) override;
	void handleCollisione(SFish& smartObject) override;
	void handleCollisione(SmartObject& smartObject) override;
	void handleCollisione(RescueBubble& smartObject) override;
	sf::FloatRect getMouthBounds()const override;
	void move() override;
	void restart() override;
	sf::Vector2f getScale() const;
	void updateScore(size_t value, Score mood);
	size_t getScore() const;
	void moveByMouse(sf::RenderWindow* window);

private:
	void updateMove();
	sf::Clock m_clockStay;
	std::function<void()> m_protectedOff;
	std::vector<details> initAnimationData();
	sf::Vector2f m_lastLocation;
	std::unique_ptr<PlayerBaseBehavior> m_Behavior;
	void ProtectedOff();
	bool m_isProtected;
	bool m_ProtectedSpikes;
	void ProtectedSpikes();
	void ProtectedOffSpikes();
	size_t m_score;
	sf::Clock m_clockProtected;
	sf::Clock m_clockProtectedSpikes;
	sf::Clock m_clockFirstTime;
	bool m_moveFirstTime;
};
