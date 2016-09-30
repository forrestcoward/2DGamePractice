#ifndef CREATURESOUNDEFFECTS
#define CREATURESOUNDEFFECTS

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

class CreatureSoundEffects
{
public:
	int runSoundTicker;
	void CreatureSoundEffects::playFireballSound();
	void CreatureSoundEffects::playJumpSound();
	void CreatureSoundEffects::playRunSound();
	void CreatureSoundEffects::playStompSound();
	CreatureSoundEffects(string name);
	CreatureSoundEffects();
	~CreatureSoundEffects();
private:
	vector <Mix_Chunk*>* soundEffects;
	void CreatureSoundEffects::setSounds(string name);
};

#endif