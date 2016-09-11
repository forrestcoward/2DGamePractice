#ifndef TEXTURE
#define TEXTURE


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Texture.h"

using namespace std;

class Texture;

class Creature
{
public: 
	int x;
	int y;
	int w;
	int h;
	double gravity;
	int velocity;
	double verticalVelocity;
	bool jumping;
	SDL_Texture* texture;
	Creature(SDL_Texture* texture, int x, int y, int velocity);
	bool Creature::isCollidingBelow(vector <Texture>* Terrain);
	void Creature::jump(vector <Texture>* Terrain);
	void Creature::jumpAdjust();
	void Creature::checkLand(vector <Texture>* Terrain);
};
#endif