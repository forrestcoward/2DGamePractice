#include "Animation.h"
#include "SDL.h"
#include <SDL_image.h>
#include "Texture.h"

#ifndef ITEMOBJECT
#define ITEMOBJECT

class SoundEffects;
class ItemAnimation;
class Texture;

#include <iostream>

using namespace std;

class ItemObject
{
public:
	ItemObject(vector <SDL_Texture*>* itemTextures, int x, int y, string name, int tickerCap, SDL_Renderer* renderer);
	~ItemObject();
	int ItemObject::getX();
	int ItemObject::getY();
	Animation* itemAnimation;
	SoundEffects* itemSounds;
	string name;
	void ItemObject::collectItem();
	void ItemObject::isCollidingBelow(vector <Texture*>* Terrain);
	static void ItemObject::updateItemObjectAnimations(vector <ItemObject*>* mapItems);
private:
	int x;
	int y;
};

#endif 