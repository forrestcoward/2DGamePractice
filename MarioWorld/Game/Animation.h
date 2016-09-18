#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#ifndef ANIMATION
#define ANIMATION

using namespace std;

class Animation
{
public:
	Animation();
	Animation(string name, int tickerCap, SDL_Renderer* renderer);
	bool facingRight;
	int animationFrame;
	int animationTicker;
	int animationTickerCap;
	vector <SDL_Texture*>* rightClips;
	vector <SDL_Texture*>*  leftClips;
private:
	void Animation::setClips(SDL_Renderer* renderer, string name);
};

#endif
