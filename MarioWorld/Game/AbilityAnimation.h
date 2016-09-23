#ifndef ABILITYANIMATION
#define ABILITYANIMATION

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

class AbilityAnimation
{
public:
	AbilityAnimation();
	~AbilityAnimation();
	vector <SDL_Texture*>* abilityTextures;
	void AbilityAnimation::getW();
	void AbilityAnimation::getH();
private:
	void AbilityAnimation::setTextures();
	int w;
	int h;
};
#endif
