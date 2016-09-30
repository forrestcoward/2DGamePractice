#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#ifndef ITEMANIMATION
#define ITEMANIMATION

using namespace std;

class ItemAnimation
{
public:
	int w;
	int h;
	SDL_Texture* currentTexture;
	vector <SDL_Texture*>* itemAnimations;
	ItemAnimation();
	ItemAnimation(SDL_Texture* texture, string name, int tickerCap, SDL_Renderer* renderer);
	void ItemAnimation::updateAnimation();
	void ItemAnimation::setItemAnimations(string name, SDL_Renderer* renderer);
	~ItemAnimation();
private:
	int animationFrame;
	int animationFrameTicker;
	int animationFrameTickerCap;
};

#endif