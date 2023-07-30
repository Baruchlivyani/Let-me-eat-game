#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>


//responsible for the game animations, moving the rectangles according to the 
//appropriate position in the sprite


enum class Mood
{
    Swim,
    Stay,
    Eat,
    Bursts,
    Rolling,
    VictoryBlue,
    VictoryGrin,
    VictoryYellow,
    VictoryRed, 
    locked,
    unLocked,
};


struct details
{
    sf::Vector2i size;
    size_t sumImages;
    sf::Vector2i location;
    sf::Vector2i middleSpace;
    Mood mood;
};

enum Direction
{
    Right = 1,
    Left = -1,
    Up = 0
};


class AnimationData
{
  
public:
    AnimationData(std::vector<details> detailsVec);
    AnimationData() = default;
    using ListType = std::vector<sf::IntRect>;
    using DataType = std::unordered_map<Mood, ListType>;
    DataType& AnimationDataData();

private:
    sf::Vector2i nextStart(struct details& details, size_t index) const;
    DataType m_data;

};
