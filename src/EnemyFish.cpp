#include "EnemyFish.h"
#include <iostream>
//===============================================
EnemyFish::EnemyFish(sf::Texture& texture, sf::Vector2f location, double_t size, Direction direction):
	 SmartObject(texture, location, size, direction), m_isRun(false)
{
	m_maxDirection = rand() % (MAX_TIME_DIR - MIN_TIME_DIR + 1) + MIN_TIME_DIR;
	m_sprite.getPosition().x < WINDOW_WIDTH / 2 ? replaceSide(Direction::Right) : replaceSide(Direction::Left);
	randDirection();
}
//===============================================
void EnemyFish::move()
{

	if (m_clockDirection.getElapsedTime().asSeconds() >= m_maxDirection)
	{
		m_clockDirection.restart();
		randDirection();
	}

	const auto deltaTime = m_clockMove.restart();

	if (m_isRun == true)
		m_sprite.move(m_direction * deltaTime.asSeconds() * 70.f);
	else
	m_sprite.move(m_direction * deltaTime.asSeconds() * SPEED_PER_SECOND);
	m_isRun = false;
}
//===============================================
void EnemyFish::randDirection()
{
	m_direction.y = (rand() / (float)RAND_MAX) * 2.0 - 1.0;
}
//===============================================
void EnemyFish::handleOutOfWorld(sf::Vector2u windowSize)
{
	if (isOutOfWorld(windowSize))
		returnToWorld(windowSize);
}