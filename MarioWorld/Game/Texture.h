#ifndef CREATURE
#define CREATURE

#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "Creature.h"


using namespace std;

class Creature;

class Texture
{
public:
	static void Texture::cutSprites(SDL_Texture *spriteSheet, vector <SDL_Rect>* spriteClips);
	static SDL_Texture* LoadTexture(const string &file, SDL_Renderer *renderer);
	static void Texture::RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
	static void Texture::RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);
	static void Texture::RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst, SDL_Rect *clip = nullptr);
	static vector <Texture> Texture::CreateTextureVector(vector<SDL_Rect>& clips, string fileName, SDL_Texture* spriteSheet);
	static void Texture::RenderAllTerrain(vector <Texture> Terrain, SDL_Renderer *renderer, double offset);
	int Texture::getY();
	int Texture::getX();
	int Texture::getW();
	int Texture::getH();
private:
	int x;
	int y;
	int w;
	int h;
	SDL_Rect Clip;
	SDL_Texture* spriteSheet;
};

#endif