#ifndef TEXTURE
#define TEXTURE


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Texture.h"
#include "Animation.h"

using namespace std;

class Texture;

class Animation;

class Creature
{
public: 
	Animation* characterAnimation;
	bool facingRight;
	int animationFrame;
	int animationTicker;
	string name;
	int x;
	int y;
	int w;
	int h;
	vector <SDL_Texture*>* rightClips;
	vector <SDL_Texture*>* leftClips;
	int gravity;
	int velocity;
	int verticalVelocity;
	bool jumping;
	string ability;
	SDL_Texture* texture;
	Creature(SDL_Texture* texture, int x, int y, int velocity, string name, SDL_Renderer* renderer);
	Creature();
	Creature(SDL_Texture* texture, int x, int y, int velocity, string name);
	bool Creature::isCollidingBelow(vector <Texture>* Terrain);
	void Creature::jump(vector <Texture>* Terrain);
	void Creature::jumpAdjust();
	void Creature::checkLand(vector <Texture>* Terrain);
	void Creature::checkBorders();
	void Creature::setClips(SDL_Renderer* renderer);
	void Creature::updateAnimation();
	void Creature::move();
	void Creature::updateDirection(bool direction);
};
#endif

