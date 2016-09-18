#include "Animation.h"
#include "Texture.h"


//Deafult constructor
Animation::Animation()
{
}

//Constructor
Animation::Animation(string name, int tickerCap, SDL_Renderer* renderer)
{
	Animation::setClips(renderer, name);
	animationFrame = 0;
	animationTicker = 0; 
	animationTickerCap = tickerCap;
	if (name == "mario")
		facingRight = true;
	else
		facingRight = false;
}

//Sets the animation clips
void Animation::setClips(SDL_Renderer* renderer, string name)
{
	leftClips = new vector <SDL_Texture*>();
	rightClips = new vector <SDL_Texture*>();
	if (name == "mario")
	{
		//Set right clips
		rightClips->push_back(Texture::LoadTexture("../images/mario/mario_right_still.png", renderer));
		rightClips->push_back(Texture::LoadTexture("../images/mario/mario_right_1.png", renderer));
		rightClips->push_back(Texture::LoadTexture("../images/mario/mario_right_2.png", renderer));
		rightClips->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Right.png", renderer));

		//Set left clips
		leftClips->push_back(Texture::LoadTexture("../images/mario/mario_left_still.png", renderer));
		leftClips->push_back(Texture::LoadTexture("../images/mario/mario_left_1.png", renderer));
		leftClips->push_back(Texture::LoadTexture("../images/mario/mario_left_2.png", renderer));
		leftClips->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Left.png", renderer));
	}
}
