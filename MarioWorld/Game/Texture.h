#ifndef TEXTURE
#define TEXTURE

class Creature;
class Monster;

#include <iostream>
#include <SDL_image.h>
#include <vector>

using namespace std;

class Texture
{
public:
	static vector <SDL_Rect>* Texture::cutSprites(SDL_Texture *spriteSheet);
	static SDL_Texture* Texture::LoadTexture(const string &file, SDL_Renderer *renderer);
	static Creature* Texture::createLevelObjects(vector<SDL_Rect>* clips, string fileName, SDL_Texture* spriteSheet, vector <Texture*>* mapTerrain, vector <Monster*>* mapCreatures, SDL_Texture* backgroundTexture, SDL_Renderer* renderer);
	static void Texture::renderAllTextures(SDL_Rect* camera, SDL_Texture* backgroundTexture, Creature* mario, vector <Texture*>* mapTerrain, vector <Monster*>* mapCreatures, SDL_Renderer* renderer);
	static void moveCamera(SDL_Rect* camera, Creature* mario);
	int Texture::getY();
	int Texture::getX();
	int Texture::getW();
	int Texture::getH();
private:
	static void Texture::RenderTexture(SDL_Rect* camera, SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
	static void Texture::RenderTexture(SDL_Rect* camera, SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);
	static void Texture::RenderTexture(SDL_Rect* camera, SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst, SDL_Rect *clip = nullptr);
	static void Texture::renderAllTerrain(SDL_Rect* camera, vector <Texture*>* Terrain, SDL_Renderer *renderer);
	static void Texture::renderAllMonsters(SDL_Rect* camera, vector <Monster*>* mapCreatures, vector <Texture*>* mapTerrain, SDL_Renderer* renderer);
	double x;
	double y;
	int w;
	int h;
	SDL_Rect Clip;
	SDL_Texture* spriteSheet;
};

#endif