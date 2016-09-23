#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"
#include "Animation.h"
#include "Texture.h"
#include "AbilityObject.h"
#include "AbilityAnimation.h"

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
	abilityObjects = NULL;
	characterAnimation = new Animation(texture, name, 4, renderer);
	jumping = false;
	gravity = 1;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	this->name = name;
	ability = "fireball";
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

//Constructor for bad guys
Creature::Creature(SDL_Texture* texture, int x, int y, int velocity, int patrolRadius, string name, SDL_Renderer* renderer)
{
	abilityObjects = NULL;
	characterAnimation = new Animation(texture, name, 3, renderer);
	jumping = false;
	gravity = 1;
	this->x = x;
	this->y = y;
	this->patrolRadius = patrolRadius;
	distanceFromOrigin = 0;
	this->name = name;
	ability = "fireball";
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

//Set ability
void Creature::setAbility(string ability) 
{
	this->ability = ability;
}

//Use ability
void Creature::useAbility(SDL_Renderer* renderer)
{
	if (abilityObjects == NULL)
	{
		abilityObjects = new vector <AbilityObject*>();
		abilityObjects->push_back(new AbilityObject(x + w, y + h/2, characterAnimation->getDirection(), ability, renderer));
	}
}

//Update ability animations
void Creature::updateAbilityAnimations()
{
	if (abilityObjects != NULL)
	{
		for (unsigned int i = 0; i < abilityObjects->size(); i++)
		{
			(*abilityObjects)[i]->abilityAnimation->AbilityAnimation::updateAbilityTexture();
		}
	}
}

//Move all ability objects
void Creature::moveAbilityObjects(vector <Texture*>* mapTerrain)
{
	if (abilityObjects != NULL)
	{
		for (unsigned int i = 0; i < abilityObjects->size(); i++)
		{
			(*abilityObjects)[i]->x += (*abilityObjects)[i]->velocity;
			(*abilityObjects)[i]->y += (*abilityObjects)[i]->verticalVelocity;
			(*abilityObjects)[i]->height += abs((*abilityObjects)[i]->verticalVelocity);
			(*abilityObjects)[i]->isCollidingBelow(mapTerrain);
			(*abilityObjects)[i]->checkHeight();
		}
	}
}

