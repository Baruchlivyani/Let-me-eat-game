#include "Level6.h"
#include <iostream>
#include "GameController.h"
//===============================================
Level6::Level6() :
	LevelBase(), Button("6", sf::Vector2f(WINDOW_WIDTH * 0.75 +17.f, WINDOW_HEIGHT * 0.87 -4.f), 30)
{
	m_sprite.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 4, WINDOW_HEIGHT * 0.87));
	m_name = "Level 6";
	m_levelText = sf::Text("6", Resources::instance().getArielFont(), 35);
	m_levelText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 4 - 5, WINDOW_HEIGHT * 0.87 - 20));
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	m_levelBehavior = TIMER;
	m_gameTimer = std::make_unique<Timer>(VICTORY_TIME/2);
	m_backround.setTexture(Resources::instance().getBackroundTexture1());

	m_player = (Factory<PlayerFish>::instance().create(ObjectType::PlayerFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), PLAYER_SIZE));

	for (int i = 0; i < 100; i++)
		m_SmartObjects.push_back(Factory<SmartObject>::instance().create(ObjectType::SFish, Resources::instance().getSpriteShit(),
			sf::Vector2f(positionRand()), S_SIZE));

}

std::shared_ptr<LevelBase> Level6::copyMy()
{
	return std::make_shared<Level6>();
}

void Level6::showContentButton(GameController& game, GameBoard& board)
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
