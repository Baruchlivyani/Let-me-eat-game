#include "Victory.h"

//===============================================
Victory::Victory(sf::Texture& texture, sf::Vector2f location, double_t size, Mood mood) :
	DecorativeObject(texture, location, size, Direction::Right)
{
	m_AnimationData = initAnimationData();
	m_sprite.setTextureRect(m_AnimationData.AnimationDataData().find(mood)->second[0]);
	m_lastMood = m_mood = mood;
	m_isLoop = true;
	location.x < WINDOW_WIDTH / 2 ? m_sprite.rotate(50) : m_sprite.rotate(-45);
}
//===============================================
void Victory::move()
{
	//
	//	//if(m_clockDirection.getElapsedTime().asSeconds() >= m_maxDirection)
	//	//{
	//	//	m_clockDirection.restart();
	//	//	//randDirection();
	//	//}
	//	const auto deltaTime = m_clockMove.restart();
	//	const auto speedPerSecond = 100.f;
	//	m_sprite.move(sf::Vector2f{ 0 ,-1 } *deltaTime.asSeconds() * speedPerSecond);
	//
}
//===============================================
std::vector<details> Victory::initAnimationData()
{

	return std::vector<details>{
		{
			{800, 800},
				11,
			{ 0, 0 },
			{ 10, 0 },
			Mood::VictoryBlue,
		},
				{
			{800, 800},
				11,
			{0, 810},
			{ 10, 0 },
			Mood::VictoryGrin,
				},
					{
			{800, 800},
				11,
			{0, 1620},
			{ 10, 0 },
			Mood::VictoryRed,
					},
						{
			{800, 800},
				11,
			{0, 2430},
			{ 10, 0 },
			Mood::VictoryYellow,
						}
	};
}
//===============================================
sf::FloatRect Victory::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}
//===============================================
//void Victory::handleOutOfWorld(sf::Vector2u windowSize)
//{
//	if (m_sprite.getPosition().y < 0)
//		m_sprite.setPosition(m_sprite.getPosition().x, windowSize.y);
//}

//void Bubble::randDirection()
//{
//}

sf::Clock& Victory::getVictoryClock()
{
	return m_victoryClock;
}

void Victory::setPosition(sf::RenderWindow* m_gameWindow/*, sf::Vector2f location*/)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);

	//auto topLeft = sf::Vector2f(m_gameWindow->getView().getCenter().x - m_gameWindow->getView().getSize().x / 2,
	//	m_gameWindow->getView().getCenter().y - m_gameWindow->getView().getSize().y / 2);
	//m_sprite.setPosition(topLeft + sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 2));
	// 

	


	//sf::Vector2f topLeft = m_gameWindow->getView().getCenter() - m_gameWindow->getView().getSize()/ 2.0f;
	m_sprite.setPosition(m_gameWindow->mapPixelToCoords(sf::Vector2i(m_sprite.getPosition()), m_gameWindow->getView()));

	//m_gameWindow->getView().getCenter()
}







