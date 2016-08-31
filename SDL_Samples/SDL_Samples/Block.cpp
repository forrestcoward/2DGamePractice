#include <iostream>
#include "Block.h"
#include <SDL.h>
#include <SDL_image.h>

Block::Block(SDL_Texture* texture, int x, int y){
	this->texture = texture;
	this->x = x;
	this->y = y;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}