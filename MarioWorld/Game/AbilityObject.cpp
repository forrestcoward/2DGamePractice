#include "AbilityObject.h"
#include "Texture.h"
#include "AbilityAnimation.h"


//Default Constructor
AbilityObject::AbilityObject(int x, int y, bool direction, string abilityName, SDL_Renderer* renderer)
{
	maxDistance = 122;
	distanceTraveled = 0;
	maxHeight = 32;
	height = 0;
	this->x = x;
	this->y = y;
	if (direction)
		velocity = 4;
	else
		velocity = -8;
	verticalVelocity = 4;
	abilityAnimation = new AbilityAnimation(abilityName, renderer);
}

//Deconstructor
AbilityObject::~AbilityObject()
{
	abilityAnimation->~AbilityAnimation();
	//delete abilityAnimation;
}

//Check if object is on the ground
bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		if ((y + abilityAnimation->getH() >= (*Terrain)[i]->getY()) && (((x + abilityAnimation->getW() <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x + abilityAnimation->getW()) >= ((*Terrain)[i]->getX()) || (x <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x >= ((*Terrain)[i]->getX())))
		{
			y = (*Terrain)[i]->getY() - abilityAnimation->getH();
			verticalVelocity = -verticalVelocity;
			height = 8;
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