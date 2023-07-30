#include "GameBoard.h"
#include "Level1.h"
#include "Define.h"
#include <iostream>
//===============================================
GameBoard::GameBoard(std::shared_ptr<LevelBase>& level) :
	m_currentLevel(level), m_view(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT)),
	m_growth(*this), m_isOver(false)

{
	m_gameWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), level->getName());
	m_gameWindow->setView(m_view);
	m_currentLevel->setStatus(Mood::unLocked);
}
//===============================================
GameBoard::~GameBoard()
{
	delete(m_gameWindow);
}
//===============================================
sf::RenderWindow* GameBoard::getWindow() const
{
	return m_gameWindow;
}
//===============================================
void GameBoard::print()
{
	m_gameWindow->draw(m_currentLevel->getBackround());

	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			i->drow(m_gameWindow);
		});

	std::for_each(m_currentLevel->DecorBeginVec(), m_currentLevel->DecorEndVec(), [this](auto& i)
		{
			i->drow(m_gameWindow);
		});

	m_currentLevel->getFish()->drow(m_gameWindow);

	m_growth.drow(*this);

}
//===============================================
//Resets all clocks that started counting from the start of the game
//===============================================
void GameBoard::resetClocks()
{
	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			i->initClock();
		});

	std::for_each(m_currentLevel->DecorBeginVec(), m_currentLevel->DecorEndVec(), [this](auto& i)
		{
			i->initClock();
		});
}
//===============================================
//Handles the case that objects have left the game board
//===============================================
void GameBoard::outOfWorldManager()
{
	m_currentLevel->getFish()->handleOutOfWorld(m_gameWindow->getSize());

	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			i->handleOutOfWorld(m_gameWindow->getSize());
		});

	std::for_each(m_currentLevel->DecorBeginVec(), m_currentLevel->DecorEndVec(), [this](auto& i)
		{
			i->handleOutOfWorld(m_gameWindow->getSize());
		});
}
//===============================================
bool GameBoard::isVictory() const
{
	return m_currentLevel->levelBehavior() == SCORE ?
		m_currentLevel->getFish()->getScore() >= VICTORY :
		m_currentLevel->getFish()->getScore() >= VICTORY_TIMER_SCORE;
}
//===============================================
void GameBoard::printVictory()
{
	Resources::instance().victorySound();
	m_currentLevel->victoryVec()[0].getVictoryClock().restart();
	m_currentLevel->setStatus(Mood::unLocked);

	for (auto& i : m_currentLevel->victoryVec())
	{
		i.setPosition(m_gameWindow);

	}
	while (m_gameWindow->isOpen() &&
		m_currentLevel->victoryVec()[0].getVictoryClock().getElapsedTime().asSeconds() < 10)
	{
		victoryMood();
	}
	m_currentLevel->setFinish(true);
}
//===============================================
//Handles all collisions
//===============================================
void GameBoard::collisioneManager()
{

	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			if (i->isCollisione(*m_currentLevel->getFish()))
			i->handleCollisione(*m_currentLevel->getFish());

	if (m_currentLevel->getFish()->isCollisione(*i))
		m_currentLevel->getFish()->handleCollisione(*i);
		});
	m_currentLevel->getFish()->blink();

	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			if (i->isAroundCollisione(*m_currentLevel->getFish()))
			i->ranAway(*m_currentLevel->getFish());
		});

}
//===============================================
void GameBoard::replaceTexture()
{
	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			i->replaceTexture();
		});
	m_currentLevel->getFish()->replaceTexture();
}
//===============================================
void GameBoard::eatenManager()
{
	playerEatenManager();
	objectsEatenManager();
}
//===============================================
void GameBoard::playerEatenManager()
{
	if (m_currentLevel->getFish()->isEaten() ||
		m_currentLevel->levelBehavior() == TIMER && m_currentLevel->getTimer()->isEndTime())
		gameOver();
}
//===============================================
void GameBoard::objectsEatenManager()
{

	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [](auto& i)
		{
			if (i->isEaten())
			i->restart();
		});

}
//===============================================
void GameBoard::moveObjects()
{
	m_currentLevel->getFish()->move();
	m_currentLevel->getFish()->moveByMouse(m_gameWindow);

	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [](auto& i)
		{
			i->move();
		});

	std::for_each(m_currentLevel->DecorBeginVec(), m_currentLevel->DecorEndVec(), [](auto& i)
		{
			i->move();
		});
}
//===============================================
void GameBoard::viewManager()
{
	sf::Vector2f direction = calculateViewDirection();

	if (checkLimit(direction))
		m_view.move(direction);
	m_gameWindow->setView(m_view);
	handelLimit();
}
//===============================================
//Handles the presentation of the world in case the player
//moves in one of the directions, then the world moves accordingly
//===============================================
void GameBoard::handelLimit()
{
	sf::FloatRect backgroundBounds = m_currentLevel->getBackround().getLocalBounds(),
		viewBounds(m_view.getCenter() - m_view.getSize(), m_view.getSize());

	float minX = backgroundBounds.left + viewBounds.width / 2.0f,
		maxX = backgroundBounds.left + backgroundBounds.width - viewBounds.width / 2.0f /*- 5.0f*/,
		minY = backgroundBounds.top + viewBounds.height / 2.0f /*+ 5.0f*/,
		maxY = backgroundBounds.top + backgroundBounds.height - viewBounds.height / 2.0f/* - 5.0f*/;

	sf::Vector2f viewCenter = m_view.getCenter();
	m_view.setCenter(sf::Vector2f((std::clamp(viewCenter.x, minX, maxX)), (std::clamp(viewCenter.y, minY, maxY))));
}
//===============================================
bool GameBoard::checkLimit(sf::Vector2f direction) const
{
	sf::Vector2i pixelToCoord = m_gameWindow->mapCoordsToPixel(m_currentLevel->getFish()->getLocation(), m_view);

	return ((pixelToCoord.x < m_gameWindow->getSize().x / 3 && direction.x < 0) ||
		(pixelToCoord.x > (m_gameWindow->getSize().x / 3) * 2 && direction.x > 0) ||
		(pixelToCoord.y < m_gameWindow->getSize().y / 3 && direction.y < 0) ||
		(pixelToCoord.y > (m_gameWindow->getSize().y / 3) * 2 && direction.y > 0));

}
//===============================================
sf::Vector2f GameBoard::calculateViewDirection() const
{
	return sf::Vector2f(m_currentLevel->getFish()->getLocation().x - m_currentLevel->getFish()->getLastLocation().x,
		m_currentLevel->getFish()->getLocation().y - m_currentLevel->getFish()->getLastLocation().y);
}
//===============================================
//Prints a nice indication to the user in case he is disqualified
//===============================================
void GameBoard::gameOver()
{
	Resources::instance().gameOverSound();
	auto gameOver = sf::Text(" GAME\n OVER", Resources::instance().getArielFont(), 50);
	auto rectGameOver = sf::RectangleShape(m_view.getSize() / 3.f);
	rectGameOver.setPosition(m_gameWindow->getView().getCenter());
	rectGameOver.setOrigin(rectGameOver.getGlobalBounds().width / 2,
		rectGameOver.getGlobalBounds().height / 2);
	gameOver.setPosition(rectGameOver.getPosition());
	gameOver.setOrigin(rectGameOver.getGlobalBounds().width / 2,
		rectGameOver.getGlobalBounds().height / 2);
	rectGameOver.setFillColor(sf::Color(255, 255, 255, 100));
	gameOver.setFillColor(sf::Color::Red);

	m_currentLevel->victoryVec()[0].getVictoryClock().restart();
	while (m_gameWindow->isOpen() &&
		m_currentLevel->victoryVec()[0].getVictoryClock().getElapsedTime().asSeconds() < 5)
	{
		m_gameWindow->clear();

		m_gameWindow->draw(m_currentLevel->getBackround());

		std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
			{
				i->blink();
		i->drow(m_gameWindow);
			});
		std::for_each(m_currentLevel->DecorBeginVec(), m_currentLevel->DecorEndVec(), [this](auto& i)
			{
				i->move();
		i->handleOutOfWorld(m_gameWindow->getSize());
		i->drow(m_gameWindow);
			});
		m_growth.drow(*this);
		replaceTexture();
		m_gameWindow->draw(gameOver);
		m_gameWindow->draw(rectGameOver);

		m_gameWindow->display();
	}
	m_isOver = true;
	m_currentLevel->setFails(true);
}
bool GameBoard::isLost() const
{
	return m_isOver;
}
//===============================================
void GameBoard::victoryMood()
{
	m_gameWindow->clear();
	std::for_each(m_currentLevel->smartBeginVec(), m_currentLevel->smartEndVec(), [this](auto& i)
		{
			i->victoryMood();
		});
	std::for_each(m_currentLevel->DecorBeginVec(), m_currentLevel->DecorEndVec(), [this](auto& i)
		{
			i->move();
	i->handleOutOfWorld(m_gameWindow->getSize());
		});

	m_currentLevel->getFish()->move();
	print();
	replaceTexture();
	for (auto& i : m_currentLevel->victoryVec())
	{
		i.drow(m_gameWindow);
		i.replaceTexture();
	}
	m_gameWindow->display();
}
