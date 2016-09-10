#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Texture.h"
#include "Creature.h"
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
double OFFSET = 0;
const int BACKGROUND_WIDTH = 960;
const int NUMBER_OF_BLOCKS = 10;
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;
const int MARIO_STARTING_X = 100;
const int MARIO_STARTING_Y = 100;
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

	// Create yellow block texture.
	SDL_Texture* block_texture = Texture::LoadTexture("../images/items/Question_Block_0.png", renderer);

	//Load icy tiles.
	SDL_Texture* iceBlocks;
	iceBlocks = Texture::LoadTexture("../images/tiles/Icy_Tiles.png", renderer);

	//Setup the clips for our image
	vector <SDL_Rect> tileClips;
	Texture::cutSprites(iceBlocks, &tileClips);

	//Create Terrain vector
	vector <Texture> mapTerrain = Texture::CreateTextureVector(tileClips, "level1.txt", iceBlocks);

	//mario starts at 100,100, with velocity speed 2.
	Creature* mario = &Creature(mario_texture, MARIO_STARTING_X, MARIO_STARTING_Y, 2);
	mario->w = 16;
	mario->h = 27;

	//background scroll speed
	double background_x = 0;

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
					mario->jumping = true;
					break;
				case SDLK_DOWN:
					if ((mario->y + mario->h) >= (SCREEN_HEIGHT - mario->velocity))
						mario->y = (SCREEN_HEIGHT - mario->h);
					else
						mario->y += mario->velocity;
					break;
				case SDLK_LEFT:
					if (mario->x < mario->velocity)
						mario->x = 0;
					else if(background_x < 0)
					{
						OFFSET++;
						background_x++;
					}
					break;
				case SDLK_RIGHT:
					if ((mario->x + mario->w) > (SCREEN_WIDTH - mario->velocity) )
					{
						mario->x = (SCREEN_WIDTH - mario->w);
					}
					else if(background_x <= 0)
					{
						OFFSET--;
						background_x--;
					}
					break;
				default:
					break;
				}
			}
		}
		// Clear the screen.
		SDL_RenderClear(renderer);
		//Render background.
		Texture::RenderTexture(background_texture, renderer, background_x, 0);	

		// Draw mario at the (x, y) location.
		Texture::RenderMario(renderer, mario, &mapTerrain);

		//Render the map terrain
		Texture::RenderAllTerrain(mapTerrain, renderer, OFFSET);

		// Print the screen.
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(mario_texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

