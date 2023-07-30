#pragma once
#include "Button.h"
#include "BackButton.h"
class BackButton;
class CreditButton : public Button
{
public:
	CreditButton(std::function<void(sf::RenderWindow*)> drow );
	void showContentButton(GameController& game, GameBoard& board)override;


private:
	sf::Text m_printing;
	sf::Sprite m_sprite;
	std::function<void(sf::RenderWindow*)> m_drowFunc;
	BackButton m_backButton;

};
