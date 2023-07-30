#pragma once
#include "LevelBase.h"
#include "GoMenuButton.h"
#include <SFML/Graphics.hpp>
#include <memory>

//responsible for the game board (-current game stage), printing it,
//changing and managing things related to the game board.

class GameBoard
{

public:
	GameBoard(std::shared_ptr<LevelBase>& level);
	~GameBoard();
	sf::RenderWindow* getWindow() const;
	void resetClocks();
	void print();
	void viewManager();
	void moveObjects();
	void collisioneManager();
	void eatenManager();
	void replaceTexture();
	void outOfWorldManager();
	bool isVictory() const;
	void printVictory();
	bool isLost() const;

	class Growth
	{

	public:
		Growth(GameBoard& board);
		void drow(GameBoard& board);
		void turnOnButton(GameBoard& board);

	private:
		void setTime(GameBoard& board);
		void setScore(GameBoard& board);
		void setGraph(GameBoard& board);
		float_t divideGraph(GameBoard& board) const;
		void updatePosione(GameBoard& board);
		void increaseGraph(GameBoard& board);
		void decreaseGraph(GameBoard& board);
		sf::Text m_text;
		sf::Text m_textScore[2];
		sf::Text m_textTime[2];
		sf::RectangleShape m_graph[2];
		sf::CircleShape m_graphCircles[4];
		std::vector<std::unique_ptr<SmartObject>> m_graphPhotos;
		size_t m_graphScore;
		sf::RectangleShape m_rectScore;
		sf::RectangleShape m_rectTimer;

	};


private:
	Growth m_growth;
	void victoryMood();
	void gameOver();
	void playerEatenManager();
	void objectsEatenManager();
	void handelLimit();
	bool checkLimit(sf::Vector2f direction) const;
	sf::Vector2f calculateViewDirection() const;
	sf::RenderWindow* m_gameWindow;
	std::shared_ptr<LevelBase> m_currentLevel;
	sf::View m_view;
	sf::Clock m_clockView;
	bool m_isOver;
};
