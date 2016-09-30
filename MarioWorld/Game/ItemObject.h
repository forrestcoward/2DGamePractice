#include "Animation.h"
#include "SDL.h"
#include <SDL_image.h>
#include "Texture.h"

#ifndef ITEMOBJECT
#define ITEMOBJECT

class ItemSoundEffects;
class ItemAnimation;
class Texture;

#include <iostream>

using namespace std;

class ItemObject
{
public:
	ItemObject(SDL_Texture* texture, int x, int y, string name, int tickerCap, SDL_Renderer* renderer);
	~ItemObject();
	int ItemObject::getX();
	int ItemObject::getY();
	ItemAnimation* itemAnimation;
	ItemSoundEffects* itemSounds;
	string name;
	void ItemObject::collectItem();
	void ItemObject::isCollidingBelow(vector <Texture*>* Terrain);
private:
	int x;
	int y;
};

#endif 