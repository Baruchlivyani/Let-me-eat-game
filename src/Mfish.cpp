#include "MFish.h"
#include "Factory.h"
//===============================================
static auto registerIt = Factory<SmartObject>::instance().registerType(
	ObjectType::MFish,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
	{
		return std::make_unique<MFish>(texture, location, size);
	}
);
//===============================================
MFish::MFish(sf::Texture& texture, sf::Vector2f location, double_t size) :
	EnemyFish(texture, location, size, Direction::Right)
{
	m_fishValue = 10;
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Swim)->second[0]);
}
//===============================================
std::vector<details> MFish::initAnimationData()
{
	return std::vector<details>{
		{
			{300, 300},
				8,
			{0, 2790},
			{10, 0},
			Mood::Swim

		},
		{
			{300, 300},
				8,
			{0, 3100},
			{10, 0},
			Mood::Stay
		},
	};
}
//===============================================
void MFish::handleCollisione(SmartObject& smartObject)
{
	smartObject.handleCollisione(*this);
}
//===============================================
void MFish::handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func)
{
	m_isEaten = false;
}
//===============================================
void MFish::handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func)
{
	Resources::instance().eatSound();
	m_isEaten = true;
	func(m_fishValue, UPDATE);
}
//===============================================
void MFish::handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func)
{
	Resources::instance().eatSound();
	m_isEaten = true;
	func(m_fishValue, UPDATE);
}