#include "AbilityObject.h"
#include "Texture.h"
#include "AbilityAnimation.h"


//Default Constructor
AbilityObject::AbilityObject(int x, int y, bool direction, string abilityName, SDL_Renderer* renderer)
{
	this->x = x;
	this->y = y;
	if (direction)
		velocity = 4;
	else
		velocity = -4;
	verticalVelocity = -4;
	abilityAnimation = new AbilityAnimation(abilityName, renderer);
}

//Deconstructor
AbilityObject::~AbilityObject()
{
}

//Return X
int AbilityObject::getX()
{
	return x;
}

//Return Y
int AbilityObject::getY()
{
	return y;
}

//Return H
int AbilityObject::getH()
{
	return h;
}

//Return W
int AbilityObject::getW()
{
	return w;
}

//Check if object is on the ground
bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		if ((y + h >= (*Terrain)[i]->getY()) && (((x + w <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x + w) >= ((*Terrain)[i]->getX()) || (x <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x >= ((*Terrain)[i]->getX())))
		{
			y = (*Terrain)[i]->getY() - h;
			return true;
		}
	}

	return false;
}

//Move this AbilityObject on x-axis
void AbilityObject::moveX()
{
	x += velocity;
}

//Move this AbilityObject on y-axis
void AbilityObject::moveY()
{
	y += verticalVelocity;
}