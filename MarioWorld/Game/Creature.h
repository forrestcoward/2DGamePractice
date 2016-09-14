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
	bool facingRight;
	int animationFrame;
	string name;
	int x;
	int y;
	int w;
	int h;
	vector <SDL_Texture*>* clipsRight;
	vector <SDL_Texture*>* clipsLeft;
	double gravity;
	int velocity;
	double verticalVelocity;
	bool jumping;
	SDL_Texture* texture;
	Creature(SDL_Texture* texture, int x, int y, int velocity, string name);
	bool Creature::isCollidingBelow(vector <Texture>* Terrain);
	void Creature::jump(vector <Texture>* Terrain);
	void Creature::jumpAdjust();
	void Creature::checkLand(vector <Texture>* Terrain);
	void Creature::checkMarioBorders();
	void Creature::setClips(SDL_Renderer* renderer);
	void Creature::updateAnimation();
	void Creature::move();
	void Creature::updateDirection(bool direction);
};
#endif