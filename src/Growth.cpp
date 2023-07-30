#include "GameBoard.h"
//===============================================
GameBoard::Growth::Growth(GameBoard& board) :
	m_text("GROWTH", Resources::instance().getArielFont(), GRAPH_SIZE),
	m_graphScore(0)
{

	setTime(board);
	setScore(board);
	setGraph(board);




	m_rectTimer = sf::RectangleShape(SCORE_LENGTH);
	m_rectTimer.setFillColor(sf::Color(0, 0, 0, 100));

	m_rectScore = sf::RectangleShape(SCORE_LENGTH);
	m_rectScore.setFillColor(sf::Color(0, 0, 0, 100));
	m_text.setFillColor(sf::Color::Red);

	m_graphCircles[0] = sf::CircleShape(8, 3);
	m_graphCircles[0].setOrigin(sf::Vector2f(m_graphCircles[0].getGlobalBounds().width / 2,
		m_graphCircles[0].getGlobalBounds().height / 2));
	m_graphCircles[0].setFillColor(sf::Color::Red);


	m_graphCircles[1] = m_graphCircles[0];

	m_graphPhotos.push_back(Factory<SmartObject>::instance().create(ObjectType::SFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(m_graph[0].getPosition().x, m_graph[0].getPosition().y - 30), S_SIZE * 0.75));

	m_graphPhotos.push_back(Factory<SmartObject>::instance().create(ObjectType::MFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(m_graphCircles[0].getPosition().x, m_graph[0].getPosition().y - 25), M_SIZE * 0.75));

	m_graphPhotos.push_back(Factory<SmartObject>::instance().create(ObjectType::LFish, Resources::instance().getSpriteShit(),
		sf::Vector2f(m_graphCircles[1].getPosition().x, m_graph[0].getPosition().y - 32), L_SIZE / 2));

}
//===============================================
void GameBoard::Growth::drow(GameBoard& board)
{

	updatePosione(board);

	if (board.m_currentLevel->getFish()->getScore() < m_graphScore)
		decreaseGraph(board);
	else
		increaseGraph(board);


	board.m_gameWindow->draw(m_text);
	board.m_gameWindow->draw(m_rectScore);
	board.m_gameWindow->draw(m_textScore[0]);
	board.m_gameWindow->draw(m_textScore[1]);
	board.m_gameWindow->draw(m_graph[0]);
	board.m_gameWindow->draw(m_graph[1]);

	if (board.m_currentLevel->levelBehavior() == SCORE)
	{
		board.m_gameWindow->draw(m_graphCircles[0]);
		board.m_gameWindow->draw(m_graphCircles[1]);
		for (int i = 0; i < m_graphPhotos.size(); ++i)
			m_graphPhotos[i]->drow(board.m_gameWindow);
	}
	else
	{
		int(board.m_currentLevel->getTimer()->countingDown()) % 60 >= 10 ? m_textTime[1].setString
		(std::to_string(int(board.m_currentLevel->getTimer()->countingDown() / 60)) + ':' +
			std::to_string(int(board.m_currentLevel->getTimer()->countingDown()) % 60))
			: m_textTime[1].setString( std::to_string(int(board.m_currentLevel->getTimer()->countingDown() / 60)) + ":0" + 
				std::to_string(int(board.m_currentLevel->getTimer()->countingDown()) % 60));

		board.m_gameWindow->draw(m_rectTimer);
		board.m_gameWindow->draw(m_textTime[0]);
		board.m_gameWindow->draw(m_textTime[1]);
	}

	
}
//===============================================
void GameBoard::Growth::updatePosione(GameBoard& board)
{
	auto topLeft = sf::Vector2f(board.m_view.getCenter().x - board.m_view.getSize().x / 2,
		board.m_view.getCenter().y - board.m_view.getSize().y / 2);
	m_text.setPosition(topLeft.x + 10, topLeft.y + 30);

	m_textScore[0].setPosition(sf::Vector2f(topLeft.x + board.m_view.getSize().x * 0.8, topLeft.y + 30));
	m_rectScore.setPosition(sf::Vector2f(m_textScore[0].getPosition().x + m_textScore[0].getGlobalBounds().width + 10,
		m_text.getPosition().y + 3));


	m_textScore[1].setPosition(m_rectScore.getPosition().x + 5/*m_rectScore.getGlobalBounds().width * 0.75*/
		,m_rectScore.getPosition().y - 3);


	m_textTime[0].setPosition(board.m_view.getCenter().x + 30, m_textScore[0].getPosition().y);
	m_rectTimer.setPosition(sf::Vector2f(m_textTime[0].getPosition().x + m_textTime[0].getGlobalBounds().width + 10,
		m_text.getPosition().y + 3));
	m_textTime[1].setPosition(m_rectTimer.getPosition().x + 5/*m_rectScore.getGlobalBounds().width * 0.75*/
		, m_rectTimer.getPosition().y - 3);
	
	m_graph[0].setPosition(m_text.getPosition().x + m_text.getGlobalBounds().width * 1.2, m_text.getPosition().y + 7);
	m_graph[1].setPosition(m_graph[0].getPosition());

	m_graphCircles[0].setPosition(m_graph[0].getPosition().x + m_graph[0].getGlobalBounds().width / 3,
		m_graph[0].getPosition().y + m_graph[0].getGlobalBounds().height + m_graphCircles[0].getGlobalBounds().height / 2);
	m_graphCircles[1].setPosition(m_graph[0].getPosition().x + m_graph[0].getGlobalBounds().width / 3 * 2,
		m_graphCircles[0].getPosition().y);

	m_graphPhotos[0]->setPosition(sf::Vector2f(m_graph[0].getPosition().x + 30, m_graph[0].getPosition().y - 15));
	m_graphPhotos[1]->setPosition(sf::Vector2f(m_graphCircles[0].getPosition().x + 30, m_graph[0].getPosition().y - 19));
	m_graphPhotos[2]->setPosition(sf::Vector2f(m_graphCircles[1].getPosition().x + m_graph[0].getGlobalBounds().width / 6, m_graph[0].getPosition().y - 10));
}
//===============================================
void GameBoard::Growth::increaseGraph(GameBoard& board)
{
	m_textScore[1].setString(std::to_string(board.m_currentLevel->getFish()->getScore()));

	if (m_graph[1].getSize().x < m_graph[0].getSize().x)
	m_graph[1].setSize(sf::Vector2f(m_graph[1].getSize().x +
		(float_t(board.m_currentLevel->getFish()->getScore() - m_graphScore) / divideGraph(board)), 8));
	m_graphScore = board.m_currentLevel->getFish()->getScore();
}
//===============================================
void GameBoard::Growth::decreaseGraph(GameBoard& board)
{
	m_graphScore = board.m_currentLevel->getFish()->getScore();
	m_textScore[1].setString(std::to_string(m_graphScore));

	m_graph[1].setSize(sf::Vector2f(float_t(m_graphScore / divideGraph(board)), 8));
}

