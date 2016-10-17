#include "SoundEffects.h"

//Default Constructor
SoundEffects::SoundEffects()
{

}

//Constructor
SoundEffects::SoundEffects(string name)
{
	setSounds(name);
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

//Set sounds
void SoundEffects::setSounds(string name)
{
	soundEffects = new vector <Mix_Chunk*>();
	if (name == "mario")
	{
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/begin_to_jump.wav"));//Plays a more realistic run sound that run.wav file.
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/jump.wav"));
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/land.wav"));
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/stomp.wav"));
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/kick.wav"));
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/mario_throw.wav"));
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/fireball.wav"));
	}
	else if (name == "coin")
	{
		soundEffects->push_back(Mix_LoadWAV("../sounds/wav/coin.wav"));
	}
	else
	{
		//other items will go here
	}
}