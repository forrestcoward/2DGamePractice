#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Animation.h"
#include "Texture.h"
#include "Monster.h"

//Default constructor
Monster::Monster()
{
}

//Constructor
Monster::Monster(SDL_Texture* texture, int x, int y, int velocity, int patrolRadius, string name, SDL_Renderer* renderer)
{
	characterAnimation = new Animation(texture, name, 4, renderer);
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

//Deconstructor
Monster::~Monster()
{
	characterAnimation->~Animation();
}

//Update monster animations
void Monster::updateAllMonsterAnimations(vector <Monster*>* mapMonsters)
{
	for (unsigned int i = 0; i < mapMonsters->size(); i++)
	{
		(*mapMonsters)[i]->characterAnimation->updateMonsterAnimation((*mapMonsters)[i]->velocity, (*mapMonsters)[i]->jumping);
	}
}

//Update all monster locations
void Monster::moveAllMonsters(vector <Monster*>* mapMonsters)
{
	for (unsigned int i = 0; i < mapMonsters->size(); i++)
	{

		if ((abs((*mapMonsters)[i]->distanceFromOrigin) > (*mapMonsters)[i]->patrolRadius))//Turn around
		{
			(*mapMonsters)[i]->velocity = -(*mapMonsters)[i]->velocity;
			(*mapMonsters)[i]->x += (*mapMonsters)[i]->velocity;
			(*mapMonsters)[i]->distanceFromOrigin += (*mapMonsters)[i]->velocity;
			(*mapMonsters)[i]->characterAnimation->updateMonsterDirection();
		}
		else//Keep walking
		{
			(*mapMonsters)[i]->x += (*mapMonsters)[i]->velocity;
			(*mapMonsters)[i]->distanceFromOrigin += (*mapMonsters)[i]->velocity;
		}
	}
}

