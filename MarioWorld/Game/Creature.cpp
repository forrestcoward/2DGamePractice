#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"
#include "Animation.h"
#include "Texture.h"

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;
const int BACKGROUND_WIDTH = 960;

//Default Constructor
Creature::Creature()
{

}


Creature::Creature(SDL_Texture* texture, int x, int y, int velocity, string name, SDL_Renderer* renderer)
{
	characterAnimation = new Animation(name, 4, renderer);
	animationTicker = 0;
	facingRight = true;
	animationFrame = 0;
	this->name = name;
	jumping = false;
	gravity = 1;
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

//Constructor
Creature::Creature(SDL_Texture* texture, int x, int y, int velocity, string name)
{
	//characterAnimation = animation;
	animationTicker = 0;
	facingRight = true;
	animationFrame = 0;
	//characterAnimation->facingRight = true;
	this->name = name;
	jumping = false;
	gravity = 1;
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

//Checks if this creature is on the ground
bool Creature::isCollidingBelow(vector <Texture>* Terrain)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		if ((y + h >= (*Terrain)[i].getY()) && (((x + w <= (*Terrain)[i].getX() + (*Terrain)[i].getW())) && (x + w) >= ((*Terrain)[i].getX()) || (x <= (*Terrain)[i].getX() + (*Terrain)[i].getW())) && (x  >= ((*Terrain)[i].getX())))
		{
			y = (*Terrain)[i].getY() - h;
			return true;
		}
	}
	
	return false;
}

//Mario jumps
void Creature::jump(vector <Texture>* Terrain)
{
	if (Creature::isCollidingBelow(Terrain) && !jumping)
	{
		jumping = true;
		verticalVelocity = -12;
		updateAnimation();
	}
	//else do nothing
}

//Mario jump physics
void Creature::jumpAdjust()
{
	if (jumping)
	{
		y += (int) verticalVelocity;
		verticalVelocity += gravity;
	}
}

//Check if mario is jumping
void Creature::checkLand(vector <Texture>* Terrain) 
{
	if (Creature::isCollidingBelow(Terrain) && jumping)
	{
		jumping = false;
		verticalVelocity = 0;
		updateAnimation();
	}
	//else do nothing
}

//Stop mario at screen edges
void Creature::checkBorders()
{
	if (x <= 0)
	{
		x = 0;
	}
	else if (x + w >= BACKGROUND_WIDTH)//change BACKGROUND_WIDTH to LEVEL_WIDTH once determined
	{
		x = BACKGROUND_WIDTH - w;
	}
}

//initialize 
void Creature::setClips(SDL_Renderer* renderer)
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

//Moves creature based on velocity
void Creature::move()
{
	x += velocity;
}

/*
////////////////////////////////////////////////
NEW IMPLEMENTATIONS WITH ANIMATION CLASS USED. COMMENTED-OUT UNTIL HEADER FILE ISSUE RESOLVED.
////////////////////////////////////////////////
*/

//Updates creature direction
void Creature::updateDirection(bool direction)
{
	/* Old
	if (facingRight != direction)
	{
		facingRight = direction;
		velocity = 0;
	}
	*/
	if (characterAnimation->facingRight != direction)
	{
		characterAnimation->facingRight = direction;
		velocity = 0;
	}
}

void Creature::updateAnimation()
{
	if (!jumping)
	{
		if (velocity < 0 && !characterAnimation->facingRight && characterAnimation->animationTicker == characterAnimation->animationTickerCap)//Facing left and not standing
		{
			animationFrame++;
			characterAnimation->animationTicker = 0;
		}
		else if (velocity > 0 && characterAnimation->facingRight && characterAnimation->animationTicker == characterAnimation->animationTickerCap)//Facing right and not standing
		{
			animationFrame++;
			characterAnimation->animationTicker = 0;
		}
		else
		{
			animationFrame = 0;
			characterAnimation->animationTicker = 0;
		}

		if (animationFrame == 3 && characterAnimation->animationTicker == characterAnimation->animationTickerCap)
		{
			animationFrame = 1;
			characterAnimation->animationTicker = 0;
		}
		else
			characterAnimation->animationTicker++;

		if (characterAnimation->facingRight)
			texture = (*characterAnimation->rightClips)[animationFrame];
		else
			texture = (*characterAnimation->leftClips)[animationFrame];
	}
	else
	{
		if (characterAnimation->facingRight)
		{
			texture = (*characterAnimation->rightClips)[3];
		}
		else
		{
			texture = (*characterAnimation->leftClips)[3];
		}
	}
}

//Original update animation
/*
void Creature::updateAnimation()
{
	if (!jumping)
	{
		if (velocity < 0 && !facingRight && animationTicker == 4)//Facing left and not standing
		{
			animationFrame++;
			animationTicker = 0;
		}
		else if (velocity > 0 && facingRight && animationTicker == 4)//Facing right and not standing
		{
			animationFrame++;
			animationTicker = 0;
		}
		else if(velocity == 0)
		{
			animationFrame = 0;
			animationTicker = 3;
		}

		if (animationFrame == 3)
		{
			animationFrame = 1;
			animationTicker = 0;
		}
		else
			animationTicker++;

		if (facingRight)
			texture = (*rightClips)[animationFrame];
		else
			texture = (*leftClips)[animationFrame];
		cout << animationTicker << endl;
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
*/
