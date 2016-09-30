#include "ItemSoundEffects.h"



ItemSoundEffects::ItemSoundEffects(string name)
{
	setSounds(name);
}


ItemSoundEffects::~ItemSoundEffects()
{
}


void ItemSoundEffects::setSounds(string name)
{
	soundEffects = new vector <Mix_Chunk*>();
	if (name == "coin")
	{
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/coin.wav"));
	}
	else
	{
		//other items will go here
	}
}