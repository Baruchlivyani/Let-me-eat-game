#include "Resources.h"
#include "Define.h"
//===============================================
Resources::Resources()
{
	if (!m_backroundTexture1.loadFromFile("backround1.png") ||
		!m_backroundTexture2.loadFromFile("backround2.png") ||
		!m_backroundTexture3.loadFromFile("backround3.png") ||
		!m_spriteShit.loadFromFile("spriteShit.png") ||
		!m_menuBackround.loadFromFile("menuBackround.png") ||
		!m_programmersTexture.loadFromFile("programmers.png") ||
		!m_victoryTexture.loadFromFile("victory.png") ||
		!m_iconsTexture.loadFromFile("icons.png") ||
		!m_litheFishTexture.loadFromFile("lightFish.png") ||
		!m_arielFont.loadFromFile("C:/Windows/Fonts/COOPBL.TTF"))
		throw std::runtime_error("Can't load from img file");

	sf::SoundBuffer SoundBuffer;

	if (!SoundBuffer.loadFromFile("sound.wav"))
		throw std::runtime_error("Can't load from sound file");
	
	m_soundBuffer.push_back(SoundBuffer);

	if (!SoundBuffer.loadFromFile("victory.wav"))
		throw std::runtime_error("Can't load from sound file");

	m_soundBuffer.push_back(SoundBuffer);

	if(!SoundBuffer.loadFromFile("growth.wav"))
		throw std::runtime_error("Can't load from sound file");

	m_soundBuffer.push_back(SoundBuffer);

	if (!SoundBuffer.loadFromFile("eat.wav"))
		throw std::runtime_error("Can't load from sound file");

	m_soundBuffer.push_back(SoundBuffer);

	if (!SoundBuffer.loadFromFile("gameover.wav"))
		throw std::runtime_error("Can't load from sound file");

	m_soundBuffer.push_back(SoundBuffer);

	sf::Sound sound;

	for (auto& buffer : m_soundBuffer) {
		sound.setBuffer(buffer);
		m_sounds.push_back(sound);
	}

	m_sounds.push_back(sound);
	sound.setBuffer(m_soundBuffer[0]);
	m_sounds.push_back(sound);
	sound.setBuffer(m_soundBuffer[1]);
	m_sounds.push_back(sound);
	sound.setBuffer(m_soundBuffer[2]);
	m_sounds.push_back(sound);
	sound.setBuffer(m_soundBuffer[3]);
	m_sounds.push_back(sound);
	sound.setBuffer(m_soundBuffer[4]);
	m_sounds.push_back(sound);
	
}		
//===============================================
Resources& Resources::instance()
{
	static auto resources = Resources();
	return resources;
}
//===============================================
sf::Texture& Resources::getBackroundTexture1()
{
	return m_backroundTexture1;
}
//===============================================
sf::Texture& Resources::getBackroundTexture2()
{
	return m_backroundTexture2;
}
//===============================================
sf::Texture& Resources::getBackroundTexture3()
{
	return m_backroundTexture3;
}
//===============================================
sf::Texture& Resources::getSpriteShit()
{
	return m_spriteShit;
}
//===============================================
sf::Texture& Resources::getMenuBackround()
{
	return m_menuBackround;
}
//===============================================
sf::Texture& Resources::getProgrammersTexture()
{
	return m_programmersTexture;
}
//===============================================
sf::Texture& Resources::getLitheFishTexture()
{
	return m_litheFishTexture;
}
//===============================================
sf::Texture& Resources::getVictoryTexture()
{
	return m_victoryTexture;
}
//===============================================
sf::Texture& Resources::getIconsTexture()
{
	return m_iconsTexture;
}
//===============================================
sf::Font& Resources::getArielFont()
{
	return m_arielFont;
}
//===============================================
void Resources::menuSound() 
{
	m_sounds[0].play();
	m_sounds[0].setLoop(true);
}
//===============================================
void Resources::growthSound()
{
	m_sounds[2].play();
}
//===============================================
void Resources::gameOverSound()
{
	m_sounds[4].play();
}
//===============================================
void Resources::victorySound()
{
	m_sounds[1].play();
}
//===============================================
void Resources::eatSound()
{
	m_sounds[3].play();
}
//===============================================
void Resources::playingSound()
{
	m_sounds[0].play();
	m_sounds[0].setLoop(true);
}
//===============================================






