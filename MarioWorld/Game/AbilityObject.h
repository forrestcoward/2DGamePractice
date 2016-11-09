#ifndef ABILITYOBJECT
#define ABILITYOBJECT


class Texture;
class Animation;
class Monster;
class Creature;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

class AbilityObject
{
public:
	int maxHeight;
	int height;
	int x;
	int y;
	int velocity;
	int verticalVelocity;
	Animation* abilityAnimation;
	bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain);
	bool AbilityObject::hitMonster(vector<Monster*>* mapMonsters);
	void AbilityObject::checkHeight();
	void AbilityObject::moveX();
	void AbilityObject::moveY();
	int AbilityObject::getMaxDistance();
	int AbilityObject::getDistanceTraveled();
	AbilityObject::AbilityObject(vector <SDL_Texture*>* animations, int x, int y, bool direction, SDL_Renderer* renderer);
	~AbilityObject();
private:
	int distanceTraveled;
	int maxDistance;
};
#endif
