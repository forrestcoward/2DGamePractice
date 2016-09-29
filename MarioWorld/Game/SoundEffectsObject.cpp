#include "SoundEffectsObject.h"



//Constructor
SoundEffectsObject::SoundEffectsObject(string name)
{
	setSounds(name);
}

//Deconstructor
SoundEffectsObject::~SoundEffectsObject()
{
}

//Set sound effects
void SoundEffectsObject::setSounds(string name)
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
}

//Play stomp sound
void SoundEffectsObject::playStompSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[3], 0);
}

//Play run sound
void SoundEffectsObject::playRunSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[0], 0);
}

//Play jump sound
void SoundEffectsObject::playJumpSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[1], 0);
}

//Play fireball sound
void SoundEffectsObject::playFireballSound()
{
	Mix_PlayChannel(-1, (*soundEffects)[6], 0);
}

