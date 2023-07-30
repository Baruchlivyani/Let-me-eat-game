#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerFish.h"
#include "Shark.h"
#include "SFish.h"
#include "LFish.h"
#include "MFish.h"
#include "Bubble.h"
#include "Resources.h"
#include "Factory.h"
#include "Victory.h"
#include "Timer.h"
#include "Button.h"
class GameController;

//the base class of all levels 
//- is responsible for things that are common to all.

class LevelBase 
{
public:


	virtual std::shared_ptr<LevelBase> copyMy();
	LevelBase();
    ~LevelBase() = default;
	sf::Sprite& getBackround();
	std::unique_ptr<PlayerFish>& getFish();
	sf::Vector2f positionRand() const;
	std::vector<std::unique_ptr<SmartObject>>::iterator&& smartBeginVec();
	std::vector<std::unique_ptr<SmartObject>>::iterator&& smartEndVec();
	std::vector<std::unique_ptr<DecorativeObject>>::iterator&& DecorBeginVec();
	std::vector<std::unique_ptr<DecorativeObject>>::iterator&& DecorEndVec();
	void erase(int index);
	std::unique_ptr<Timer>& getTimer();
	std::vector<Victory>& victoryVec() { return m_victory; };
	void resete();
	std::string getName() const;
	bool isFinish() const;
	bool isFails() const;
	void setFinish(bool ToF);
	void setFails(bool ToF);
	LevelBehavior levelBehavior() const;
	virtual Mood getStatus();
	virtual void setStatus(Mood mood);
	void drowIcon(sf::RenderWindow* menuWindow);
	virtual void drowButtons(sf::RenderWindow* menuWindow) {};
	virtual size_t numOfLevel() const { return 10; };


protected:
	void handelExit(GameController& game);
	LevelBehavior m_levelBehavior;
	std::unique_ptr<PlayerFish> m_player;
	sf::Sprite m_backround;
	std::vector < std::unique_ptr<SmartObject>> m_SmartObjects;
	std::vector < std::unique_ptr<DecorativeObject>> m_DecorativeObjects;
	int m_sumSFish;
	int m_sumMFish;
	int m_sumLFish;
	std::vector<Victory> m_victory;
	bool m_isFinish;
	bool m_isFails;
	std::unique_ptr<Timer> m_gameTimer;
	AnimationData m_animation;
	Mood m_mood;
	sf::Sprite m_sprite;
	std::string m_name;
	sf::Text m_levelText;

private:
	std::vector<details> initAnimationData();
	 
};
