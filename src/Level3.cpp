#include "Level3.h"
#include <iostream>
#include "GameController.h"
//===============================================
Level3::Level3():
	LevelBase(), Button("3", sf::Vector2f(WINDOW_WIDTH *0.75 + 17.f, WINDOW_HEIGHT * 0.60 -4.f), 30)
{
	m_sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 4, WINDOW_HEIGHT * 0.60));
	m_name = "Level 3";
	m_levelText = sf::Text("3", Resources::instance().getArielFont(), 35);
	m_levelText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 4 - 5, WINDOW_HEIGHT * 0.60 - 20));
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	m_levelBehavior = TIMER;
	m_gameTimer = std::make_unique<Timer>(VICTORY_TIME);
	m_backround.setTexture(Resources::instance().getBackroundTexture2());

	m_player = (Factory<PlayerFish>::instance().create(ObjectType::PlayerFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE));

	for (int i = 0; i < 100; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::SFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), S_SIZE));

}

std::shared_ptr<LevelBase> Level3::copyMy()
{
	return std::make_shared<Level3>();
}

void Level3::showContentButton(GameController& game, GameBoard& board)
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
