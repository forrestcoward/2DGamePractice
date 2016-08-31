#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#ifndef BLOCK
#define BLOCK

class Block{
public: 
	int x;
	int y;
	int w;
	int h;
	SDL_Texture* texture;
	Block(SDL_Texture* texture, int x, int y);
};
#endif BLOCK