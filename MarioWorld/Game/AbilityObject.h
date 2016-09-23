#ifndef ABILITYOBJECT
#define ABILITYOBJECT


class Texture;
class AbilityAnimation;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

class AbilityObject
{
public:
	int velocity;
	int verticalVelocity;
	AbilityAnimation* abilityAnimation;
	bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain);
	void AbilityObject::moveX();
	void AbilityObject::moveY();
	int AbilityObject::getX();
	int AbilityObject::getY();
	int AbilityObject::getW();
	int AbilityObject::getH();
	AbilityObject(int x, int y, bool direction, string abilityName, SDL_Renderer* renderer);
	~AbilityObject();
private:
	int x;
	int y;
	int w;
	int h;
};
#endif
