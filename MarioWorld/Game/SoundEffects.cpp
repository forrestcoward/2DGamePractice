#include "SoundEffects.h"

//Default Constructor
SoundEffects::SoundEffects()
{

}

//Constructor
SoundEffects::SoundEffects(string name, vector <Mix_Chunk*>* objectSounds)
{
	soundEffects = objectSounds;
}

//Deconstructor
SoundEffects::~SoundEffects()
{

}

//Play fireball sound
void SoundEffects::playFireballSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[6], 0);
}

//Play jump sound
void SoundEffects::playJumpSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[1], 0);
}

//Play run sound
void SoundEffects::playRunSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[0], 0);
}

//Play stomp sound
void SoundEffects::playStompSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[3], 0);
}

vector <Mix_Chunk*>* SoundEffects::loadItemSounds()
{
	vector <Mix_Chunk*>* itemSounds = new vector <Mix_Chunk*>();
	
	itemSounds->push_back(Mix_LoadWAV("../sounds/wav/coin.wav"));
	//load other sounds here eventually

	return itemSounds;
}

vector <Mix_Chunk*>* SoundEffects::loadMarioSounds()
{
	vector <Mix_Chunk*>* marioSounds = new vector <Mix_Chunk*>();
	
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/begin_to_jump.wav"));//Plays a more realistic run sound that run.wav file.
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/jump.wav"));
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/land.wav"));
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/stomp.wav"));
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/kick.wav"));
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/mario_throw.wav"));
	marioSounds->push_back(Mix_LoadWAV("../sounds/wav/fireball.wav"));

	return marioSounds;
}

vector <Mix_Chunk*>* SoundEffects::loadKoopaShellSounds()
{
	vector <Mix_Chunk*>* koopaShellSounds = new vector <Mix_Chunk*>();

	koopaShellSounds->push_back(Mix_LoadWAV("../sounds/wav/kick.wav"));
	koopaShellSounds->push_back(Mix_LoadWAV("../sounds/wav/stomp.wav"));

	return koopaShellSounds;
}
