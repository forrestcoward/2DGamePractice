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
	Animation(SDL_Texture* texture, string name, int tickerCap, SDL_Renderer* renderer);
	SDL_Texture* texture;
	void Animation::updateAnimation(int velocity, bool jumping);
	void Animation::updateMonsterAnimation(int velocity, bool jumping);
	void Animation::updateDirection(bool direction, int* velocity);
	void Animation::updateMonsterDirection();
	void Animation::setClips(SDL_Renderer* renderer, string name);
private:
	bool facingRight;
	int animationFrame;
	int animationTicker;
	int animationTickerCap;
	vector <SDL_Texture*>* rightClips;
	vector <SDL_Texture*>*  leftClips;
};

#endif
