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
	int maxHeight;
	int height;
	int x;
	int y;
	int velocity;
	int verticalVelocity;
	AbilityAnimation* abilityAnimation;
	bool AbilityObject::isCollidingBelow(vector <Texture*>* Terrain);
	void AbilityObject::checkHeight();
	void AbilityObject::moveX();
	void AbilityObject::moveY();
	AbilityObject(int x, int y, bool direction, string abilityName, SDL_Renderer* renderer);
	~AbilityObject();
private:
};
#endif
