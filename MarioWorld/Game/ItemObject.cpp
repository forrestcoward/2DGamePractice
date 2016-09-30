#include "ItemObject.h"
#include "ItemSoundEffects.h"
#include "ItemAnimation.h"

//Constructor
ItemObject::ItemObject(SDL_Texture* texture, int x, int y, string name, int tickerCap, SDL_Renderer* renderer)
{
	this->x = x;
	this->y = y;
	itemAnimation = new ItemAnimation(texture, name, tickerCap, renderer);
	itemSounds = new ItemSoundEffects(name);
	this->name = name;
}


ItemObject::~ItemObject()
{

}

//Return X
int ItemObject::getX()
{
	return x;
}

//Return Y
int ItemObject::getY()
{
	return y;
}

//Collect item
void ItemObject::collectItem()
{

}

//Checks if it is on terrain
void ItemObject::isCollidingBelow(vector <Texture*>* Terrain)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		if ((y + itemAnimation->h >= (*Terrain)[i]->getY()) && (((x + itemAnimation->w <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x + itemAnimation->w) >= ((*Terrain)[i]->getX()) || (x <= (*Terrain)[i]->getX() + (*Terrain)[i]->getW())) && (x >= ((*Terrain)[i]->getX())))
		{
			y = (*Terrain)[i]->getY() - itemAnimation->h;
		}
	}
}

//Update all item 
void ItemObject::updateItemObjectAnimations(vector <ItemObject*>* mapItems)
{
	for (unsigned int i = 0; i < mapItems->size(); i++)
	{
		(*mapItems)[i]->itemAnimation->updateAnimation();
	}
}

