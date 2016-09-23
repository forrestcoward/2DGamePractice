#ifndef ABILITYOBJECT
#define ABILITYOBJECT

class Texture;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

class AbilityObject
{
public:
	bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain);
	void AbilityObject::getX();
	void AbilityObject::getY();
	void AbilityObject::getW();
	void AbilityObject::getH();
	AbilityObject();
	~AbilityObject();
private:
	int x;
	int y;
	int w;
	int h;
};
#endif
