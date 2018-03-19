#ifndef __BaseNpc__
#define __BaseNpc__

class Tile;
class ProjectileManager;
class Player;
class Inventory;
class Item;
class Potion;
class RenderableManager;
class Room;
#include "LTexture.h"
#include "SDL.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>




bool checkCollision(SDL_Rect a, SDL_Rect b, int offsety);
bool touchesWall(SDL_Rect box, Room* room, int offsety);
bool touchesPlayer(SDL_Rect box, Player player);

class BaseNpc
{
public:
	BaseNpc(int x, int y);
	
	double getAngle(int x, int y);
	void RenderBatch(SDL_Rect& camera, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip, Player* player, Room* room);
	virtual bool move(Player& player, Room* room, ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer);
	virtual void targetedMove(Player& player, Room* room, ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer);
	virtual void setMoveDirections(Player& player, Room* room);
	virtual void shoot(Player& player, ProjectileManager& p)
	{
		
	}
	virtual void dealDamage(int pdamage);
	void die(RenderableManager& r, SDL_Renderer* gRenderer, Player* player);
	void smoothMove(Player& player, Room* room, ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer);

	virtual void render(SDL_Rect& camera, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip, Player* player, Room* room);
	virtual bool getAlive();
	double nPosX, nPosY;
	double nVelX, nVelY;
	int frame, clock, v1;

	SDL_Rect mCollider;
	SDL_Rect healthbox;
	SDL_Rect* healthbox1;

	double width;


	double getxDirection(Player& player );
	double getyDirection(Player& player );
	std::string name;
	int snum = 0;
	double health;
	double maxHealth;
	bool damaged;
	bool dead;
	bool drops;
	bool smoothFlag;
	int xDest, yDest;
	int xDestOri, yDestOri;
	double angle_;
	int radius = 100;
	double totalDistance;

};

static SDL_Rect currentSprite[27];
static LTexture gSpriteSheetTexture2;

void loadLevelOneMobs();
bool loadSlimeMedia(SDL_Renderer* gRenderer);
#endif