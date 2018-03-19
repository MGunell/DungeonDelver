#ifndef __Player__
#define __Player__

class Tile;
class Weapon;
class ProjectileManager; 
class Inventory;
class Weapon;
class Level;
class EquipInv;
class Inventory3;
class Enemy;
#include "ProjectileManager.h"
#include "SDL.h"
#include "LTexture.h"
class Room;

const int scale = 2;
const int LEVEL_WIDTH = 16 * 128;
const int LEVEL_HEIGHT = 12 * 128;
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
	bool camera_offset;
	//maximum axis velocty of the player sprite
	static const int P_VEL = 7;

	Player();

	bool weaponTouch;
	bool npcTouch;

	void handleEvent(SDL_Event& e);

	void update(Level* room, ProjectileManager* p, SDL_Rect* camera, EquipInv* inv, SDL_Renderer* gRenderer, EnemyManager& enemy);
	void move(Level* level, EnemyManager& enemy);
	void knockback(Level* level, EnemyManager& enemy1, Enemy& enemy);
	void teleport(int x, int y);

	void setWeapon(Weapon* src)
	{
		equippedWeapon = src;
	}

	void renderBow(SDL_Renderer* gRenderer, SDL_Rect& camera);
	//centers camera over the dot
	void setCamera(SDL_Rect& camera);

	void render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle = 0.0, SDL_Point* center = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect* clip2 = 0);
	void shoot(ProjectileManager& pManager, int x, int y, EquipInv& inv);
	double getangle(int x, int y);

	void hotbarSlide(int x, int y);
	bool sliding, slideflag;
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
		if (health + amount < maxHealth) health += amount;
	else health = maxHealth;
	}
	int getDamage();
	int getLevel();
	void attack(const SDL_Rect& a, const SDL_Rect& B, int x, int y);
	void dealDamage(int damage);
	void leftClick(EquipInv* equip, SDL_Renderer* gRenderer, ProjectileManager* pManager, SDL_Rect* camera, Room* room);
	void LevelUp();
	void giveExperience(int amount);
	void renderBars(SDL_Renderer* gRenderer);
	void cameraPan(SDL_Rect& camera);
	bool panning;

	int coins;
	
	void selectEnemy(Enemy* target);
	void unselectEnemy();
	void setAngle();
	void strafe(Level* level, EnemyManager& enemy);
	double strafeSpeed;
	int strafeRadius;
	bool strafing;
	bool setStrafing;

	//void setWeapon(Weapon* weapon);
	//Weapon* getWeapon();
	SDL_Rect mCollider;
	Weapon* equippedWeapon;
	Inventory3* hotbar; 
	LTexture boxSprite;

	Enemy* targetedEnemy;
	double targetedAngle;

	bool shootable;
	int shootangle; //radians
	double x, y;
	double knockX, knockY;
	bool hit;
	int iFrames;

	int rotating;
	int shootingframes;
	int radius;
private:

	bool attacking;
	bool attackable = true;
	bool talked;
	bool teleporting;
	bool talkable;
	int facing;
	bool moving;
	bool shooting;
	
	
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

	SDL_Rect experienceBox;
	SDL_Rect experienceBoxMax;
	//Inventory pInventory;

	//velocity
	double mVelX, mVelY;
	
	
	int health;
	int maxHealth;
	int level;
	int damage;
	int dexterity;
	int swordRange;
	//Weapon* pWeapon = new Weapon("bear hands", 1, 0);
	//Weapon equippedWeapon;
	int experience, experienceTotal, experienceLeft, experienceTotalPrevious;

	int cX2, cY2;
};

void loadPlayerMedia(SDL_Renderer* gRenderer);
bool touchesWall(SDL_Rect box, Room* room, int offsety);

static LTexture gSpriteSheetTexture;
static SDL_Rect gSpriteClips[18];

bool checkCircleCollision(EnemyManager& enemy, Player* player, double angle = 0.0);

#endif