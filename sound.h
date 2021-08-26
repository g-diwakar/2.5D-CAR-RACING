#ifndef SOUND_H
#define SOUND_H

#include<SFML/Audio.hpp>
#include<string>

class GameSound
{
private:
	sf::SoundBuffer s_buffer[4];
	sf::Sound sound[4];
public:
	void loadSound();
	void playSound(int);
	void pauseSound(int);
	void stopSound(int);
	
};

void GameSound::loadSound()
{
	for (int i=0;i<4;i++)
	{
		s_buffer[i].loadFromFile("Sounds/"+std::to_string(i)+".ogg");
		sound[i].setBuffer(s_buffer[i]);
	}
	sound[3].setLoop(true);
	sound[3].setVolume(50);
}

void GameSound::playSound(int n)
{
	sound[n].play();
}

void GameSound::pauseSound(int n)
{
	sound[n].pause();
}

void GameSound::stopSound(int n)
{
	sound[n].stop();
}

#endif

