#include "RescueBubble.h"
#include "Factory.h"
#include "PlayerFish.h"
//===============================================
static auto registerIt = Factory<SmartObject>::instance().registerType(
	ObjectType::RescueBubble,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
	{
		return std::make_unique<RescueBubble>(texture, location, size);
	}
);
//===============================================
RescueBubble::RescueBubble(sf::Texture& texture, sf::Vector2f location, double_t size) :
	SmartObject(texture, location, size, Direction::Up), m_isProtector(false)
{
	m_maxDirection = 60;
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Swim)->second[0]);
}
//===============================================
void RescueBubble::handleCollisione(SmartObject& smartObject)
{
	smartObject.handleCollisione(*this);
}
//===============================================
void RescueBubble::handleCollisione(PlayerFish& player, std::function<sf::Vector2f()> func)
{
	if (!m_isEaten)
	{
		m_getPlayerLcocation = func;
		m_isProtector = true;
		player.setProtectedOff(std::bind(&RescueBubble::burstBubble, this));
		m_sprite.setScale(player.getScale() + sf::Vector2f(player.getScale().x / 3, player.getScale().y / 3));
	}
}
//===============================================
void RescueBubble::burstBubble()
{
	m_isProtector = false;
	updateMood(Mood::Bursts, false);
	m_isEaten = true;

}
//===============================================
void RescueBubble::restart()
{
	return;
}
//===============================================
void RescueBubble::move()
{
	if (m_mood != Mood::Bursts && m_isEaten)
		m_sprite.setPosition(-m_sprite.getPosition());

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	if (m_mood != Mood::Bursts)
		m_sprite.rotate(1);
	const auto deltaTime = m_clockMove.restart();
	const auto speedPerSecond = 100.f;
	
	if (m_isProtector)
		m_sprite.setPosition(m_getPlayerLcocation());
	else
		m_sprite.move(sf::Vector2f{ 0 ,-1 } *deltaTime.asSeconds() * speedPerSecond);
}
//===============================================
std::vector<details> RescueBubble::initAnimationData()
{

	return std::vector<details>{
		{
			{300, 300},
				1,
			{ 0, 4340 },
			{ 10, 0 },
				Mood::Swim
		},
{
{300, 300},
7,
{ 0, 4340 },
{ 10, 0 },
Mood::Bursts
},
	};
}
//===============================================
sf::FloatRect RescueBubble::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}
//===============================================
void RescueBubble::handleOutOfWorld(sf::Vector2u windowSize)
{
	if (m_sprite.getPosition().y < 0)
	{
		m_isEaten = false;
		m_clockDirection.restart();
		m_sprite.setPosition(rand() % int(WINDOW_WIDTH) + 1, windowSize.y);
	}
}