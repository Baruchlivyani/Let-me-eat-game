#include "Bubble.h"
#include "Factory.h"
//===============================================
static auto registerIt = Factory<DecorativeObject>::instance().registerType(
	ObjectType::Bubble,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<DecorativeObject>
	{
		return std::make_unique<Bubble>(texture, location, size);
	}
);
//===============================================
Bubble::Bubble(sf::Texture& texture, sf::Vector2f location, double_t size) :
	DecorativeObject(texture, location, size, Direction::Up)
{
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Stay)->second[0]);
	m_lastMood = m_mood = Mood::Stay;

}
//===============================================
void Bubble::move()
{
	const auto deltaTime = m_clockMove.restart();
	const auto speedPerSecond = 100.f;
	m_sprite.move(sf::Vector2f{0 ,-1} *deltaTime.asSeconds() * speedPerSecond);

}
//===============================================
std::vector<details> Bubble::initAnimationData()
{

	return std::vector<details>{
		{
			{300, 300},
				1,
			{ 0, 4340 },
			{ 10, 0 },
				Mood::Stay
		},
				{
			{300, 300},
				7,
			{ 0, 4340},
			{ 10, 0 },
			Mood::Bursts
				},
	};
}
//===============================================
sf::FloatRect Bubble::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}
//===============================================
void Bubble::handleOutOfWorld(sf::Vector2u windowSize)
{
		if (m_sprite.getPosition().y < 0)
			m_sprite.setPosition(m_sprite.getPosition().x, windowSize.y);
}






