#include "GameObject.h"
//===============================================
GameObject::GameObject(sf::Texture& texture, sf::Vector2f location) :
	m_sprite(texture ,sf::IntRect(0, 0, 300, 300)), m_index(0),
	m_mood(Mood::Swim),m_lastMood(Mood::Swim), m_isLoop(true)
{
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2,
		m_sprite.getGlobalBounds().height / 2));
	m_sprite.setPosition(location);
	m_sprite.setScale(sf::Vector2f(PIXEL_SIZE / m_sprite.getGlobalBounds().width,
		PIXEL_SIZE / m_sprite.getGlobalBounds().height));
}
//===============================================
GameObject::GameObject(sf::Texture& texture, sf::Vector2f location, double_t size, Direction directionm) :
	GameObject(texture, location)
{
	m_RoL = directionm;
	m_sprite.scale(size  *0.5, size *0.5);
}
//===============================================
void GameObject::drow(sf::RenderWindow* window) const
{
	window->draw(m_sprite);
}
//===============================================
bool GameObject::isOutOfWorld(sf::Vector2u WindowSize)
{
	return (m_sprite.getPosition().x < 0 ||
		m_sprite.getPosition().x > WindowSize.x ||
		m_sprite.getPosition().y < 0 ||
		m_sprite.getPosition().y > WindowSize.y);
};
//===============================================
void GameObject::replaceTexture()
{
	if (m_clockReplace.getElapsedTime().asSeconds() > REPLACE_TIME)
	{
		m_clockReplace.restart();
		m_index %= m_AnimationData.AnimationDataData().find(m_mood)->second.size();
		m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(m_mood)->second[m_index++]);

		if (m_index >= m_AnimationData.AnimationDataData().find(m_mood)->second.size() && !m_isLoop)
			updateMood(m_lastMood, true);
	}
}
//===============================================
void GameObject::replaceSide(Direction direction)
{
	if (m_RoL != direction)
	{
		m_RoL = direction;
		m_sprite.scale(-1, 1);		
	}

	m_direction.x = direction;
}
//===============================================
void GameObject::updateMood(Mood mood, bool isLoop)
{
	if (m_mood != mood)
	{
		m_mood = mood;
		m_index = 0;
	}
	m_isLoop = isLoop;
}
//===============================================
void GameObject::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
//===============================================
void GameObject::returnToWorld(sf::Vector2u windowSize)
{
	if (m_sprite.getPosition().x > windowSize.x + m_sprite.getGlobalBounds().width)
		m_sprite.setPosition(-m_sprite.getGlobalBounds().width, m_sprite.getPosition().y);

	if (m_sprite.getPosition().x < 0 - m_sprite.getGlobalBounds().width)
		m_sprite.setPosition(windowSize.x + m_sprite.getGlobalBounds().width, m_sprite.getPosition().y);

	if (m_sprite.getPosition().y > windowSize.y + m_sprite.getGlobalBounds().height/* - INFORMATION_DISPLAY*/)
		m_sprite.setPosition(m_sprite.getPosition().x, -m_sprite.getGlobalBounds().height);

	if (m_sprite.getPosition().y < 0 - m_sprite.getGlobalBounds().height)
		m_sprite.setPosition(m_sprite.getPosition().x, windowSize.y + m_sprite.getGlobalBounds().height/* - INFORMATION_DISPLAY*/);
}
//===============================================
void GameObject::initClock()
{
	m_clockMove.restart();
	m_clockReplace.restart();
	m_clockMood.restart();
}
