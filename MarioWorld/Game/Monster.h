#ifndef MONSTER
#define MONSTER

#include "Creature.h"

class Monster :
	public Creature
{
public:
	Monster::Monster(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, int x, int y, int velocity, int patrolRadius, string name, SDL_Renderer* renderer);
	Monster();
	~Monster();
	static void Monster::moveAllMonsters(vector <Monster*>* mapMonsters);
	static void Monster::updateAllMonsterAnimations(vector <Monster*>* mapMonsters);
private:
	int distanceFromOrigin;
	int patrolRadius;
};

#endif