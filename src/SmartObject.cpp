#include "SmartObject.h"
#include "Spikes.h"
#include <typeinfo>
//===============================================
SmartObject::SmartObject(sf::Texture& texture, sf::Vector2f location) :
	GameObject(texture, location), m_isEaten(false), m_isEat(false){}
//===============================================
SmartObject::SmartObject(sf::Texture& texture, sf::Vector2f location, double_t size, Direction directionm):
	GameObject(texture, location , size, directionm), m_isEaten(false), m_isEat(false) {}
//===============================================
bool SmartObject::isCollisione(SmartObject& smartObject)
{
	//return (m_sprite.getGlobalBounds().intersects(smartObject.getMouthBounds()));
	//Button* ptr = dynamic_cast<Button*>(item.get);
	//if(typeid(Spikes) == typeid(smartObject))
	
	return (getMouthBounds().intersects(typeid(Spikes) == typeid(smartObject) ?
		smartObject.getSmallerBounds()
		: smartObject.m_sprite.getGlobalBounds()));
}
//===============================================
sf::FloatRect SmartObject::getSmallerBounds() const
{
	sf::FloatRect spriteBounds = m_sprite.getGlobalBounds();
	sf::Vector2f spritePosition = m_sprite.getPosition();

	return sf::FloatRect(sf::Vector2f(spritePosition.x + spriteBounds.width/2 -50.f,
		spritePosition.y - spriteBounds.height), sf::Vector2f(spriteBounds.width * 0.15,
			spritePosition.y - spriteBounds.height));
}

sf::FloatRect SmartObject::getMouthBounds() const
{
	return sf::FloatRect(sf::Vector2f(m_RoL == Direction::Right ? 
		m_sprite.getPosition().x + m_sprite.getGlobalBounds().width * MOUTH_SIZE * 3 :
		m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * MOUTH_SIZE * 3
		,m_sprite.getPosition().y),
		sf::Vector2f(m_sprite.getGlobalBounds().width * MOUTH_SIZE, m_sprite.getGlobalBounds().height * MOUTH_SIZE));
}
//===============================================
bool SmartObject::isAroundCollisione(SmartObject& smartObject)
{
	return (getAroundBounds().intersects(smartObject.m_sprite.getGlobalBounds()));
}
//===============================================
sf::FloatRect SmartObject::getAroundBounds() const
{
	sf::FloatRect spriteBounds = m_sprite.getGlobalBounds();
	sf::Vector2f spritePosition = m_sprite.getPosition();

	return sf::FloatRect(sf::Vector2f(spritePosition.x - spriteBounds.width, 
		spritePosition.y - spriteBounds.height), sf::Vector2f(spriteBounds.width * 1.5,
			spritePosition.y - spriteBounds.height));
}
//===============================================
sf::Vector2f SmartObject::getLocation() const
{
	return m_sprite.getPosition();
}
//===============================================
void SmartObject::setEat()
{
	m_isEat = true;
}

bool SmartObject::isEaten()
{
	return m_isEaten;
}
//===============================================
void SmartObject::blink()
{
	if (m_isEat && m_clockBlink.getElapsedTime().asSeconds() > 0.3)
	{
		if (m_sprite.getColor().a == 255)
			m_sprite.setColor(sf::Color::Color(m_sprite.getColor().r,
				m_sprite.getColor().g, m_sprite.getColor().b, 100));
		else
			m_sprite.setColor(sf::Color::Color(m_sprite.getColor().r,
				m_sprite.getColor().g, m_sprite.getColor().b, 255));

		m_clockBlink.restart();
	}
}

void SmartObject::restart()
{
	m_isEaten = false;
	m_sprite.setPosition(m_direction.x > 0 ? - m_sprite.getGlobalBounds().width : 
		WINDOW_WIDTH + m_sprite.getGlobalBounds().width, rand() % int(WINDOW_HEIGHT) + 1);
}

void SmartObject::victoryMood()
{
	const auto deltaTime = m_clockMove.restart();
	m_sprite.move(m_direction * deltaTime.asSeconds() * SPEED_PER_SECOND * 10.f);
}

