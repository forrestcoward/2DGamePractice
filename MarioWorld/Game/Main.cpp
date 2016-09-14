#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <time.h>
#include <string>
#include <tchar.h>
#include <vector>

// SDL includes.
// See https://www.libsdl.org/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// Poco includes.
// We use Poco to avoid dealing with awful file system utilities provided to us by C++.
// See http://pocoproject.org/
#include <Poco\File.h>
#include "Poco/FileStream.h"
#include <Poco\Path.h>
#include <Poco\DirectoryIterator.h>

#include <iostream>

// Our own includes.
#include "Texture.h"
#include "Creature.h"

using namespace std;

double OFFSET = 0;
const int MARIO_WIDTH = 16;
const int MARIO_HEIGHT = 27;
const int BACKGROUND_WIDTH = 960;
const int NUMBER_OF_BLOCKS = 10;
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;
const int MARIO_STARTING_X = 100;
const int MARIO_STARTING_Y = SCREEN_HEIGHT - 32;
int MARIO_STARTING_VELOCITY = 5;
const char* SCREEN_TITLE = "Mario World";

// Sets an environment variables value.
void SetEnvironmentVarible(char* environmentVariable, char* value)
{
	_putenv_s(environmentVariable, value);
}

// Gets the value of an environment variable.
// If it does not exist, write a message to the console and exit with an error.
char* GetEnvironmentVariable(const char * environmentVariable)
{
	char* variable;
	size_t requiredSize;

	// Get the size of the environment variable.
	getenv_s(&requiredSize, NULL, 0, environmentVariable);

	// Error out if it does not exist.
	if (requiredSize == 0)
	{
		printf("Environment variable %s does not exist", environmentVariable);
		exit(1);
	}

	// Allocate space to store the value of the environment variable.
	variable = (char*)malloc(requiredSize * sizeof(char));
	// Get the actual environment variable.
	getenv_s(&requiredSize, variable, requiredSize, environmentVariable);

	return variable;
}

string GetRandomMp3File()
{
	Poco::Path p("../sounds/midi", Poco::Path::Style::PATH_WINDOWS);
	Poco::DirectoryIterator dirIterator(p);
	Poco::DirectoryIterator end;
	std::vector<std::string> files;
	std::string file;

	// Get all the files in the mp3 directory.
	while (dirIterator != end)
	{
		file = dirIterator->path();
		++dirIterator;
		files.push_back(file);
	}

	// Choose a random file to play a different song each time.
	srand(time(NULL)); // Initialize random seed.
	int random = rand();
	int randomIndex = random % files.size();
	string musicToPlay = files[randomIndex];
	cout << "Playing music '" << musicToPlay << "'" << endl;
	return musicToPlay;
}

void PlayMusic()
{
	// This is required if you want SDL_Mixer to be able to play .mid files.
	// We must point the TIMIDITY_CFG environment variable to the timidity download location.
	SetEnvironmentVarible("TIMIDITY_CFG", "../timidity");
	char* timidity = GetEnvironmentVariable("TIMIDITY_CFG");
	// Double check we set the variable correctly.
	cout << timidity << endl;

	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 640);
	string musicToPlay = GetRandomMp3File();
	Mix_Music *music = Mix_LoadMUS(musicToPlay.c_str());
	// Loop the music forever.
	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
	int r = Mix_PlayMusic(music, -1);

	// Play a wav.
	// Mix_Chunk* sound = Mix_LoadWAV("../sounds/bird.wav");
	// Mix_PlayChannel(-1, music, 0);
}

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	PlayMusic();

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

	//mario starts at 100,100, with velocity speed 5.
	Creature* mario =  new Creature(mario_texture, MARIO_STARTING_X, MARIO_STARTING_Y, 0, "mario");
	mario->w = MARIO_WIDTH;
	mario->h = MARIO_HEIGHT;

	//Set mario's animations
	mario->setClips(renderer);

	//background scroll speed
	double background_x = 0;

	SDL_Event e;
	bool running = true;

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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
					mario->jump(&mapTerrain);
					//mario->y += mario->velocity;
					break;
				case SDLK_LEFT:
					mario->velocity = -MARIO_STARTING_VELOCITY;
					mario->updateDirection(false);
					mario->updateAnimation();
					mario->move();
					break;
				case SDLK_RIGHT:
					mario->velocity = MARIO_STARTING_VELOCITY;
					mario->updateDirection(true);
					mario->updateAnimation();
					mario->move();
					break;
				default:
					break;
				}
			}
			else
			{
				mario->velocity = 0;
				mario->updateAnimation();
			}
		}

		Texture::moveCamera(&camera, mario);
		mario->jumpAdjust();
		mario->checkLand(&mapTerrain);
		mario->checkMarioBorders();

		// Clear the screen.
		SDL_RenderClear(renderer);

		//Draw background
		Texture::RenderTexture(&camera, background_texture, renderer, 0, 0);	

		// Draw mario at the (x, y) location.
		Texture::RenderTexture(&camera, mario->texture, renderer, mario->x, mario->y);

		//Draw the map terrain
		Texture::RenderAllTerrain(&camera, &mapTerrain, renderer);

		//Draw the screen.
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(mario_texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


// GameObject
// -> x
// -> y
// -> Texture
// Render


// AnimatedGameObject : GameObject (Inheritence)
// if mario is jumping -> set the texture to jumping
// How do I update my animations?
// Render
// base.Render
// override Render 


// AnimatedGameObject (Composition)
// -> GameObject
// -> GameObject->x
// -> GameObject->y
// -> GameObject->Render




// RenderGame( list of GameObject )


