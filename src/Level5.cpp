#include "Level5.h"
#include <iostream>
#include "GameController.h"
//===============================================
Level5::Level5() :
	LevelBase(), Button("5", sf::Vector2f(WINDOW_WIDTH / 2 + 17.f, WINDOW_HEIGHT * 0.87 - 4.f), 30)
{
	m_sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.87 ));

	m_levelBehavior = SCORE;
	m_name = "Level 5";
	m_levelText = sf::Text("5", Resources::instance().getArielFont(), 35);
	m_levelText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT * 0.87 - 20));
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));

	m_backround.setTexture(Resources::instance().getBackroundTexture2());

	m_player = (Factory<PlayerFish>::instance().create(ObjectType::PlayerFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE));

	/*m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::Shark, Resources::instance().getSpriteShit(),
		sf::Vector2f(positionRand()), SHARK_SIZE));*/

	for (int i = 1; i < 4; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::Spikes, Resources::instance().getSpriteShit(),
			sf::Vector2f(WINDOW_WIDTH / 4 * i, WINDOW_HEIGHT+7), SPIKES_SIZE));

	for (int i = 1; i < 7; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::SuddenlySpikes, Resources::instance().getSpriteShit(),
			sf::Vector2f(WINDOW_WIDTH / 7 * i, -PIXEL_SIZE/6), SPIKES_SUDDENLY_SIZE));

	for (int i = 0; i < 2; i++)
		m_SmartObjects.push_back(std::make_unique<Shark>(Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), SHARK_SIZE,
			std::bind(&PlayerFish::getLocation, m_player.get()/*, std::placeholders::_1*/), 55.f));

	for (int i = 0; i < 20; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::SFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), S_SIZE));

	for (int i = 0; i < 8; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::MFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), M_SIZE));

	for (int i = 0; i < 7; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::LFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), L_SIZE));



	/*for (int i = 0; i < 7; i++)*/
	m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::RescueBubble, Resources::instance().getSpriteShit(),
		sf::Vector2f(rand() % int(WINDOW_WIDTH) + 1, rand() % int(WINDOW_HEIGHT) + WINDOW_HEIGHT), RESCUE_BUBBLE_SIZE));


}

std::shared_ptr<LevelBase> Level5::copyMy()
{
	return std::make_shared<Level5>();
}

void Level5::showContentButton(GameController& game, GameBoard& board)
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