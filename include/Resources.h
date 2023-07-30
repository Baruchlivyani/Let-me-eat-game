#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//responsible for managing the various resources related to the game.

class Resources
{
public:

	static Resources& instance();
	Resources(const Resources&) = delete;
	void operator = (const Resources&) = delete;
	sf::Texture& getSpriteShit();
	sf::Texture& getBackroundTexture1();
	sf::Texture& getBackroundTexture2();
	sf::Texture& getBackroundTexture3();
	sf::Texture& getMenuBackround();
	sf::Texture& getProgrammersTexture();
	sf::Texture& getVictoryTexture();
	sf::Texture& getIconsTexture();
	sf::Texture& getLitheFishTexture();


	sf::Font& getArielFont();
	void menuSound();
	void growthSound();
	void playingSound();
	void eatSound();
	void victorySound();
	void gameOverSound();


private:
	Resources();
	~Resources() = default;
	sf::SoundBuffer m_gameBuffer;
	std::vector <sf::SoundBuffer> m_soundBuffer;
	std::vector <sf::Sound> m_sounds;
	/*sf::Sound m_eatingSound;
	sf::Sound m_playSound;*/
	sf::Texture m_backroundTexture1;
	sf::Texture m_backroundTexture2;
	sf::Texture m_backroundTexture3;
	sf::Texture m_spriteShit;
	sf::Texture m_menuBackround;
	sf::Texture m_programmersTexture;
	sf::Texture m_victoryTexture;
	sf::Texture m_iconsTexture;
	sf::Texture m_litheFishTexture;
	sf::Font m_arielFont;

};







