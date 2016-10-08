#include "Animation.h"
#include "Texture.h"


//Deafult constructor
Animation::Animation()
{
}

//Deconstructor
Animation::~Animation()
{
	for (unsigned int i = 0; i < rightAnimations->size(); i++)
	{
		SDL_DestroyTexture((*rightAnimations)[i]);
	}
	rightAnimations->clear();
	
	for (unsigned int i = 0; i < leftAnimations->size(); i++)
	{
		SDL_DestroyTexture((*leftAnimations)[i]);
	}
	leftAnimations->clear();

	SDL_DestroyTexture(texture);
}

//Constructor
Animation::Animation(SDL_Texture* texture, string name, int tickerCap, SDL_Renderer* renderer)
{
	Animation::setAnimations(renderer, name);
	abilityAnimations = NULL;
	this->texture = texture;
	animationFrame = 0;
	animationTicker = 0; 
	animationTickerCap = tickerCap;
	if (name == "mario")
		facingRight = true;
	else
		facingRight = false;
}

//Sets the animation clips
void Animation::setAnimations(SDL_Renderer* renderer, string name)
{
	leftAnimations = new vector <SDL_Texture*>();
	rightAnimations = new vector <SDL_Texture*>();
	if (name == "mario")
	{
		//Set right clips
		rightAnimations->push_back(Texture::LoadTexture("../images/mario/mario_right_still.png", renderer));
		rightAnimations->push_back(Texture::LoadTexture("../images/mario/mario_right_1.png", renderer));
		rightAnimations->push_back(Texture::LoadTexture("../images/mario/mario_right_2.png", renderer));
		rightAnimations->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Right.png", renderer));

		//Set left clips
		leftAnimations->push_back(Texture::LoadTexture("../images/mario/mario_left_still.png", renderer));
		leftAnimations->push_back(Texture::LoadTexture("../images/mario/mario_left_1.png", renderer));
		leftAnimations->push_back(Texture::LoadTexture("../images/mario/mario_left_2.png", renderer));
		leftAnimations->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Left.png", renderer));
	}
	else if (name == "koopa")
	{
		//Set right clips
		rightAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Right_1.png", renderer));
		rightAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Right_2.png", renderer));

		//Set left clips
		leftAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Left_1.png", renderer));
		leftAnimations->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Left_2.png", renderer));
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

