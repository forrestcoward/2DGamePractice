#include "AbilityObject.h"


//Default Constructor
AbilityObject::AbilityObject()
{
}


//Deconstructor
AbilityObject::~AbilityObject()
{
}

//Return X
void AbilityObject::getX()
{

}

//Return Y
void AbilityObject::getY()
{

}

//Return H
void AbilityObject::getH()
{
	
}

//Return W
void AbilityObject::getW()
{

}

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