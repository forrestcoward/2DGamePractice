#include <iostream>
#include <string>
#include <SDL_image.h>
#ifndef TEXTURE
#define TEXTURE
using namespace std;

class Texture{
public:
	static SDL_Texture* LoadTexture(const string &file, SDL_Renderer *renderer);
	static void RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
	static void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
private:
	int x;
	int y;
};
#endif TEXTURE
