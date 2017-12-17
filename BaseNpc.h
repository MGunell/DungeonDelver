#ifndef __BaseNpc__
#define __BaseNpc__

class Tile;
class ProjectileManager;
class Player;
#include "LTexture.h"
#include "SDL.h"
#include "Player.h"


bool checkCollision(SDL_Rect a, SDL_Rect b);
bool touchesWall(SDL_Rect box, Tile* tiles[]);
bool touchesPlayer(SDL_Rect box, Player player);

class BaseNpc
{
public:
	BaseNpc(int x, int y);
	
	virtual void move(Player player, Tile* tiles[]);
	virtual void targetedMove(Player& player, Tile* tiles[], ProjectileManager& p);
	virtual void setMoveDirections(Player& player);
	virtual void dealDamage(int pdamage);

	virtual void render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip);
	virtual bool getAlive();
	int nPosX, nPosY;
	double nVelX, nVelY;
	int frame, clock, v1;

	SDL_Rect mCollider;
	SDL_Rect healthbox;
	SDL_Rect* healthbox1;

	double width;


	double getxDirection(Player& player );
	double getyDirection(Player& player );

	int snum = 0;
	double health;
	double maxHealth;
	bool damaged;
	bool dead;

};

static SDL_Rect currentSprite[2];
static LTexture gSpriteSheetTexture2;

void loadLevelOneMobs();
bool loadSlimeMedia(SDL_Renderer* gRenderer);
#endif