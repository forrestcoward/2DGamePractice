#include "AbilityAnimation.h"
#include "Texture.h"

//Default constructor
AbilityAnimation::AbilityAnimation()
{
}

//Constructor
AbilityAnimation::AbilityAnimation(string name, SDL_Renderer* renderer)
{
	texture = Texture::LoadTexture("../images/baddies/Fireball_1.png", renderer);
	//setTextures(name, renderer);
	w = 8;
	h = 8;
	animationFrame = 0;
}

//Deconstructor
AbilityAnimation::~AbilityAnimation()
{
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
void AbilityAnimation::setTextures(string abilityName, SDL_Renderer* renderer)
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

int AbilityAnimation::getAnimationFrame()
{
	return animationFrame;
}