float_t GameBoard::Growth::divideGraph(GameBoard& board) const
{
	if (board.m_currentLevel->levelBehavior() == TIMER)
		return float_t(VICTORY_TIMER_SCORE / (GRAFH_LENGTH.x /*/ 3*/));

	if (m_graphScore < S_GROWTH)
		return float_t(S_GROWTH / (GRAFH_LENGTH.x / 3));

	else if (m_graphScore < M_GROWTH)
		return  float_t((M_GROWTH - S_GROWTH) / (GRAFH_LENGTH.x / 3));

	return  float_t( (L_GROWTH - M_GROWTH) / (GRAFH_LENGTH.x / 3));
}

void GameBoard::Growth::setTime(GameBoard& board)
{
	auto topLeft = sf::Vector2f(board.m_view.getCenter().x - board.m_view.getSize().x / 2,
		board.m_view.getCenter().y - board.m_view.getSize().y / 2);


	m_textTime[0] = sf::Text("TIMER", Resources::instance().getArielFont(), SCORE_SIZE);
	m_textTime[0].setFillColor(sf::Color::Red);
	m_textTime[1] = sf::Text("0", Resources::instance().getArielFont(), SCORE_SIZE);
	m_textTime[1].setFillColor(sf::Color::Yellow);


}

void GameBoard::Growth::setScore(GameBoard& board)
{
	m_textScore[0] = sf::Text("SCORE", Resources::instance().getArielFont(), SCORE_SIZE);
	m_textScore[1] = sf::Text("0", Resources::instance().getArielFont(), SCORE_SIZE);
	m_textScore[0].setFillColor(sf::Color::Red);
	m_textScore[1].setFillColor(sf::Color::Yellow);
}

void GameBoard::Growth::setGraph(GameBoard& board)
{
	m_graph[0] = sf::RectangleShape(GRAFH_LENGTH);
	m_graph[0].setFillColor(sf::Color::Black);
	m_graph[1] = sf::RectangleShape(sf::Vector2f(0, 5));
	m_graph[1].setFillColor(sf::Color::Yellow);
}
