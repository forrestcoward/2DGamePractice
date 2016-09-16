#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
public:
	Monster(SDL_Texture* texture, int x, int y, int velocity, string name, Animation* animation, SDL_Renderer* renderer, string ability);
private:
	int patrolRadius;
	bool hasAbility;
};

