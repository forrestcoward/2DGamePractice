#include <string>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include "Texture.h"
#include "Creature.h"
#include "Animation.h"
#include "Monster.h"
#include "AbilityObject.h"
#include "AbilityAnimation.h"

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 380;
const int BACKGROUND_WIDTH = 960;

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
 * Renders a texture onto the screen with a specified width and height.
 */
void Texture::RenderTexture(SDL_Rect* camera, SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x - camera->x;
	dst.y = y;
	dst.h = h;
	dst.w = w;
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

/*
* Renders a clip of a texture.
*/
void Texture::RenderTexture(SDL_Rect* camera, SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
	SDL_Rect dst;
	dst.x = x - camera->x; 
	dst.y = y;
	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
		SDL_QueryTexture(texture, NULL, NULL, &dst.w ,&dst.h);

	RenderTexture(camera, texture, renderer, dst, clip);
}

/* 
* Renders a clipped texture.
*/ 
void Texture::RenderTexture(SDL_Rect* camera, SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst, SDL_Rect *clip)
{
	SDL_RenderCopy(renderer, texture, clip, &dst);
}

/*
* Cuts up the spritesheet.
*/
vector <SDL_Rect>* Texture::cutSprites(SDL_Texture* spriteSheet)
{
	vector <SDL_Rect>* spriteClips = new vector <SDL_Rect>();
	SDL_Rect tempClip;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			tempClip.x = 48 * j;
			tempClip.y = 32 * i;
			tempClip.w = 48;
			tempClip.h = 32;
			spriteClips->push_back(tempClip);
		}	
	}

	return spriteClips;
}

//Return vector of level terrain textures
Creature* Texture::createLevelObjects(vector<SDL_Rect>*clips, string fileName, SDL_Texture* spriteSheet, vector <Texture*>* mapTerrain, vector <Monster*>* mapMonsters, SDL_Texture* backgroundTexture, SDL_Renderer* renderer)
{
	Creature* mario = NULL;
	int currentX = 0;
	int currentY = SCREEN_HEIGHT - 32;
	char currentCharacter;
	ifstream levelFile;
	levelFile.open(fileName);

	while (levelFile >> noskipws >> currentCharacter)
	{
		if (currentCharacter == 'a')
		{
			Texture* newTerrain = new Texture();
			newTerrain->x = currentX;
			newTerrain->y = currentY;
			newTerrain->h = (*clips)[0].h;
			newTerrain->w = (*clips)[0].w;
			newTerrain->Clip = (*clips)[0];
			newTerrain->spriteSheet = spriteSheet;
			mapTerrain->push_back(newTerrain);
		}
		else if (currentCharacter == 'b')
		{
			Texture* newTerrain = new Texture();
			newTerrain->x = currentX;
			newTerrain->y = currentY;
			newTerrain->h = (*clips)[1].h;
			newTerrain->w = (*clips)[1].w;
			newTerrain->Clip = (*clips)[1];
			newTerrain->spriteSheet = spriteSheet;
			mapTerrain->push_back(newTerrain);
		}
		else if (currentCharacter == 'm')
		{
			SDL_Texture* marioTexture = Texture::LoadTexture("../images/mario_right_still.png", renderer);
			mario = new Creature(marioTexture, currentX, currentY, 0, "mario", renderer);
			mario->w = 16;
			mario->h = 27;
			mario->characterAnimation->setAnimations(renderer, mario->name);
		}
		else if (currentCharacter == 'k')
		{
			SDL_Texture* koopaTexture = Texture::LoadTexture("../images/baddies/Koopa_Red_Left_1.png", renderer);
			Monster* newKoopa = new Monster(koopaTexture, currentX, currentY, -2, 100, "koopa", renderer);
			newKoopa->w = 16;
			newKoopa->h = 27;
			newKoopa->characterAnimation->setAnimations(renderer, newKoopa->name);
			mapMonsters->push_back(newKoopa);
		}
		else if (currentCharacter == '#')
		{
			currentX += 48;
			currentY = SCREEN_HEIGHT - 32;
		}
		else if(currentCharacter == '0')
		{
			currentY += 32;
		}
			
			
	}

	return mario;
}

//Return w
int Texture::getW()
{
	return this->w;
}

//Return h
int Texture::getH() 
{
	return this->h;
}

//Renders bad guys
void Texture::renderAllMonsters(SDL_Rect* camera, vector <Monster*>* mapMonsters, vector<Texture*>* mapTerrain, SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i < mapMonsters->size(); i++)
	{
		(*mapMonsters)[i]->checkLand(mapTerrain);
		Texture::RenderTexture(camera, (*mapMonsters)[i]->characterAnimation->texture, renderer, (*mapMonsters)[i]->x, (*mapMonsters)[i]->y);
	}
}

//Renders terrain
void Texture::renderAllTerrain(SDL_Rect* camera, vector <Texture*>* Terrain, SDL_Renderer *renderer)
{
	for (unsigned int i = 0; i < Terrain->size(); i++)
	{
		Texture::RenderTexture(camera, (*Terrain)[i]->spriteSheet, renderer, (*Terrain)[i]->x, (*Terrain)[i]->y, &(*Terrain)[i]->Clip);
	}
}

// Return y
int Texture::getY()
{
	return this->y;
}

//Return x 
int Texture::getX()
{
	return this->x;
}

//Move camera
void Texture::moveCamera(SDL_Rect* camera, Creature* mario)
{
			if (mario->x < SCREEN_WIDTH / 2)//Beginning of level
		{
			camera->x = 0;
		}
		else if (mario->x > BACKGROUND_WIDTH - SCREEN_WIDTH / 2)//End of level
		{
			camera->x = BACKGROUND_WIDTH - SCREEN_WIDTH;//change BACKGROUND_WIDTH to LEVEL_WIDTH once determined
		}
		else
		{
			camera->x = mario->x - SCREEN_WIDTH / 2;
		}
}

//Render all textures
void Texture::renderAllTextures(SDL_Rect* camera, SDL_Texture* backgroundTexture, Creature* mario, vector <Texture*>* mapTerrain, vector <Monster*>* mapMonsters, SDL_Renderer* renderer)
{
	Texture::RenderTexture(camera, backgroundTexture, renderer, 0, 0);
	Texture::renderAllTerrain(camera, mapTerrain, renderer);
	Texture::renderAllMonsters(camera, mapMonsters, mapTerrain, renderer);
	Texture::RenderTexture(camera, mario->characterAnimation->texture, renderer, mario->x, mario->y);
	Texture::renderAllAbilityObjects(camera, mario->abilityObjects, renderer);
	SDL_RenderPresent(renderer);
}

//Render all ability objects
void Texture::renderAllAbilityObjects(SDL_Rect* camera, vector <AbilityObject*>* abilityObjects, SDL_Renderer* renderer)
{
	if (abilityObjects != NULL)
	{
		for (unsigned int i = 0; i < abilityObjects->size(); i++)
		{
			Texture::RenderTexture(camera, (*abilityObjects)[i]->abilityAnimation->texture, renderer, (*abilityObjects)[i]->x, (*abilityObjects)[i]->y);
		}
	}
}
