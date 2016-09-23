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
	int originalHeight;
	SDL_Texture* texture;
	AbilityAnimation();
	AbilityAnimation(string name, SDL_Renderer* renderer);
	~AbilityAnimation();
	vector <SDL_Texture*>* abilityTextures;
	int AbilityAnimation::getW();
	int AbilityAnimation::getH();
	void AbilityAnimation::setAnimations(string abilityName, SDL_Renderer* renderer); 
	int AbilityAnimation::getAnimationFrame();
	void AbilityAnimation::updateAbilityTexture();
private:
	int animationFrameTickerCap;
	int animationFrameTicker;
	int animationFrame;
	int w;
	int h;
};
#endif
