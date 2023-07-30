#include "Level1.h"
#include <iostream>
#include "GameController.h"
//===============================================
Level1::Level1() :
	LevelBase() ,Button("1", sf::Vector2f(WINDOW_WIDTH/4 + 19.f, WINDOW_HEIGHT* 0.60 -4.f), 30)
{
	m_sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT * 0.60));
	m_levelBehavior = SCORE;
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	m_name = "Level 1";
	m_levelText = sf::Text("1", Resources::instance().getArielFont(), 35);
	m_levelText.setPosition(sf::Vector2f(WINDOW_WIDTH / 4 - 5, WINDOW_HEIGHT * 0.60 - 20));
	m_backround.setTexture(Resources::instance().getBackroundTexture2());

	m_player = (Factory<PlayerFish>::instance().create(ObjectType::PlayerFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE));

	/*m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::Shark, Resources::instance().getSpriteShit(),
		sf::Vector2f(positionRand()), SHARK_SIZE));*/

	for (int i = 1; i < 4; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::Spikes, Resources::instance().getSpriteShit(),
			sf::Vector2f(WINDOW_WIDTH/4*i, WINDOW_HEIGHT+7), SPIKES_SIZE));

	m_SmartObjects.push_back(std::make_unique<Shark>(Resources::instance().getSpriteShit(),
		sf::Vector2f(positionRand()), SHARK_SIZE,
		std::bind(&PlayerFish::getLocation, m_player.get()/*, std::placeholders::_1*/), 35.f));

	for (int i = 0; i < 50; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::SFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), S_SIZE));

	for (int i = 0; i < 8; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::MFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), M_SIZE));

	for (int i = 0; i < 5; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::LFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), L_SIZE));

	

	/*for (int i = 0; i < 7; i++)*/
	m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::RescueBubble, Resources::instance().getSpriteShit(),
		sf::Vector2f(rand() % int(WINDOW_WIDTH) + 1, rand() % int(WINDOW_HEIGHT) + WINDOW_HEIGHT), RESCUE_BUBBLE_SIZE));

	m_mood = Mood::unLocked;
	m_sprite.setTextureRect(m_animation.AnimationDataData().find(m_mood)->second[0]);

}

std::shared_ptr<LevelBase> Level1::copyMy()
{
	return std::make_shared<Level1>();
}

void Level1::showContentButton(GameController& game, GameBoard& board)
{
	if (m_buttonOn)
	{
		std::shared_ptr<LevelBase> sharedPtr(this);
		m_buttonOn = false;
		board.getWindow()->close();
		game.startGame(sharedPtr);
		handelExit(game);
	}
}

void Level1::drowButtons(sf::RenderWindow* menuWindow)
{
	drowButton(menuWindow);
}


size_t Level1::numOfLevel() const
{ 
	return 1; 
};