#include "SFish.h"
#include "Factory.h"
//===============================================
static auto registerIt = Factory<SmartObject>::instance().registerType(
	ObjectType::SFish,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
	{
		return std::make_unique<SFish>(texture, location, size);
	}
);
//===============================================
SFish::SFish(sf::Texture& texture, sf::Vector2f location, double_t size):
	EnemyFish(texture, location, size, Direction::Left)
{
	m_fishValue = 5;
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Swim)->second[0]);
}
//===============================================
std::vector<details> SFish::initAnimationData()
{
	/*SmallFishRand randFish = static_cast<SmallFishRand>(SMALL_FISH_1 + rand() % (SMALL_FISH_4 - SMALL_FISH_1 + 1));
	int correctFish = static_cast<int>(randFish);*/

	return std::vector<details>{
		{
			{300, 300},
				24,
			{ 0, randFish()},
			{ 10, 0 },
			Mood::Swim
		},
	};
}
//===============================================
void SFish::handleCollisione(SmartObject& smartObject)
{
	smartObject.handleCollisione(*this);
}
//===============================================
void SFish::handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func)
{
	Resources::instance().eatSound();
	m_isEaten = true;
	func(m_fishValue, UPDATE);
}
//===============================================
void SFish::handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func)
{
	Resources::instance().eatSound();
	m_isEaten = true;
	func(m_fishValue, UPDATE);
}
//===============================================
void SFish::handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func)
{
	Resources::instance().eatSound();
	m_isEaten = true;
	func(m_fishValue, UPDATE);
}
//===============================================
void SFish::ranAway(SmartObject& player)
{
	m_direction.x = m_sprite.getPosition().x > player.getLocation().x ? 1 : -1;
	m_direction.y = m_sprite.getPosition().y > player.getLocation().y ? 1 : -1;
	replaceSide(Direction(m_direction.x));
	m_isRun = true;
}
//===============================================
int SFish::randFish() const
{
	size_t SmallFishRand[] = { SMALL_FISH_1, SMALL_FISH_2, SMALL_FISH_3, SMALL_FISH_4, SMALL_FISH_5 };
	return SmallFishRand[rand() % sizeof(SmallFishRand) / sizeof(SmallFishRand[0])];
}

