#include "SuddenlySpikes.h"
#include "Factory.h"
//===============================================
static auto registerIt = Factory<SmartObject>::instance().registerType(
	ObjectType::SuddenlySpikes,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
	{
		return std::make_unique<SuddenlySpikes>(texture, location, size);
	}
);
//===============================================
SuddenlySpikes::SuddenlySpikes(sf::Texture& texture, sf::Vector2f location, double_t size) :
	SmartObject(texture, location, size, Direction::Right)
{
	m_maxDirection = rand() % (MAX_TIME_DIR - (MIN_TIME_DIR/2) + 1) + MIN_TIME_DIR;
	//m_fishValue = 20;
	//m_clockReplace.restart();
	m_mood = m_lastMood = Mood::Rolling;
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Rolling)->second[0]);
}
//===============================================
std::vector<details> SuddenlySpikes::initAnimationData()
{
	return std::vector<details>{
		/*{
			{300, 300},
				1,
			{ 0, 4960 },
			{ 10, 0 },
			Mood::Stay

		},*/

		{
			{300, 300},
				1,
			{0, 5580},
			{10, 0},
			Mood::Rolling
		},
	};
}
//===============================================
void SuddenlySpikes::move()
{
	m_sprite.rotate(0.75);
	const auto deltaTime = m_clockMove.restart();
	//const auto speedPerSecond = 30.f;
	if (m_clockDirection.getElapsedTime().asSeconds() > m_maxDirection)
	{
		m_sprite.move(sf::Vector2f(0, 1) * deltaTime.asSeconds() * SUDDENLY_SPIKES_SPEED);
	}
}
//===============================================
void SuddenlySpikes::handleCollisione(SmartObject& smartObject)
{
	smartObject.handleCollisione(*this);
}
//===============================================
void SuddenlySpikes::handleOutOfWorld(sf::Vector2u windowSize)
{
	if (m_sprite.getPosition().y > windowSize.y)
	{
		m_clockDirection.restart();
		m_sprite.setPosition(m_sprite.getPosition().x, 0 - m_sprite.getGlobalBounds().height);

	}
}
void SuddenlySpikes::handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func)
{
	func(0, RESETE);
}

void SuddenlySpikes::handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func)
{
	func(S_GROWTH / 2, RESETE);
}

void SuddenlySpikes::handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func)
{
	func(M_GROWTH / 2, RESETE);
}


//void Spikes::handleCollisione(eatS& smartObject, std::function<void(size_t)> func)
//{
//	m_isEaten = false;
//}
////===============================================
//void LFish::handleCollisione(eatM& smartObject, std::function<void(size_t)> func)
//{
//	m_isEaten = false;
//}
////===============================================
//void LFish::handleCollisione(eatL& smartObject, std::function<void(size_t)> func)
//{
//	m_isEaten = true;
//	func(m_fishValue);
//}

