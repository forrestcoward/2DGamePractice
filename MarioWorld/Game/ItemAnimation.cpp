#include "ItemAnimation.h"
#include "Texture.h"


//Default Cosntructor
ItemAnimation::ItemAnimation()
{
}

//Constructor
ItemAnimation::ItemAnimation(SDL_Texture* texture, string name, int tickerCap, SDL_Renderer* renderer)
{
	currentTexture = texture;
	setItemAnimations(name, renderer);
	animationFrameTickerCap = tickerCap;
	animationFrame = 0;
	animationFrameTicker = 0;
}

//Deconstructor
ItemAnimation::~ItemAnimation()
{
}

//Update item animation
void ItemAnimation::updateAnimation()
{
	if (animationFrameTicker == animationFrameTickerCap)
	{
		animationFrameTicker = 0;
		animationFrame++;
	}
	else
		animationFrameTicker++;

	if (animationFrame > 7)
		animationFrame = 0;

	currentTexture = (*itemAnimations)[animationFrame];
}

//Set item animations
void ItemAnimation::setItemAnimations(string name, SDL_Renderer* renderer)
{
	itemAnimations = new vector <SDL_Texture*>();
	if (name == "coin")
	{
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_1.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_2.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_3.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_4.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_5.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_6.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_7.png", renderer));
		itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_8.png", renderer));
	}
}
