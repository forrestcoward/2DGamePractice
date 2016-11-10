#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
#include <iostream>

#ifndef SOUNDEFFECTS
#define SOUNDEFFECTS

using namespace std;

class SoundEffects
{
public:
	SoundEffects();
	~SoundEffects();
	int runSoundTicker;
	void SoundEffects::playFireballSound();
	void SoundEffects::playJumpSound();
	void SoundEffects::playRunSound();
	void SoundEffects::playStompSound();
	static vector <Mix_Chunk*>* SoundEffects::loadItemSounds();
	static vector <Mix_Chunk*>* SoundEffects::loadMarioSounds();
	static vector <Mix_Chunk*>* SoundEffects::loadKoopaShellSounds();
	SoundEffects(string name, vector <Mix_Chunk*>* objectSounds);
private:
	vector <Mix_Chunk*>* soundEffects;
};

#endif
