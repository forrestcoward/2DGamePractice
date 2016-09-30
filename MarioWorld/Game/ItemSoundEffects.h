#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
#include <iostream>

#ifndef ITEMSOUNDEFFECTS
#define SOUNDEFFECTS

using namespace std;

class ItemSoundEffects
{
public:
	ItemSoundEffects(string name);
	~ItemSoundEffects();
private:
	vector <Mix_Chunk*>* soundEffects;
	void ItemSoundEffects::setSounds(string name);
};

#endif 