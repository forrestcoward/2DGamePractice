#ifndef CREATURE
#define CREATURE

class Animation;
class Texture;
class AbilityObject;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;
class Monster;
class Creature
{
public: 
	Animation* characterAnimation;
	AbilityObject* abilityObject;
	string name;
	string ability;
	int patrolRadius;
	int distanceFromOrigin;
	int x;
	int y;
	int w;
	int h;
	int gravity;
	int velocity;
	int verticalVelocity;
	bool jumping;
	Creature(SDL_Texture* texture, int x, int y, int velocity, string name, SDL_Renderer* renderer);
	Creature(SDL_Texture* texture, int x, int y, int velocity, int patrolRadius , string name, SDL_Renderer* renderer);
	Creature();
	~Creature();
	void Creature::checkDistance();
	bool Creature::isCollidingBelow(vector <Texture*>* Terrain);
	void Creature::jump(vector <Texture*>* Terrain);
	void Creature::jumpAdjust();
	void Creature::checkLand(vector <Texture*>* mapTerrain);
	void Creature::checkBorders();
	void Creature::move();
	void Creature::setAbility(string ability);
	void Creature::useAbility(SDL_Renderer* renderer);
	void Creature::updateAbilityAnimations();
	void Creature::moveAbilityObjects(vector <Texture*>* mapTerrain);
	void Creature::checkStompingMonster(vector <Monster*>* mapMonsters);
	void Creature::die();
};

#endif CREATURE