#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;
const int BACKGROUND_WIDTH = 960;

Creature::Creature(SDL_Texture* texture, int x, int y, int velocity, string name)
{
	animationFrame = 0;
	facingRight = true;
	this->name = name;
	jumping = false;
	gravity = .5;
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
		if ((y + h >= (*Terrain)[i].getY()) && (((x + w < (*Terrain)[i].getX() + (*Terrain)[i].getW())) && (x + w) > ((*Terrain)[i].getX()) || (x < (*Terrain)[i].getX() + (*Terrain)[i].getW())) && (x  > ((*Terrain)[i].getX())))
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
		verticalVelocity = -9;
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
void Creature::checkMarioBorders()
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
	clipsLeft = new vector <SDL_Texture*>();
	clipsRight = new vector <SDL_Texture*>();
	if (name == "mario")
	{
		//Set right clips
		clipsRight->push_back(Texture::LoadTexture("../images/mario/mario_right_still.png", renderer));
		clipsRight->push_back(Texture::LoadTexture("../images/mario/mario_right_1.png", renderer));
		clipsRight->push_back(Texture::LoadTexture("../images/mario/mario_right_2.png", renderer));
		clipsRight->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Right.png", renderer));
		
		//Set left clips
		clipsLeft->push_back(Texture::LoadTexture("../images/mario/mario_left_still.png", renderer));
		clipsLeft->push_back(Texture::LoadTexture("../images/mario/mario_left_1.png", renderer));
		clipsLeft->push_back(Texture::LoadTexture("../images/mario/mario_left_2.png", renderer));
		clipsLeft->push_back(Texture::LoadTexture("../images/mario/Mario_Big_Jump_Left.png", renderer));
	}
}

//Moves creature based on velocity
void Creature::move()
{
	x += velocity;
}

//Updates creature direction
void Creature::updateDirection(bool direction)
{
	if (facingRight != direction)
	{ 
		facingRight = direction;
		velocity = 0;
	}
		
}

//Update animation
void Creature::updateAnimation()
{
	if (!jumping)
	{
		if (velocity < 0 && !facingRight)//Facing left and not standing
		{
			animationFrame++;
		}
		else if (velocity > 0 && facingRight)//Facing right and not standing
		{
			animationFrame++;
		}
		else
		{
			animationFrame = 0;
		}

		if (animationFrame == 3)
			animationFrame = 1;

		if (facingRight)
			texture = (*clipsRight)[animationFrame];
		else
			texture = (*clipsLeft)[animationFrame];
		if (texture == NULL)
			cout << NULL << endl;
	}
	else 
	{
		if (facingRight)
		{
			texture = (*clipsRight)[3];
		}
		else
		{
			texture = (*clipsLeft)[3];
		}
	}
}
