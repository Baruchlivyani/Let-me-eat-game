#pragma once

const int PIXEL_SIZE = 300;
const double_t WINDOW_HEIGHT = 800;
const double_t WINDOW_WIDTH = 1200;
const double_t VIEW_HEIGHT = WINDOW_HEIGHT / 2;
const double_t VIEW_WIDTH = WINDOW_WIDTH / 2;
const sf::Vector2f MID_VIEW = { VIEW_WIDTH , VIEW_HEIGHT };
const double_t GRAPH_SIZE = WINDOW_HEIGHT / 50;
const double_t SCORE_SIZE = WINDOW_HEIGHT / 50;
const float SPEED_PER_SECOND = 30.f;
//===============================================
//object game const
//===============================================
const double_t MOUTH_SIZE = 0.075;
const double_t MOUTH_SIZE_PLY = 0.125;
//===============================================
const int MAX_TIME_DIR = 14;
const int MIN_TIME_DIR = 7;
const double_t S_SIZE = 0.25;
const double_t BUbBLE_SIZE = 0.25;

const double_t PLAYER_SIZE = 0.5;
const double_t L_SIZE = 0.85;
const double_t M_SIZE = 0.75;
const double_t SHARK_SIZE = 1.4;
const float_t PLAYER_SPEED = 200.f;
const float_t SUDDENLY_SPIKES_SPEED = 200.f;

const sf::Vector2f GRAFH_LENGTH = { WINDOW_WIDTH / 6, WINDOW_HEIGHT / 100 };
const sf::Vector2f SCORE_LENGTH = { WINDOW_WIDTH / 20, WINDOW_HEIGHT / 50 };

const double_t VICTORY = 200 ; //20
const double_t VICTORY_TIMER_SCORE = 400;
const int VICTORY_TIME = 2;

const double_t S_GROWTH = VICTORY / 10; //100
const double_t M_GROWTH = VICTORY * double_t(0.60); //600
const double_t L_GROWTH = VICTORY; //1000
const double_t RESCUE_BUBBLE_SIZE = 0.7;
const double_t SPIKES_SIZE = 0.9;
const double_t SPIKES_SUDDENLY_SIZE = 0.3;

const float_t REPLACE_TIME = 0.2;
const float_t REPLACE_DUTTON_TIME = REPLACE_TIME * 7;
const std::string LOST = "                     \n   You lost!!!  \n                    ";
const std::string HELP = "Let Me Eat:\n"
"Big Fish Eat Smaller is an arcade game where you start\n"
"the game as a small fish and you should try to get bigger\n"
"by eating smaller fish.The ocean is big and full of surprises,\n"
"so try not to run into big fish that might bite you right away.\n"
"Be patient while growing, and you can land the bigger fish!\n"
"Objects in the game :\n"
"Rescue Bubble - Protects the player once against\n"
"a collision with an enemy.\n"
"Spikes - shrink the player and lower his score.\n"
"options- gives the player the option to choose the\n"
"stages he has passed.   continue - continues from the stage\n"
" the player stopped.    new game - a new game starts.";

enum Score
{
	UPDATE,
	RESETE
};

enum LevelBehavior
{
	SCORE,
	TIMER
};

enum SmallFishRand
{
	SMALL_FISH_1 = 1240,
	SMALL_FISH_2 = 1550,
	SMALL_FISH_3 = 1860,
	SMALL_FISH_4 = 2170,
	SMALL_FISH_5 = 2480,
};




