#include "Spikes.h"
#include "Factory.h"
//===============================================
static auto registerIt = Factory<SmartObject>::instance().registerType(
	ObjectType::Spikes,
	[](sf::Texture& texture, sf::Vector2f location, double_t size) -> std::unique_ptr<SmartObject>
	{
		return std::make_unique<Spikes>(texture, location, size);
	}
);
//===============================================
Spikes::Spikes(sf::Texture& texture, sf::Vector2f location, double_t size) :
	SmartObject(texture, location, size, Direction::Right)
{
	//m_fishValue = 20;
	m_clockReplace.restart();
	m_mood = m_lastMood = Mood::Rolling;
	m_sprite.setOrigin(m_sprite.getOrigin().x, m_sprite.getOrigin().y + m_sprite.getGlobalBounds().height + 20);
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(Mood::Rolling)->second[0]);
}
//===============================================
std::vector<details> Spikes::initAnimationData()
{
	return std::vector<details>{
		{
			{300, 300},
				1,
			{ 0, 6200 },
			{ 10, 0 },
				Mood::Stay

		},

		{
			{300, 300},
				9,
			{0, 6200},
			{10, 0},
			Mood::Rolling
		},
	};
}
//===============================================
void Spikes::move()
{
	//const auto deltaTime = m_clockMove.restart();

	//const auto speedPerSecond = 30.f;
	//m_sprite.move(sf::Vector2f(0, 1) * deltaTime.asSeconds() * SUDDENLY_SPIKES_SPEED);


	//m_sprite.setScale(0, -1);
	//צריך לעשות משתנה בוליאני או משהו, וכל פעם הוא יעשה לא שווה לו
}
//===============================================
void Spikes::handleCollisione(SmartObject& smartObject)
{
	//smartObject.handleCollisione(*this);
}
//===============================================
void Spikes::handleCollisione(eatS& smartObject, std::function<void(size_t, Score)> func)
{
	func(0, RESETE);
}

void Spikes::handleCollisione(eatM& smartObject, std::function<void(size_t, Score)> func)
{
	func(S_GROWTH/2, RESETE);
}
void Spikes::handleCollisione(eatL& smartObject, std::function<void(size_t, Score)> func)
{
	func(M_GROWTH - (M_GROWTH - S_GROWTH)/2, RESETE);
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

