#ifndef MONSTER
#define MONSTER

#include "Creature.h"

class Monster :
	public Creature
{
public:
	Monster(SDL_Texture* texture, int x, int y, int velocity, int patrolRadius, string name, SDL_Renderer* renderer);
	Monster();
	~Monster();
	static void Monster::moveAllMonsters(vector <Monster*>* mapMonsters);
	static void Monster::updateAllMonsterAnimations(vector <Monster*>* mapMonsters);
private:
	int distanceFromOrigin;
	int patrolRadius;
};

#endif