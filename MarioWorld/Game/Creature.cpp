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

//Constructor for mario
Creature::Creature(SDL_Texture* texture, int x, int y, int velocity, string name, SDL_Renderer* renderer)
{
	characterAnimation = new Animation(texture, name, 4, renderer);
	jumping = false;
	gravity = 1;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	this->name = name;
	ability = "none";
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

//Constructor for bad guys
Creature::Creature(SDL_Texture* texture, int x, int y, int velocity, int patrolRadius, string name, SDL_Renderer* renderer)
{
	characterAnimation = new Animation(texture, name, 3, renderer);
	jumping = false;
	gravity = 1;
	this->x = x;
	this->y = y;
	this->patrolRadius = patrolRadius;
	distanceFromOrigin = 0;
	this->name = name;
	ability = "none";
	this->velocity = velocity;
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

//Checks if this creature is on the ground
bool Creature::isCollidingBelow(vector <Texture*>* Terrain)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		if ((y + h >= (*Terrain)[i]->getY()) && (((x + w <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x + w) >= ((*Terrain)[i]->getX()) || (x <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x  >= ((*Terrain)[i]->getX())))
		{
			y = (*Terrain)[i]->getY() - h;
			return true;
		}
	}
	
	return false;
}

//Mario jumps
void Creature::jump(vector <Texture*>* Terrain)
{
	if (Creature::isCollidingBelow(Terrain) && !jumping)
	{
		jumping = true;
		verticalVelocity = -12;
		characterAnimation->updateAnimation(velocity, jumping);
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
void Creature::checkLand(vector <Texture*>* Terrain) 
{
	if (Creature::isCollidingBelow(Terrain) && jumping)
	{
		jumping = false;
		verticalVelocity = 0;
		characterAnimation->updateAnimation(velocity, jumping);
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

//Moves creature based on velocity
void Creature::move()
{
		x += velocity;
}

