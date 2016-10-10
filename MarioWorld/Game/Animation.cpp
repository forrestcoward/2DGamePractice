#include "Animation.h"
#include "Texture.h"


//Deafult constructor
Animation::Animation()
{
}

//Deconstructor
Animation::~Animation()
{
	rightAnimations = NULL;
	leftAnimations = NULL;
	abilityAnimations = NULL;
}

//Constructor for mario and monsters
Animation::Animation(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, int tickerCap, SDL_Renderer* renderer, bool isMario)
{
	animationFrame = 0;
	animationTicker = 0; 
	animationTickerCap = tickerCap;
	if (isMario)
		facingRight = true;
	else
		facingRight = false;
	itemAnimations = NULL;
	this->rightAnimations = rightAnimations;
	this->leftAnimations = leftAnimations;
	abilityAnimations = NULL;
}

//Constructor for items/abilities
Animation::Animation(int tickerCap, SDL_Renderer* renderer, vector <SDL_Texture*>* itemAnimations = nullptr, vector <SDL_Texture*>* abilityAnimations = nullptr)
{
	animationFrame = 0;
	animationTicker = 0;
	animationTickerCap = tickerCap;
	this->itemAnimations = itemAnimations;
	rightAnimations = NULL;
	leftAnimations = NULL;
	this->abilityAnimations = abilityAnimations;
	if (abilityAnimations != NULL)
	{
		w = 8;
		h = 8;
	}
	else
	{
		w = 16;
		h = 16;
	}
}



void Animation::updateAnimation(int velocity, bool jumping)
{
	if (!jumping)
	{
		if (velocity < 0 && !facingRight && animationTicker >= animationTickerCap && animationFrame < 2)//Facing left and not standing
		{
			animationFrame++;
			animationTicker = 0;
		}
		else if (velocity > 0 && facingRight && animationTicker >= animationTickerCap && animationFrame < 2)//Facing right and not standing
		{
			animationFrame++;
			animationTicker = 0;
		}
		else if (animationFrame == 2 && animationTicker >= animationTickerCap)
		{
			animationFrame = 1;
			animationTicker = 0;
		}
		else if (velocity == 0)
		{
			animationFrame = 0;
			animationTicker = animationTickerCap;
		}

		animationTicker++;

		if (facingRight)
			texture = (*rightAnimations)[animationFrame];
		else
			texture = (*leftAnimations)[animationFrame];
	}
	else
	{
		if (facingRight)
		{
			texture = (*rightAnimations)[3];
		}
		else
		{
			texture = (*leftAnimations)[3];
		}
	}
}

void Animation::updateMonsterAnimation(int velocity, bool jumping)
{
	if (!jumping)
	{
		if (velocity < 0 && !facingRight && animationTicker >= animationTickerCap && animationFrame < 1)//Facing left and not standing
		{
			animationFrame++;
			animationTicker = 0;
		}
		else if (velocity > 0 && facingRight && animationTicker >= animationTickerCap && animationFrame < 1)//Facing right and not standing
		{
			animationFrame++;
			animationTicker = 0;
		}
		else if (animationFrame == 1 && animationTicker >= animationTickerCap)
		{
			animationFrame = 0;
			animationTicker = 0;
		}

		animationTicker++;

		if (facingRight)
			texture = (*rightAnimations)[animationFrame];
		else
			texture = (*leftAnimations)[animationFrame];
	}
	else
	{
		if (facingRight)
		{
			texture = (*rightAnimations)[3];
		}
		else
		{
			texture = (*leftAnimations)[3];
		}
	}
}

void Animation::updateItemAnimation()
{
	if (animationTicker == animationTickerCap)
	{
		animationTicker = 0;
		animationFrame++;
	}
	else
		animationTicker++;

	if (animationFrame > 7)
		animationFrame = 0;

	texture = (*itemAnimations)[animationFrame];
}

void Animation::updateDirection(bool direction, int* velocity)
{
	if (facingRight != direction)
	{
		facingRight = direction;
		*velocity = 0;
	}
}

void Animation::updateMonsterDirection()
{
		facingRight = !facingRight;
}

bool Animation::getDirection()
{
	return facingRight;
}

void Animation::updateAbilityAnimation()
{
	if (animationTicker == animationTickerCap)
	{
		animationFrame++;
		animationTicker = 0;
	}

	if (animationFrame == 4)
	{
		animationFrame = 0;
		animationTicker = 0;
	}
	else
		animationTicker++;

	texture = (*abilityAnimations)[animationFrame];
}

vector <SDL_Texture*>* Animation::loadRightMarioTextures(SDL_Renderer* renderer)
{
	vector <SDL_Texture*>* rightAnimations = new vector <SDL_Texture*>();
	rightAnimations->push_back(Texture::LoadTexture("../images/mario/mario_right_still.png", renderer));
	rightAnimations->push_back(Texture::LoadTexture("../images/mario/mario_right_1.png", renderer));
	rightAnimations->push_back(Texture::LoadTexture("../images/mario/mario_right_2.png", renderer));
	rightAnimations->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Right.png", renderer));

	return rightAnimations;
}

vector <SDL_Texture*>* Animation::loadLeftMarioTextures(SDL_Renderer* renderer)
{
	vector <SDL_Texture*>* leftAnimations = new vector <SDL_Texture*>();
	leftAnimations->push_back(Texture::LoadTexture("../images/mario/mario_left_still.png", renderer));
	leftAnimations->push_back(Texture::LoadTexture("../images/mario/mario_left_1.png", renderer));
	leftAnimations->push_back(Texture::LoadTexture("../images/mario/mario_left_2.png", renderer));
	leftAnimations->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Left.png", renderer));

	return leftAnimations;

}

vector <SDL_Texture*>* Animation::loadRightKoopaTextures(SDL_Renderer* renderer)
{
	vector <SDL_Texture*>* rightAnimations = new vector <SDL_Texture*>();
	rightAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Right_1.png", renderer));
	rightAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Right_2.png", renderer));

	return rightAnimations;
}

vector <SDL_Texture*>* Animation::loadLeftKoopaTextures(SDL_Renderer* renderer)
{
	vector <SDL_Texture*>* leftAnimations = new vector <SDL_Texture*>();
	leftAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Left_1.png", renderer));
	leftAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Left_2.png", renderer));

	return leftAnimations;
}

vector <SDL_Texture*>* Animation::loadItemTextures(SDL_Renderer* renderer)
{
	vector <SDL_Texture*>* itemAnimations = new vector <SDL_Texture*>();

	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_1.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_2.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_3.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_4.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_5.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_6.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_7.png", renderer));
	itemAnimations->push_back(Texture::LoadTexture("../images/items/Coin_8.png", renderer));

	return itemAnimations;
}

vector <SDL_Texture*>* Animation::loadAbilityTextures(string ability, SDL_Renderer* renderer)
{
	vector <SDL_Texture*>* abilityTextures = new vector <SDL_Texture*>();

	abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_1.png", renderer));
	abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_2.png", renderer));
	abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_3.png", renderer));
	abilityTextures->push_back(Texture::LoadTexture("../images/baddies/Fireball_4.png", renderer));

	return abilityTextures;
}