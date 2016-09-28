#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "AbilityAnimation.h"
#include "Texture.h"
#include <string>

using namespace std;

//Default constructor
AbilityAnimation::AbilityAnimation()
{
}

//Constructor
AbilityAnimation::AbilityAnimation(string name, SDL_Renderer* renderer)
{
	animationFrameTicker = 0;
	animationFrameTickerCap = 2;
	texture = Texture::LoadTexture("../images/baddies/Fireball_1.png", renderer);
	setAnimations(name, renderer);
	w = 8;
	h = 8;
	animationFrame = 0;
}

//Deconstructor
AbilityAnimation::~AbilityAnimation()
{
	for (unsigned int i = 0; i < abilityTextures->size(); i++)
	{
		SDL_DestroyTexture((*abilityTextures)[i]);
	}
	abilityTextures->clear();
	SDL_DestroyTexture(texture);
}

//Return h
int AbilityAnimation::getH()
{
	return h;
}

//Return w
int AbilityAnimation::getW()
{
	return w;
}

//Sets ability textures 
void AbilityAnimation::setAnimations(string abilityName, SDL_Renderer* renderer)
{
	abilityTextures = new vector <SDL_Texture*>();
	if (abilityName == "fireball")
	{
		abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_1.png", renderer));
		abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_2.png", renderer));
		abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_3.png", renderer));
		abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_4.png", renderer));
	}
}

//Returns animation frame
int AbilityAnimation::getAnimationFrame()
{
	return animationFrame;
}

//Updates current texture
void AbilityAnimation::updateAbilityTexture()
{
	if (animationFrameTicker == animationFrameTickerCap)
	{
		animationFrame++;
		animationFrameTicker = 0;
	}

	if (animationFrame == 4)
	{
		animationFrame = 0;
		animationFrameTicker = 0;
	}
	else
		animationFrameTicker++;

	texture = (*abilityTextures)[animationFrame];
}
