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
}

//Constructor
Animation::Animation(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, int tickerCap, SDL_Renderer* renderer, bool isMario)
{
	this->rightAnimations = rightAnimations;
	this->leftAnimations = leftAnimations;
	abilityAnimations = NULL;
	this->texture = texture;
	animationFrame = 0;
	animationTicker = 0; 
	animationTickerCap = tickerCap;
	if (isMario)
		facingRight = true;
	else
		facingRight = false;
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

void Animation::updateItemAnimation() 
{

}

void Animation::updateAbilityAnimation()
{

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