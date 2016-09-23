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
	SDL_Texture* texture;
	AbilityAnimation();
	AbilityAnimation(string name, SDL_Renderer* renderer);
	~AbilityAnimation();
	vector <SDL_Texture*>* abilityTextures;
	int AbilityAnimation::getW();
	int AbilityAnimation::getH();
	void AbilityAnimation::setTextures(string abilityName, SDL_Renderer* renderer); 
	int AbilityAnimation::getAnimationFrame();
private:
	int animationFrame;
	int w;
	int h;
};
#endif
