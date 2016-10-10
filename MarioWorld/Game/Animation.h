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
	int w;
	int h;
	Animation();
	Animation::Animation(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, int tickerCap, SDL_Renderer* renderer, bool isMario);
	Animation::Animation(vector <SDL_Texture*>* itemAnimations, int tickerCap, SDL_Renderer* renderer);
	~Animation();
	SDL_Texture* texture;
	void Animation::updateAnimation(int velocity, bool jumping);
	void Animation::updateMonsterAnimation(int velocity, bool jumping);
	void Animation::updateItemAnimation();
	void Animation::updateAbilityAnimation();
	void Animation::updateDirection(bool direction, int* velocity);
	void Animation::updateMonsterDirection();
	bool Animation::getDirection();
	static vector <SDL_Texture*>* Animation::loadRightMarioTextures(SDL_Renderer* renderer);
	static vector <SDL_Texture*>* Animation::loadLeftMarioTextures(SDL_Renderer* renderer);
	static vector <SDL_Texture*>* Animation::loadRightKoopaTextures(SDL_Renderer* renderer);
	static vector <SDL_Texture*>* Animation::loadLeftKoopaTextures(SDL_Renderer* renderer);
	static vector <SDL_Texture*>* Animation::loadItemTextures(SDL_Renderer* renderer);
private:
	bool facingRight;
	int animationFrame;
	int animationTicker;
	int animationTickerCap;
	vector <SDL_Texture*>* rightAnimations;
	vector <SDL_Texture*>* leftAnimations;
	vector <SDL_Texture*>* abilityAnimations;
	vector <SDL_Texture*>* itemAnimations;
};

#endif
