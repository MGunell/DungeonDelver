#pragma once
#include "Projectile.h"
class Projectile;
class BaseNpc;
class ProjectileManager
{
public:
	ProjectileManager();
	static const int capacity = 100;
	void renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, BaseNpc* enemy[]);
	void insert(double angle, int x,int y, double velX, double velY, int damage);
	void remove_current();
	void start();
	void advance();
private:
	Projectile* projectiles;
	int used;
	int index;
};