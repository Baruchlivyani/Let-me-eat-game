#include "LFish.h"
#include "Factory.h"
//===============================================
static auto registerIt = Factory<SmartObject>::instance().registerType(
	ObjectType::LFish,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
	{
		return std::make_unique<LFish>(texture, location, size);
	}
);
//===============================================
LFish::LFish(sf::Texture& texture, sf::Vector2f location, double_t size) :
	EnemyFish(texture, location, size, Direction::Right)
{
	m_fishValue = 20;
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Swim)->second[0]);
}
//===============================================
std::vector<details> LFish::initAnimationData()
{
	return std::vector<details>{
		{
			{300, 300},
				6,
			{ 0, 620 },
			{ 10, 0 },
			Mood::Swim

		},

		{
			{300, 300},
				8,
			{0, 930},
			{10, 0},
			Mood::Eat
		},
	};
	//else
	//return std::vector<details>{
	//		{
	//			{620, 380},
	//				4,
	//			{ 10, 10 },
	//			{ 20, 0 },
	//			Mood::Swim

	//		},

	//	{
	//		{640, 380},
	//			4,
	//		{ 20, 10 },
	//		{ 20, 0 },
	//		Mood::Eat
	//	},
	//};

}
//===============================================
void LFish::handleCollisione(SmartObject& smartObject)
{
	smartObject.handleCollisione(*this);
}
//===============================================
void LFish::handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func)
{
	m_isEaten = false;
}
//===============================================
void LFish::handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func)
{
	m_isEaten = false;
}
//===============================================
void LFish::handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func)
{
	Resources::instance().eatSound();
	m_isEaten = true;
	func(m_fishValue, UPDATE);
}

