#include "Monster.h"



Monster::Monster(SDL_Texture* texture, int x, int y, int velocity, string name, Animation* animation, SDL_Renderer* renderer, string ability = "none")
{
	characterAnimation = new Animation(name, 4, renderer);
	hasAbility = false;
	this->ability = ability;
	animationTicker = 0;
	facingRight = true;
	animationFrame = 0;
	this->name = name;
	jumping = false;
	gravity = 1;
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->velocity = velocity;
	verticalVelocity = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}


