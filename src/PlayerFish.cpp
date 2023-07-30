#include "PlayerFish.h"
#include "Define.h"
#include "eatL.h"
#include "eatM.h"
#include "eatS.h"
#include "RescueBubble.h"
#include <iostream>
#include "Factory.h"
//=====================================
static auto registerIt = Factory<PlayerFish>::instance().registerType(
	ObjectType::PlayerFish,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<PlayerFish>
	{
		return std::make_unique<PlayerFish>(texture, location, size);
	}
);
//=====================================
PlayerFish::PlayerFish(sf::Texture& texture, sf::Vector2f location, double_t size) :
	SmartObject(texture, location, size, Direction::Right), m_Behavior(std::make_unique<eatS>()),
	m_score(0), m_isProtected(false), m_moveFirstTime(true), m_ProtectedSpikes(false), m_protectedOff(nullptr)
{
	m_clockReplace.restart();
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Swim)->second[0]);
}
//=====================================
std::vector<details> PlayerFish::initAnimationData()
{
	return std::vector<details>{
		{
			{300, 300},
				6,
			{ 0, 0 },
			{ 10, 0 },
				Mood::Swim

		},
		{
			{300, 300},
				6,
			{0, 310},
			 {10, 0},
			Mood::Stay
		},
	};
}
//=====================================
//moov the player by the keybord
//=====================================
void PlayerFish::move()
{
	if (m_clockProtected.getElapsedTime().asSeconds() > 2 && m_clockProtected.getElapsedTime().asSeconds() < 2.2)
		m_isProtected = false;

	if (m_clockStay.getElapsedTime().asSeconds() > 1.5)
		updateMood(Mood::Stay, true);

	m_lastLocation = m_sprite.getPosition();
	sf::Vector2f direction;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = sf::Vector2f(-1, 0);
		updateMove();
		replaceSide(Direction::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = sf::Vector2f(1, 0);
		updateMove();
		replaceSide(Direction::Right);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = sf::Vector2f(0, -1);
		updateMove();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = sf::Vector2f(0, 1);
		updateMove();

	}

	m_sprite.move(direction * m_clockMove.restart().asSeconds() * PLAYER_SPEED);
	ProtectedOffSpikes();
}
//=====================================
//moov the player by the mouse
//=====================================
void PlayerFish::moveByMouse(sf::RenderWindow* window)
{

	sf::Vector2f direction = { 0,0 };
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f worldMousePosition = window->mapPixelToCoords(mousePosition/*, window->getView()*/);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		if (worldMousePosition.x > m_sprite.getPosition().x + 10 || worldMousePosition.x < m_sprite.getPosition().x - 10)
		{
			if (worldMousePosition.x < m_sprite.getPosition().x)
			{
				updateMove();
				replaceSide(Direction::Left);
				direction.x = -1;
			}
			if (worldMousePosition.x > m_sprite.getPosition().x)
			{
				updateMove();
				replaceSide(Direction::Right);
				direction.x = 1;
			}
		}
		if (worldMousePosition.y > m_sprite.getPosition().y + 10 || worldMousePosition.y < m_sprite.getPosition().y - 10)
		{
			if (worldMousePosition.y < m_sprite.getPosition().y)
			{
				updateMove();
				direction.y = -1;
			}
			if (worldMousePosition.y > m_sprite.getPosition().y)
			{
				updateMove();
				direction.y = 1;
			}
		}
	}
	m_sprite.move(direction * m_clockMove.restart().asSeconds() * 30000.f);
}
//=====================================
sf::Vector2f PlayerFish::getScale() const
{
	return m_sprite.getScale();
}
//=====================================
sf::Vector2f PlayerFish::getLastLocation() const
{
	return m_lastLocation;
}
//=====================================
void PlayerFish::handleOutOfWorld(sf::Vector2u WindowSize)
{
	if (isOutOfWorld(WindowSize))
		m_sprite.setPosition(m_lastLocation);
}
//=====================================
void PlayerFish::handleCollisione(Shark& smartObject)
{
	m_isEaten = true;
	ProtectedOff();
}
//=====================================
void PlayerFish::handleCollisione(LFish& smartObject)
{
	m_isEaten = m_Behavior->handleCollisione(smartObject);
	ProtectedOff();
}
//=====================================
void PlayerFish::handleCollisione(MFish& smartObject)
{
	m_isEaten = m_Behavior->handleCollisione(smartObject);
	ProtectedOff();
}
//=====================================
void PlayerFish::handleCollisione(SFish& smartObject)
{
	m_isEaten = m_Behavior->handleCollisione(smartObject);
	ProtectedOff();
}
//=====================================
void PlayerFish::handleCollisione(SmartObject& smartObject)
{
	m_Behavior->handleCollisione(smartObject, std::bind(&PlayerFish::updateScore, this,
		std::placeholders::_1, std::placeholders::_2));
	smartObject.handleCollisione(*this, std::bind(&PlayerFish::getLocation, this/* std::placeholders::_1*/));
}
//=====================================
void PlayerFish::handleCollisione(RescueBubble& smartObject)
{
	smartObject.handleCollisione(*this, std::bind(&PlayerFish::getLocation, this /*, std::placeholders::_1*/));
}
//=====================================
void PlayerFish::updateScore(size_t value, Score mood)
{
	switch (mood)
	{
	case UPDATE:
		m_score += value;
		if (m_Behavior->isGrow(m_score))
		{
			Resources::instance().growthSound();
			m_Behavior = m_Behavior->increaseBehavior();
			m_sprite.scale(1.5, 1.5);
		}
		break;

	case RESETE:
		if (!m_ProtectedSpikes)
		{
			ProtectedSpikes();
			m_score = value;
			m_isEat = true;
			if (m_Behavior->isSmaller(m_score))
			{
				m_Behavior = m_Behavior->decreaseBehavior();
				m_sprite.scale(2.0f / 3.0f, 2.0f / 3.0f);
			}
			m_isProtected = true;
		}
		break;
	}

}
//=====================================
size_t PlayerFish::getScore() const
{
	return m_score;
}
//=====================================
void PlayerFish::ProtectedOff()
{
	if (m_clockProtected.getElapsedTime().asSeconds() < 2)
	{
		m_isEaten = false;
		m_isProtected = true;
	}
	else if (m_isProtected && m_isEaten)
	{
		m_clockProtected.restart();
		m_isEaten = false;
		if (m_protectedOff)
			m_protectedOff();
	}
}
//=====================================
void PlayerFish::setProtectedOff(std::function<void()> burstBubbleFunc)
{
	m_isProtected = true;
	m_protectedOff = burstBubbleFunc;
}
//=====================================
void PlayerFish::restart()
{
	m_moveFirstTime = true;
	m_score = 0;
	m_Behavior = std::make_unique<eatS>();
	m_isEaten = m_isProtected = false;
	m_sprite.setScale(sf::Vector2f(PIXEL_SIZE / m_sprite.getGlobalBounds().width,
		PIXEL_SIZE / m_sprite.getGlobalBounds().height));
	m_sprite.scale(PLAYER_SIZE * 0.5, PLAYER_SIZE * 0.5);
}
//=====================================
void PlayerFish::ProtectedSpikes()
{
	m_ProtectedSpikes = true;
	m_clockProtectedSpikes.restart();
}
//=====================================
void PlayerFish::ProtectedOffSpikes()
{
	if (m_clockProtectedSpikes.getElapsedTime().asSeconds() > 3.5)
	{
		m_ProtectedSpikes = false;
		m_isEat = true;
		m_sprite.setColor(sf::Color::Color(m_sprite.getColor().r,
			m_sprite.getColor().g, m_sprite.getColor().b, 255));
	}
}
//=====================================
void PlayerFish::updateMove()
{
	updateMood(Mood::Swim, true);
	m_clockStay.restart();
}
//=====================================
sf::FloatRect PlayerFish::getMouthBounds() const
{
	return sf::FloatRect(sf::Vector2f(m_RoL == Direction::Right ?
		m_sprite.getPosition().x + m_sprite.getGlobalBounds().width * MOUTH_SIZE_PLY * 3 :
		m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * MOUTH_SIZE_PLY * 3
		, m_sprite.getPosition().y),
		sf::Vector2f(m_sprite.getGlobalBounds().width * MOUTH_SIZE_PLY, m_sprite.getGlobalBounds().height * MOUTH_SIZE_PLY));
}
