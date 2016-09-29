#ifndef SOUNDEFFECTSOBJECT
#define SOUNDEFFECTSOBJECT
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

using namespace std;

class SoundEffectsObject
{
public:
	SoundEffectsObject(string name);
	~SoundEffectsObject();
	void SoundEffectsObject::setSounds(string name);
	void SoundEffectsObject::playStompSound();
	void SoundEffectsObject::playRunSound();
	void SoundEffectsObject::playJumpSound();
	void SoundEffectsObject::playFireballSound();
	int runSoundTicker;
private:
	vector <Mix_Chunk*>* soundEffects;

};
#endif 
