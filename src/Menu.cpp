#include "Menu.h"
#include  <iostream>
#include "NewGameButton.h"
#include "ExitButton.h"
#include "GameBoard.h"
#include "GameController.h"
#include "ContinueButton.h"
#include "CreditButton.h"
#include "HelpButton.h"
#include "OptionsButton.h"
//===============================================
Menu::Menu():
	m_closeMenu(false) , m_background(Resources::instance().getMenuBackround()), m_fishBackground()
{
    setButtons();
}
//===============================================
void Menu::setButtons()
{
	m_buttons.push_back(std::make_unique<ContinueButton>());
	m_buttons.push_back(std::make_unique<OptionsButton>(std::bind(&Menu::drow, this, std::placeholders::_1)));
	m_buttons.push_back(std::make_unique<NewGameButton>());
	m_buttons.push_back(std::make_unique<ExitButton>());
	m_buttons.push_back(std::make_unique<CreditButton>(std::bind(&Menu::drow, this, std::placeholders::_1)));
	m_buttons.push_back(std::make_unique<HelpButton>(std::bind(&Menu::drow, this, std::placeholders::_1)));
}
//===============================================
//open the menu and make all the user comments
//===============================================
void Menu::openMenu(GameController& game, GameBoard& board)
{
		board.getWindow()->setView(sf::View( sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT),
		sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));
		Resources::instance().playingSound();
	while (board.getWindow()->isOpen())
	{
		board.getWindow()->clear();
		resetfirstbutton();
		drowMenu(game, board);
		board.getWindow()->display();
		for (auto event = sf::Event{}; board.getWindow()->pollEvent(event); )
			switch (event.type)
			{
			case sf::Event::Closed:
				board.getWindow()->close();
				game.goExit(true);
				break;

			case sf::Event::KeyPressed:
				isKeyPressed(game, event, board);
				break;

			case sf::Event::MouseMoved:
				isMouseMoved(event);
				break;

			case sf::Event::MouseButtonReleased:
				isMousReleased(game, event, board);
				break;
			}
	}
}
//===============================================
void Menu::drowMenu(GameController& game, GameBoard& board)
{
	drow(board.getWindow());

	
	std::for_each(m_fishBackground.smartBeginVec(), m_fishBackground.smartEndVec(), [&board](auto& i)
		{
			i->drow(board.getWindow());
			i->replaceTexture();
		});
	for (int cell = 0; cell < m_buttons.size(); ++cell)
		m_buttons[cell]->drowButton(board.getWindow());

	for (int cell = 0; cell < m_buttons.size(); ++cell)
		m_buttons[cell]->showContentButton(game, board);

}
//===============================================
void Menu::drow(sf::RenderWindow* menuWindow)
{
	menuWindow->draw(m_background);

	std::for_each(m_fishBackground.DecorBeginVec(), m_fishBackground.DecorEndVec(), [menuWindow](auto& i)
		{
			i->drow(menuWindow);
	i->handleOutOfWorld(menuWindow->getSize());
		});

	moveBackground(menuWindow);
}


void Menu::moveBackground(sf::RenderWindow* menuWindow)
{
	std::for_each(m_fishBackground.smartBeginVec(), m_fishBackground.smartEndVec(), [menuWindow](auto& i)
		{
			i->move();
	i->handleOutOfWorld(menuWindow->getSize());
		});

	std::for_each(m_fishBackground.DecorBeginVec(), m_fishBackground.DecorEndVec(), [menuWindow](auto& i)
		{
			i->move();
	i->handleOutOfWorld(menuWindow->getSize());
		});
}

void Menu::isMouseMoved(const sf::Event& event)
{
	for (int cell = 0; cell < m_buttons.size(); ++cell)
		if (m_buttons[cell]->isButtonPressed(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
			m_buttons[cell]->highlightsButton(m_arrow);
		else
			m_buttons[cell]->resetHighlightsButton();
}
//===============================================
void Menu::isMousReleased(GameController& game, const sf::Event& event, GameBoard& board)
{
	for (int cell = 0; cell < m_buttons.size(); ++cell)
		if (m_buttons[cell]->isButtonPressed(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
			m_buttons[cell]->turnOnButton(/*game, board*/);
}
//===============================================
//Moves the cursor backand forth
void Menu::isKeyPressed(GameController& game, const sf::Event& event, GameBoard& board)
{
	switch (event.key.code)
	{

	case sf::Keyboard::Up:
		isUpPressed();
		break;

	case sf::Keyboard::Down:
		isDownPressed();
		break;

	case sf::Keyboard::Enter:
		for (int cell = 0; cell < m_buttons.size(); ++cell)
			if (m_buttons[cell]->isPressedNow())
				m_buttons[cell]->turnOnButton(/*game, board*/);
	
		break;
	}
}
//===============================================
void Menu::isUpPressed()//Moves the cursor backand forth
{
	for (size_t cell = 0; cell < m_buttons.size(); ++cell)
		if (m_buttons[cell]->isPressedNow())
		{
			m_buttons[cell]->resetHighlightsButton();
			if (cell - 1 == -1)
				cell = m_buttons.size() - 1;
			else
				cell -= 1;
			m_buttons[cell]->highlightsButton(m_arrow);
		}
}
//===============================================
void Menu::isDownPressed()//Moves the cursor backand forth
{
	for (int cell = 0; cell < m_buttons.size(); ++cell)
		if (m_buttons[cell]->isPressedNow())
		{
			m_buttons[cell]->resetHighlightsButton();
			if (cell + 1 == m_buttons.size())
				cell = 0;
			else
				cell += 1;
			m_buttons[cell]->highlightsButton(m_arrow);
		}
}
//===============================================
void Menu::flashingArrow()
{
	if (m_arrowClock.getElapsedTime().asSeconds() > 0.8)
	{
		m_arrowClock.restart();
		if (m_arrow.getFillColor() == sf::Color(0, 0, 0, 0))
		{
			m_arrow.setOutlineColor(sf::Color::Black);
			m_arrow.setFillColor(sf::Color::Red);
		}
		else
		{
			m_arrow.setFillColor(sf::Color(0, 0, 0, 0));
			m_arrow.setOutlineColor(sf::Color(0, 0, 0, 0));
		}
	}
}
//===============================================
void Menu::resetfirstbutton()
{
	for (int cell = 0; cell < m_buttons.size(); ++cell)
		if (m_buttons[cell]->isPressedNow())
			return;
	m_buttons[0]->highlightsButton(m_arrow);
}
//===============================================


