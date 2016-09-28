#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"
#include "Monster.h"
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
	abilityObject = NULL;
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
	abilityObject = NULL;
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

//Deconstructor
Creature::~Creature()
{
	characterAnimation->~Animation();
	delete characterAnimation;

	if (abilityObject != NULL)
	{
		abilityObject->~AbilityObject();
		delete abilityObject;
		abilityObject = NULL;
	}
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
void Creature::checkLand(vector <Texture*>* mapTerrain) 
{
	if (isCollidingBelow(mapTerrain) && jumping)
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
	if (abilityObject == NULL)
		abilityObject = new AbilityObject(x + w, y + h / 2, characterAnimation->getDirection(), ability, renderer);
}

//Update ability animations
void Creature::updateAbilityAnimations()
{
	if (abilityObject != NULL)
	{
			abilityObject->abilityAnimation->AbilityAnimation::updateAbilityTexture();
	}
}

//Move all ability objects
void Creature::moveAbilityObjects(vector <Texture*>* mapTerrain)
{
	if (abilityObject != NULL)
	{
		abilityObject->moveX();
		abilityObject->moveY();
		abilityObject->height += abs(abilityObject->verticalVelocity);
		abilityObject->isCollidingBelow(mapTerrain);
		abilityObject->checkHeight();
		checkDistance();
	}
}

//Check fireball distance traveled
void Creature::checkDistance()
{
	if (abilityObject->getDistanceTraveled() > abilityObject->getMaxDistance())
	{
		//start deleting the fireball
		abilityObject->~AbilityObject();
		delete abilityObject;
		abilityObject = NULL;
	}
}

//Check if falling on monster
void Creature::checkStompingMonster(vector <Monster*>* mapMonsters)
{
	for (unsigned int i = 0; i < mapMonsters->size(); i++)
	{
		if ((y + h >= (*mapMonsters)[i]->y) && (((x + w <= (*mapMonsters)[i]->x + (*mapMonsters)[i]->w)) && (x + w) >= ((*mapMonsters)[i]->x) || (x <= (*mapMonsters)[i]->x + (*mapMonsters)[i]->w)) && (x >= ((*mapMonsters)[i]->x)))
		{
			(*mapMonsters)[i]->~Monster();
			mapMonsters->erase(mapMonsters->begin() + i);
		}
	}
}

//Kill onject
void Creature::die()
{
	Creature::~Creature();
}
