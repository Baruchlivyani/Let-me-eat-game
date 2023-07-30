#pragma once
#include "GameObject.h"
#include "SmartObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

//responsible for the factory template of the game,
//adding different objects, this class is template,
//to receive different types of objects.

enum class ObjectType
{
	LFish,
	MFish,
	SFish,
	Shark,
	Bubble,
	Spikes,
	SuddenlySpikes,
	RescueBubble,
	PlayerFish,
};

template <typename T>
class Factory
{
public:
	static Factory& instance()
	{
		static auto instance = Factory();
		return instance;
	}

	using FuncType = std::unique_ptr<T>(*)(sf::Texture& texture, sf::Vector2f location, double_t size);

	bool registerType(ObjectType t, FuncType f)
	{
		m_map.emplace(t, f);
		return true;
	}

	std::unique_ptr<T> create(ObjectType t, sf::Texture& texture, sf::Vector2f location, double_t size) const
	{
		return m_map.at(t)(texture, location, size);
	}



private:
	Factory() = default;
	Factory(const Factory&) = delete;
	void operator=(const Factory&) = delete;
	std::unordered_map<ObjectType, FuncType> m_map;
};
