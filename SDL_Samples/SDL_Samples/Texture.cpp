#include <string>
#include <SDL_image.h>
#include "Texture.h"
using namespace std;

/*
 * Load a texture from a file.
 */
SDL_Texture* Texture::LoadTexture(const string &file, SDL_Renderer *renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	// We can use IMG_GetError() to get the error message.
	return texture;
}

/*
 * Renders a texture onto a renderer.
 */
void Texture::RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	RenderTexture(texture, renderer, x, y, w, h);
}

/*
 * Renders a texture onto a renderer with a specified with and height.
 */
void Texture::RenderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}
