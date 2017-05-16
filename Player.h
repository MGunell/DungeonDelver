#pragma once
#include "stdafx.h"
#include "ProjectileManager.h"
#include "FireStaff1.h"

class Tile;
class Weapon;
class ProjectileManager;


const int scale = 2;
const int LEVEL_WIDTH = 100 + 16*32*scale;
const int LEVEL_HEIGHT = 200 + 12*32*scale;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 740;

class Player
{
public:
	int frames = 0;
	void incrementFrames();
	//dimensions of the player
	static const int P_WIDTH = 12 * scale;
	static const int P_HEIGHT = 15 * scale;

	//maximum axis velocty of the player sprite
	static const int P_VEL = 5;

	Player();

	bool weaponTouch;
	bool npcTouch;

	void handleEvent(SDL_Event& e);

	void move(Tile* tiles[], ProjectileManager& p, SDL_Rect& camera);
	void teleport(int x, int y);

	//centers camera over the dot
	void setCamera(SDL_Rect& camera);

	void render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* clip2);
	void shoot(ProjectileManager& pManager, int x, int y);
	double getangle(int x, int y);

	SDL_Rect* getClip();
	SDL_Rect getBox();
	SDL_Rect getChatBubble();
	int getpFacing();
	bool getMoving();
	bool getTalkable();
	bool getTalked();
	int getPosX();
	int getPosY();
	int getHealth();
	int getDamage();
	int getLevel();
	//void setWeapon(Weapon* weapon);
	//Weapon* getWeapon();
private:

	bool talked;
	bool teleporting;
	bool talkable;
	int facing;
	bool moving;
	bool shooting;
	bool shootable;
	int shootingframes;
	int teleportingframes = 0;
	bool teleportable = true;
	//the x and y offsets
	int mPosX, mPosY;

	//the collision box
	SDL_Rect mCollider;

	//the chat box
	SDL_Rect chatBubble;

	//velocity
	int mVelX, mVelY;

	int health;
	int level;
	int damage;
	int dexterity;
	//Weapon* pWeapon = new Weapon("bear hands", 1, 0);
	//Weapon equippedWeapon;
};

void loadPlayerMedia(SDL_Renderer* gRenderer);
bool touchesWall(SDL_Rect box, Tile* tiles[]);