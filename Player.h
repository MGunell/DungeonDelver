#ifndef __Player__
#define __Player__

class Tile;
class Weapon;
class ProjectileManager; 
class Inventory;
#include "ProjectileManager.h"
#include "SDL.h"
#include "LTexture.h"


const int scale = 2;
const int LEVEL_WIDTH = 16 * 64 * 1.5;
const int LEVEL_HEIGHT = 12 * 64 * 1.5;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

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
	void heal(int amount) { 
	if (health + amount < 100) health += amount;
	else health = 100;
	}
	int getDamage();
	int getLevel();
	void attack(const SDL_Rect& a, const SDL_Rect& B, int x, int y);
	void dealDamage(int damage);

	void LevelUp();

	//void setWeapon(Weapon* weapon);
	//Weapon* getWeapon();
	SDL_Rect mCollider;
private:

	bool attacking;
	bool attackable = true;
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

	//the chat box
	SDL_Rect chatBubble;
	SDL_Rect healthBox;
	SDL_Rect* maxHealthBox1;
	SDL_Rect maxHealthBox;
	//Inventory pInventory;

	//velocity
	int mVelX, mVelY;

	int health;
	int maxHealth;
	int level;
	int damage;
	int dexterity;
	int swordRange;
	//Weapon* pWeapon = new Weapon("bear hands", 1, 0);
	//Weapon equippedWeapon;
};

void loadPlayerMedia(SDL_Renderer* gRenderer);
bool touchesWall(SDL_Rect box, Tile* tiles[]);

static LTexture gSpriteSheetTexture;
static SDL_Rect gSpriteClips[18];

#endif