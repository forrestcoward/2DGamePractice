#ifndef ABILITYOBJECT
#define ABILITYOBJECT


class Texture;
class Animation;
class Monster;
class Creature;
class ItemObject;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>

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
	bool AbilityObject::hitMonster(vector<Monster*>* mapMonsters, vector <ItemObject*>* mapItems, vector <SDL_Texture*>* koopaShellTextures, vector <Mix_Chunk*>* koopaShellSounds, SDL_Renderer* renderer);
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
