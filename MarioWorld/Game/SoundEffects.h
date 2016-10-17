#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
#include <iostream>

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
	SoundEffects(string name);
private:
	vector <Mix_Chunk*>* soundEffects;
	void SoundEffects::setSounds(string name);
};

