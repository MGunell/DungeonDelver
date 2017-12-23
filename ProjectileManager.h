#ifndef __ProjectileManager__
#define __ProjectileManager__

class BaseNpc;
class Player;
class Projectile;
#include "Projectile.h"
#include "SDL.h"


class ProjectileManager {
public:
	ProjectileManager();
	const int capacity = 50;
	void renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, BaseNpc* enemy[]);
	void renderAllEnemy(SDL_Rect& camera, SDL_Renderer* gRenderer, Player& player);

	void insert(double angle, int x,int y, double velX, double velY, int damage, int range1 = 5);
	void remove_current();
	void start();
	void advance();
private:
	Projectile* projectiles;
	int used;
	int index;
};
#endif