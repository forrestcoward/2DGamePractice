#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Texture.h"
#include "Block.h"
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
const int NUMBER_OF_BLOCKS = 10;
const int MOVEMENT = 3;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* SCREEN_TITLE = "Sample";

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create the window we will draw on.
	SDL_Window* window = SDL_CreateWindow(SCREEN_TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// Create the renderer. This will draw to the window.
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Create the mario texture.
	SDL_Texture* mario_texture = Texture::LoadTexture("../images/mario_right_still.png", renderer);
	// Create background texture.
	SDL_Texture* background_texture = Texture::LoadTexture("../images/backgrounds/Icy_Background.png", renderer);
	SDL_Texture* koopa_texture = Texture::LoadTexture("../images/baddies/Koopa_Red_Left_1.png.", renderer);
	SDL_Texture* block_texture = Texture::LoadTexture("../images/items/Question_Block_0.png", renderer);

	vector<Block>blocks;
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
	{
		int x = rand() % SCREEN_WIDTH;
		int y = rand() % SCREEN_HEIGHT;
		blocks.push_back(Block(block_texture, x, y));
	}
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
	{
		Block b = blocks[i];
		int width = b.w;
		int height = b.h;
	}
	//mario starts at 100,100
	Block mario = Block(mario_texture, 100, 100);

	SDL_Event e;

	bool running = true;

	while (running)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

			// If a key was pressed.
			if (e.type == SDL_KEYDOWN)
			{
				// Detect which key was pressed.
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					if (mario.y < MOVEMENT){
						mario.y = 0;
					}
					else{
						mario.y -= MOVEMENT;
					}
					break;
				case SDLK_DOWN:
					if ((mario.y + mario.h) >= (SCREEN_HEIGHT - MOVEMENT)){
						mario.y = (SCREEN_HEIGHT - mario.h);
					}
					else{
						mario.y += 3;
					}
					break;
				case SDLK_LEFT:
					if (mario.x < MOVEMENT){
						mario.x = 0;
					}
					else{
						mario.x -= MOVEMENT;
					}
					break;
				case SDLK_RIGHT:
					if ((mario.x + mario.w)>(SCREEN_WIDTH - MOVEMENT)){
						mario.x = (SCREEN_WIDTH - mario.w);
					}
					else{
						mario.x += 3;
					}
					break;
				default:
					break;
				}
			}
		}
		// Clear the screen.
		SDL_RenderClear(renderer);
		Texture::RenderTexture(background_texture, renderer, 0, 0);

		for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
		{
			Texture::RenderTexture(blocks[i].texture, renderer, blocks[i].x, blocks[i].y);
			//Block(blocks, x, y);
		}
		// Draw mario at the (x, y) location.
		Texture::RenderTexture(mario.texture, renderer, mario.x, mario.y);
		Texture::RenderTexture(koopa_texture, renderer, 300, 200);




		// Print the screen.
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(mario_texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

