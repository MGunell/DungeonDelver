#ifndef __ProjectileManager__
#define __ProjectileManager__

class BaseNpc;
class Player;
class Projectile;
class EnemyManager;
#include "Projectile.h"
#include "SDL.h"


class ProjectileManager {
public:
	ProjectileManager();
	const int capacity = 1000;
	void renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, EnemyManager* eM, Room* room, Player* player);
	void renderAllEnemy(SDL_Rect& camera, SDL_Renderer* gRenderer, Player& player, Room* room);

	void insert(double angle, int x,int y, double velX, double velY, int damage, int range1 = 5, int mtype1 = 0, int speed = 5);
	void insert(Projectile* projectile);
	void remove_current();
	void start();
	void advance();
private:
	Projectile* projectiles;
	int used;
	int index;
};
#endif