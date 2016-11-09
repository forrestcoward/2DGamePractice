#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"
#include "Monster.h"
#include "Animation.h"
#include "Texture.h"
#include "AbilityObject.h"
#include "SoundEffects.h"

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;
const int BACKGROUND_WIDTH = 960;

//Default Constructor
Creature::Creature()
{

}

//Constructor for mario
Creature::Creature(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, vector <Mix_Chunk*>* marioSounds, int x, int y, int velocity, string name, SDL_Renderer* renderer)
{
	creatureSounds = new SoundEffects(name, marioSounds);
	creatureSounds->runSoundTicker = 4;
	abilityObject = NULL;
	characterAnimation = new Animation(rightAnimations, leftAnimations, 4, renderer, true);
	jumping = false;
	gravity = 1;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	this->name = name;
	ability = "fireball";
	verticalVelocity = 0;
	SDL_QueryTexture((*rightAnimations)[0], NULL, NULL, &w, &h);
}

//Constructor for bad guys
Creature::Creature(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, int x, int y, int velocity, int patrolRadius, string name, SDL_Renderer* renderer)
{
	creatureSounds = NULL;
	abilityObject = NULL;
	characterAnimation = new Animation(rightAnimations, leftAnimations, 3, renderer, false);
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
	SDL_QueryTexture((*leftAnimations)[0], NULL, NULL, &w, &h);
}

//Deconstructor
Creature::~Creature()
{
	characterAnimation->~Animation();
	delete characterAnimation;
	if (creatureSounds != NULL)
		delete creatureSounds;

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
		creatureSounds->playJumpSound();
		jumping = true;
		verticalVelocity = -9;
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
		if (!jumping && creatureSounds->runSoundTicker >= 4)
		{
			creatureSounds->playRunSound();
			creatureSounds->runSoundTicker = 0;
		}
		else
		{
			creatureSounds->runSoundTicker++;
		}
}

//Set ability
void Creature::setAbility(string ability) 
{
	this->ability = ability;
}

//Use ability
void Creature::useAbility(vector <SDL_Texture*>* animations, SDL_Renderer* renderer)
{
	if (abilityObject == NULL)
	{
		abilityObject = new AbilityObject(animations, x + w, y + h / 2, characterAnimation->getDirection(), renderer);
		creatureSounds->playFireballSound();
	}
}

//Update ability animations
void Creature::updateAbilityAnimations()
{
	if (abilityObject != NULL)
	{
			abilityObject->abilityAnimation->Animation::updateAbilityAnimation();
	}

}

//Move all ability objects
void Creature::moveAbilityObjects(vector <Texture*>* mapTerrain, vector <Monster*>* mapMonsters)
{
	if (abilityObject != NULL)
	{
		abilityObject->moveX();
		abilityObject->moveY();
		abilityObject->height += abs(abilityObject->verticalVelocity);
		abilityObject->isCollidingBelow(mapTerrain);
		abilityObject->checkHeight();
		
		if (!abilityObject->hitMonster(mapMonsters))
			checkAbilityDistance();
		else
		{
			abilityObject->~AbilityObject();
			delete abilityObject;
			abilityObject = NULL;
		}
	}
}

//Check fireball distance traveled
void Creature::checkAbilityDistance()
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
		if (((y + h >= (*mapMonsters)[i]->y) && (((x + w <= (*mapMonsters)[i]->x + (*mapMonsters)[i]->w)) && (x + w) >= ((*mapMonsters)[i]->x) || (x <= (*mapMonsters)[i]->x + (*mapMonsters)[i]->w)) && (x >= ((*mapMonsters)[i]->x))) && verticalVelocity > 0)
		{
			(*mapMonsters)[i]->~Monster();
			mapMonsters->erase(mapMonsters->begin() + i);
			stompJump();
			creatureSounds->playStompSound();
		}
	}
}

//Kill this
void Creature::die()
{
	Creature::~Creature();
}

//Jump after stomp 
void Creature::stompJump()
{
	verticalVelocity = -6;
}







