#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"


Creature::Creature(SDL_Texture* texture, int x, int y, int velocity)
{
	jumping = false;
	gravity = 0;
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

//Checks if this creature is on the ground
bool Creature::isCollidingBelow(vector <Texture>* Terrain)
{
	for (int i = 0; i < Terrain->size(); i++)
	{
		if ((this->y + this->h >= (*Terrain)[i].getY()) && ((this->x + this->w < (*Terrain)[i].getX() + (*Terrain)[i].getW())) && (this->x + this->w) > ((*Terrain)[i].getX()))
		{
			this->y = (*Terrain)[i].getY() - this->h;
			return true;
		}
	}
	
	return false;
}

