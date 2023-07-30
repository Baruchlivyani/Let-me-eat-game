#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Define.h"
#include "AnimationData.h"
#include <functional>

//responsible for the game objects in general, and implementing 
//functions that are common to all if necessary - the grandfather of
//all the different game objects.

class GameObject
{
public:
	GameObject(sf::Texture& texture, sf::Vector2f location);
	GameObject(sf::Texture& texture, sf::Vector2f location, double_t size, Direction directionm);
	GameObject() = default;
	virtual ~GameObject() = default;
	void drow(sf::RenderWindow* window) const;
	virtual void move() = 0;
	virtual void handleOutOfWorld(sf::Vector2u WindowSize) {};
	bool isOutOfWorld(sf::Vector2u WindowSize);
	void replaceTexture();
	void returnToWorld(sf::Vector2u windowSize);
	void updateMood(Mood mood, bool isLoop);
	void setPosition(sf::Vector2f position);
	void initClock();

protected:
	void replaceSide(Direction direction);
	sf::Sprite m_sprite;
	sf::Clock  m_clockMove;
	sf::Clock  m_clockReplace;
	sf::Clock  m_clockMood;
	sf::Texture m_texture;
	sf::Vector2f m_direction;
	AnimationData m_AnimationData;
	size_t m_index;
	Mood m_mood;
	Mood m_lastMood;
	Direction m_RoL;
	bool m_isLoop;

private:

};

