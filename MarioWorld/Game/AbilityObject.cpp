#include "AbilityObject.h"
#include "Texture.h"
#include "Monster.h"
#include "Creature.h"
#include "ItemObject.h"



//Default Constructor
AbilityObject::AbilityObject(vector <SDL_Texture*>* animations, int x, int y, bool direction, SDL_Renderer* renderer)
{
	maxDistance = 122;
	distanceTraveled = 0;
	maxHeight = 32;
	height = 0;
	this->x = x;
	this->y = y;
	if (direction)
		velocity = 8;
	else
		velocity = -8;
	verticalVelocity = 4;
	abilityAnimation = new Animation(2, renderer, "fireball", NULL, animations);
}

//Deconstructor
AbilityObject::~AbilityObject()
{
	abilityAnimation->~Animation();
}

//Check if object is on the ground
bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		if ((y + abilityAnimation->h >= (*Terrain)[i]->getY()) && (((x + abilityAnimation->w <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x + abilityAnimation->w) >= ((*Terrain)[i]->getX()) || (x <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x >= ((*Terrain)[i]->getX())))
		{
			y = (*Terrain)[i]->getY() - abilityAnimation->h;
			verticalVelocity = -verticalVelocity;
			height = 8;
			return true;
		}
	}

	return false;
}

//Check if object hit a monster
bool AbilityObject::hitMonster(vector<Monster*>* mapMonsters, vector <ItemObject*>* mapItems, vector <SDL_Texture*>* koopaShellTextures, vector <Mix_Chunk*>* koopaShellSounds, SDL_Renderer* renderer)
{
	for (int i = 0; i < mapMonsters->size(); i++)
	{
		if ((((x + abilityAnimation->w) > (*mapMonsters)[i]->x) && (x + abilityAnimation->w) < ((*mapMonsters)[i]->x + (*mapMonsters)[i]->w)) && (((y + abilityAnimation->h) > (*mapMonsters)[i]->y)) && (((y + abilityAnimation->h) < ((*mapMonsters)[i]->y + (*mapMonsters)[i]->y))))
		{
			if ((*mapMonsters)[i]->name == "koopa")
				mapItems->push_back(new ItemObject(koopaShellTextures, koopaShellSounds, (*mapMonsters)[i]->x, (*mapMonsters)[i]->y + (*mapMonsters)[i]->h, "koopaShell", 2, renderer));
			(*mapMonsters)[i]->~Monster();
			mapMonsters->erase(mapMonsters->begin() + i);
			return true;
		}
	}
	return false;
}

//Check height
void AbilityObject::checkHeight()
{
	if (height > maxHeight)
	{
		verticalVelocity = -verticalVelocity;
		height = 0;
	}
}

//Move this AbilityObject on x-axis
void AbilityObject::moveX()
{
	x += velocity;
	distanceTraveled += abs(velocity);
}

//Move this AbilityObject on y-axis
void AbilityObject::moveY()
{
	y += verticalVelocity;
}

//Return distance traveled
int AbilityObject::getDistanceTraveled()
{
	return distanceTraveled;
}

//Return max distance
int AbilityObject::getMaxDistance()
{
	return maxDistance;
}