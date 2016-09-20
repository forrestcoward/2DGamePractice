#include "Animation.h"
#include "Texture.h"


//Deafult constructor
Animation::Animation()
{
}

//Constructor
Animation::Animation(SDL_Texture* texture, string name, int tickerCap, SDL_Renderer* renderer)
{
	Animation::setClips(renderer, name);
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
	else if (name == "koopa")
	{
		//Set right clips
		rightClips->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Right_1.png", renderer));
		rightClips->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Right_2.png", renderer));

		//Set left clips
		leftClips->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Left_1.png", renderer));
		leftClips->push_back(Texture::LoadTexture("../images/baddies/Koopa_Red_Left_2.png", renderer));
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
			texture = (*rightClips)[animationFrame];
		else
			texture = (*leftClips)[animationFrame];
	}
	else
	{
		if (facingRight)
		{
			texture = (*rightClips)[3];
		}
		else
		{
			texture = (*leftClips)[3];
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
			texture = (*rightClips)[animationFrame];
		else
			texture = (*leftClips)[animationFrame];
	}
	else
	{
		if (facingRight)
		{
			texture = (*rightClips)[3];
		}
		else
		{
			texture = (*leftClips)[3];
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
