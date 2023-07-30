#include "LevelBase.h"
#include "Define.h"
#include <iostream>
#include "GameController.h"

const int SIZE = 560;
LevelBase::LevelBase() :
	m_isFinish(false), m_isFails(false),
	m_sprite(Resources::instance().getIconsTexture(), sf::IntRect(0, 0, SIZE, SIZE))
{
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2,
		m_sprite.getGlobalBounds().height / 2));
	//m_sprite.setTexture(texture);
	//m_sprite.setScale(50, 50);
	m_sprite.setScale(sf::Vector2f(SIZE / m_sprite.getGlobalBounds().width,
		SIZE / m_sprite.getGlobalBounds().height));

	m_sprite.scale(0.35, 0.35);
	//m_levelText.setCharacterSize(35);
	m_levelText.setFillColor(sf::Color::Blue);
	m_levelText.setOrigin(m_levelText.getGlobalBounds().width/2, m_levelText.getGlobalBounds().height / 2);

	m_victory.emplace_back(Resources::instance().getVictoryTexture(), sf::Vector2f(200, VIEW_HEIGHT / 3),
		double_t(1), Mood::VictoryBlue);
	m_victory.emplace_back(Resources::instance().getVictoryTexture(), sf::Vector2f(200, VIEW_HEIGHT / 3.5),
		double_t(0.8), Mood::VictoryRed);
	m_victory.emplace_back(Resources::instance().getVictoryTexture(), sf::Vector2f(830, VIEW_HEIGHT / 1.3),
		double_t(0.8), Mood::VictoryYellow);
	m_victory.emplace_back(Resources::instance().getVictoryTexture(), sf::Vector2f(830, VIEW_HEIGHT / 1.5),
		double_t(0.5), Mood::VictoryGrin);

	for (int i = 0; i < 30; i++)
		m_DecorativeObjects.push_back(Factory<DecorativeObject>::instance().create(ObjectType::Bubble, Resources::instance().getSpriteShit(),
			sf::Vector2f(rand() % int(WINDOW_WIDTH) + 1, rand() % int(WINDOW_HEIGHT) + WINDOW_HEIGHT), (rand() / (float)RAND_MAX) * BUbBLE_SIZE - 0.083));

	m_animation = initAnimationData();
	m_mood = Mood::locked;
	m_sprite.setTextureRect(m_animation.AnimationDataData().find(m_mood)->second[0]);
}
//===============================================
std::shared_ptr<LevelBase> LevelBase::copyMy()
{
	return std::shared_ptr<LevelBase>();
};

sf::Sprite& LevelBase::getBackround()
{
	return m_backround;
}
//===============================================
std::unique_ptr<PlayerFish>& LevelBase::getFish()
{
	return m_player;
}
//===============================================
//std::unique_ptr<Shark>& LevelBase::getShark()
//{
//	return m_shark;
//}

std::vector<std::unique_ptr<SmartObject>>::iterator&& LevelBase::smartBeginVec()
{
	return m_SmartObjects.begin();
}
//===============================================
std::vector<std::unique_ptr<SmartObject>>::iterator&& LevelBase::smartEndVec()
{
	return m_SmartObjects.end();
}
//===============================================
std::vector<std::unique_ptr<DecorativeObject>>::iterator&& LevelBase::DecorBeginVec()
{
	return m_DecorativeObjects.begin();
}
//===============================================
std::vector<std::unique_ptr<DecorativeObject>>::iterator&& LevelBase::DecorEndVec()
{
	return m_DecorativeObjects.end();
}


//std::vector <std::unique_ptr<SmartObject>>& LevelBase::getSmartObjects()
//{
//	return m_SmartObjects;
//}

void LevelBase::erase(int index)
{
	m_SmartObjects.erase(m_SmartObjects.begin() + index);
}

sf::Vector2f LevelBase::positionRand() const
{
	sf::Vector2f position;

	do
	{
		position.x = rand() % int(WINDOW_WIDTH) + 1;
		position.y = rand() % int(WINDOW_HEIGHT) + 1;

	} while ((!((position.x > 0) && (position.x < MID_VIEW.x - VIEW_WIDTH / 2)) &&
		!((position.x > MID_VIEW.x + VIEW_WIDTH / 2) && (position.x < WINDOW_WIDTH))) &&
		(!((position.y > 0) && (position.y < MID_VIEW.y - VIEW_HEIGHT / 2)) &&
			!((position.y > MID_VIEW.y + VIEW_HEIGHT / 2) && (position.y < WINDOW_HEIGHT))));

	return position;
}

void LevelBase::resete()
{

	std::for_each(smartBeginVec(), smartEndVec(), [this](auto& i)
		{
			i->restart();
	i->setPosition(positionRand());
		});

	m_player->restart();
}

std::string LevelBase::getName() const
{
	return m_name;
}

bool LevelBase::isFinish() const
{
	return m_isFinish;
}

bool LevelBase::isFails() const
{
	return m_isFails;
}

void  LevelBase::setFinish(bool ToF)
{
	m_isFinish = ToF;
}

void LevelBase::setFails(bool ToF) 
{
	m_isFails = ToF;
}

LevelBehavior LevelBase::levelBehavior() const
{
	return m_levelBehavior;
}

std::unique_ptr<Timer>& LevelBase::getTimer()
{
	return m_gameTimer;
}

std::vector<details> LevelBase::initAnimationData()
{
	return std::vector<details>{
		{
			{SIZE, SIZE},
				1,
			{ 0, 540 },
			{ 20, 0 },
				Mood::unLocked

		},
		{
			{SIZE, SIZE},
				1,
			{SIZE + 20, 540},
			{20, 0},
			Mood::locked
		},
	};
}

Mood LevelBase::getStatus()
{
	return m_mood;
}

void LevelBase::handelExit(GameController& game)
{
	if (game.isExit())
		exit(EXIT_SUCCESS);
}

void LevelBase::setStatus(Mood mood)
{
	m_mood = mood;
	m_sprite.setTextureRect(m_animation.AnimationDataData().find(m_mood)->second[0]);

}

void LevelBase::drowIcon(sf::RenderWindow* menuWindow)
{
	menuWindow->draw(m_sprite);
	if(m_mood == Mood::unLocked)
	menuWindow->draw(m_levelText);
}
