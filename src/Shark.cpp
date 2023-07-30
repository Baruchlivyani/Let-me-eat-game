#include "Shark.h"
#include "Factory.h"
#include <iostream>
//===============================================
//static auto registerIt = Factory<SmartObject>::instance().registerType(
//	ObjectType::Shark,
//	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
//	{
//		return std::make_unique<Shark>(texture, location, size);
//	}
//);


Shark::Shark(sf::Texture& texture, sf::Vector2f location, double_t size, 
	std::function<sf::Vector2f()> playerLocationFunc , float_t speedPerSecond) :
	EnemyFish(texture, location, size, Direction::Right) , m_playerLocationFunc(playerLocationFunc),
	m_speedPerSecond(speedPerSecond)/*, m_algoritem(std::make_unique<eatS>()),*/
{
	m_mood = m_lastMood = Mood::Stay;
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Stay)->second[0]);
}
//===============================================
std::vector<details> Shark::initAnimationData()
{
	return std::vector<details>{
		{
			{300, 300},
				6,
			{ 0, 3410 },
			{ 10, 0 },
			Mood::Stay

		},
			{
			{300, 300},
				6,
			{ 0, 3720},
			{ 10, 0 },
			Mood::Swim
			},

		{
			{300, 300},
				8,
			{0, 4030},
			{10, 0},
			Mood::Eat
		},
	};
}
//===============================================
void Shark::move()
{

	//updateMood(Mood::Stay, true);
	//std::cout << m_clockMood.getElapsedTime().asSeconds() << "\n";
	if (m_clockMood.getElapsedTime().asSeconds() > 5 && m_mood == Mood::Stay)
	{
		updateMood(Mood::Swim, false);
		m_clockMood.restart();
	}



		const auto deltaTime = m_clockMove.restart();
		const auto speedPerSecond = 30.f;
		m_sprite.move(chasingFish() * deltaTime.asSeconds() * m_speedPerSecond);

}
//===============================================
sf::Vector2f Shark::chasingFish() 
{
	sf::Vector2f direction;
	if (m_clockChase.getElapsedTime().asSeconds() > 10)
	{
		if (m_clockChase.getElapsedTime().asSeconds() < 20)
		{
			direction.x = m_playerLocationFunc().x > m_sprite.getPosition().x ? 1 : -1;
			direction.y = m_playerLocationFunc().y > m_sprite.getPosition().y ? 1 : -1;
			direction.x = m_playerLocationFunc().x == m_sprite.getPosition().x ? 0 : direction.x;
		}
		else
			m_clockChase.restart();
	}
	else
	{
		direction.y = (rand() / (float)RAND_MAX) * 2.0 - 1.0;
		direction.x = 1;
	}
	if (m_playerLocationFunc().x > m_sprite.getPosition().x + 5 || m_playerLocationFunc().x < m_sprite.getPosition().x - 5)
		direction.x < 0 ? replaceSide(Direction::Left) : replaceSide(Direction::Right);

	return direction;	
}
//===============================================
void Shark::handleCollisione(SmartObject& smartObject)
{
	smartObject.handleCollisione(*this);
	updateMood(Mood::Eat, false);
}
//===============================================
void Shark::ranAway(SmartObject& player)
{
	//m_direction.x = m_sprite.getPosition().x > player.getLocation().x ? 1 : -1;
	//m_direction.y = m_sprite.getPosition().y > player.getLocation().y ? 1 : -1;
	//replaceSide(Direction(m_direction.x));
	//m_isRun = true;
	updateMood(Mood::Eat, false);
}
/*
void LFish::handleCollisione(eatS& smartObject, std::function<void(size_t)> func)
{
	m_isEaten = false;
}
void LFish::handleCollisione(eatM& smartObject, std::function<void(size_t)> func)
{
	m_isEaten = false;
}
void LFish::handleCollisione(eatL& smartObject, std::function<void(size_t)> func)
{
	m_isEaten = true;
	func(m_fishValue);
}*/

