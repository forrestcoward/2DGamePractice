#include <string>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include "Texture.h"
#include "Creature.h"
#include "Animation.h"
#include "Monster.h"
#include "AbilityObject.h"
#include "ItemObject.h"
#include "SoundEffects.h"

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
Creature* Texture::createLevelObjects(vector <SDL_Texture*>* rightMarioTextures, vector <SDL_Texture*>* leftMarioTextures, vector <SDL_Texture*>* rightKoopaTextures, vector <SDL_Texture*>* leftKoopaTextures, vector <SDL_Texture*>* itemTextures, vector<SDL_Rect>*clips, string fileName, SDL_Texture* spriteSheet, vector <Texture*>* mapTerrain, vector <Monster*>* mapMonsters, vector <ItemObject*>* mapItems, SDL_Texture* backgroundTexture, vector <Mix_Chunk*>* marioSounds, vector <Mix_Chunk*>* itemSounds, SDL_Renderer* renderer)
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
			mario = new Creature(rightMarioTextures, leftMarioTextures, marioSounds, currentX, currentY, 0, "mario", renderer);
			mario->w = 16;
			mario->h = 27;
		}
		else if (currentCharacter == 'k')
		{
			Monster* newKoopa = new Monster(rightKoopaTextures, leftKoopaTextures, currentX, currentY, -2, 100, "koopa", renderer);
			newKoopa->w = 16;
			newKoopa->h = 27;
			mapMonsters->push_back(newKoopa);
		}
		else if (currentCharacter == 'c')
		{
			ItemObject* newCoin = new ItemObject(itemTextures, itemSounds, currentX, currentY, "coin", 2, renderer);
			newCoin->itemAnimation->h = 16;
			newCoin->itemAnimation->w = 16;
			newCoin->isCollidingBelow(mapTerrain);
			mapItems->push_back(newCoin);
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
		if((*mapMonsters)[i]->x > camera->x - 50 && (*mapMonsters)[i]->x < camera->x + SCREEN_WIDTH + 50)
			Texture::RenderTexture(camera, (*mapMonsters)[i]->characterAnimation->texture, renderer, (*mapMonsters)[i]->x, (*mapMonsters)[i]->y);
	}
}

//Renders terrain
void Texture::renderAllTerrain(SDL_Rect* camera, vector <Texture*>* terrain, SDL_Renderer *renderer)
{
	for (unsigned int i = 0; i < terrain->size(); i++)
	{
		if((*terrain)[i]->x > camera->x  -50 && (*terrain)[i]->x < camera->x + SCREEN_WIDTH +50)
			Texture::RenderTexture(camera, (*terrain)[i]->spriteSheet, renderer, (*terrain)[i]->x, (*terrain)[i]->y, &(*terrain)[i]->Clip);
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
void Texture::renderAllTextures(SDL_Rect* camera, SDL_Texture* backgroundTexture, Creature* mario, vector <Texture*>* mapTerrain, vector <Monster*>* mapMonsters, vector <ItemObject*>* mapItems, SDL_Renderer* renderer)
{
	Texture::RenderTexture(camera, backgroundTexture, renderer, 0, 0);
	Texture::renderAllTerrain(camera, mapTerrain, renderer);
	Texture::renderAllMonsters(camera, mapMonsters, mapTerrain, renderer);
	Texture::RenderTexture(camera, mario->characterAnimation->texture, renderer, mario->x, mario->y);
	Texture::renderAllAbilityObjects(camera, mario->abilityObject, renderer);
	Texture::renderAllItemObjects(camera, mapItems, renderer);
	SDL_RenderPresent(renderer);
}

//Render all ability objects
void Texture::renderAllAbilityObjects(SDL_Rect* camera, AbilityObject* abilityObject, SDL_Renderer* renderer)
{
	if (abilityObject != NULL)
	{
		Texture::RenderTexture(camera, abilityObject->abilityAnimation->texture, renderer, abilityObject->x, abilityObject->y);
	}
}

//Render all map items
void Texture::renderAllItemObjects(SDL_Rect* camera, vector <ItemObject*>* mapItems, SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i < mapItems->size(); i++)
	{
		if((*mapItems)[i]->getX() > camera->x + 50 && (*mapItems)[i]->getX() < camera->x + SCREEN_WIDTH + 50)
			Texture::RenderTexture(camera, (*mapItems)[i]->itemAnimation->texture, renderer, (*mapItems)[i]->getX(), (*mapItems)[i]->getY());
	}
}
