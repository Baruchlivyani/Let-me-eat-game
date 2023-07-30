#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Resources.h"
#include "Define.h"
#include "Bubble.h"
//===============================================
class GameBoard;
class GameController;
//===============================================
//responsible for managing the various game buttons, and defining them if necessary -
//BackButton, ContinueButton, ExitButton, HelpButton, NewGameButton
//The base department, literally things related to everyone.
//An abstract class that assigns to each button
//in the menu
//And the different functions for each button realized by virtual


//template <typename T>
class Button
{
public:
    Button(const char buttonName[], sf::Vector2f Location, int sizeFont);
    Button() = default;
    virtual ~Button() = default;
    void turnOnButton();

    virtual void showContentButton(GameController& game, GameBoard& board) {};

    //A function responsible for highlighting as open the cursor on it
    void highlightsButton(sf::ConvexShape& m_arrow);
    void highlightsButton();
    void resetHighlightsButton();
    void drowButton(sf::RenderWindow* menuWindow);
    bool isButtonPressed(sf::Vector2f click);
    bool isPressedNow();
    sf::Vector2i getBackClickPosition(sf::RenderWindow* menuWindow) const;


protected:
    void HandleClosWindow(sf::RenderWindow* menuWindow) const;
    bool m_buttonOn;
    sf::Clock m_clockOn;
    Bubble m_key;
    sf::Text m_text;
    sf::Color m_color;
    sf::Color m_defaultColor;


private:
    bool m_pressedNow;
    void setText(sf::Vector2f Location);

};