#ifndef CREATURE
#define CREATURE

class Monster;
class Animation;
class Texture;
class AbilityObject;
class SoundEffects;
class ItemObject;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>

using namespace std;


class Creature
{
public: 
	SoundEffects* creatureSounds;
	Animation* characterAnimation;
	AbilityObject* abilityObject;
	string name;
	string ability;
	int patrolRadius;
	int distanceFromOrigin;
	int x;
	int y;
	int w;
	int h;
	int gravity;
	int velocity;
	int verticalVelocity;
	bool jumping;
	bool dying;
	Creature::Creature(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, vector <Mix_Chunk*>* marioSounds, int x, int y, int velocity, string name, SDL_Renderer* renderer);
	//Creature::Creature(vector <SDL_Texture*>* rightAnimations, vector <SDL_Texture*>* leftAnimations, int x, int y, int velocity, int patrolRadius , string name, SDL_Renderer* renderer); 
	Creature();
	~Creature();
	void Creature::checkAbilityDistance();
	bool Creature::isCollidingBelow(vector <Texture*>* Terrain);
	void Creature::jump(vector <Texture*>* Terrain);
	void Creature::jumpAdjust();
	void Creature::checkLand(vector <Texture*>* mapTerrain);
	void Creature::checkBorders();
	void Creature::move();
	void Creature::setAbility(string ability);
	void Creature::useAbility(vector <SDL_Texture*>* animations, SDL_Renderer* renderer);
	void Creature::updateAbilityAnimations();
	void Creature::moveAbilityObjects(vector <Texture*>* mapTerrain, vector <Monster*>* mapMonsters, vector <ItemObject*>* mapItems, vector <SDL_Texture*>* koopaShellTextures, vector <Mix_Chunk*>* koopaShellSounds, SDL_Renderer* renderer);
	void Creature::checkStompingMonster(vector <Monster*>* mapMonsters);
	void Creature::die();
	void Creature::stompJump();

};

#endif CREATURE