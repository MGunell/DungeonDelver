#pragma once
#include "Weapon.h"
#include "LTexture.h"

class BaseNpc;

class Projectile
{
public:
	Projectile(int x = 0, int y = 0, double VelX = 0, double VelY = 0,int damage1 = 25.0, int range1 = 10, int speed1 = 5, int mtype = 0);
	bool move(BaseNpc& enemy);
	friend bool loadProjectileMedia(SDL_Renderer* gRenderer);
	void renderProjectile(SDL_Rect& camera, SDL_Renderer* gRenderer);
	bool alive;

	bool checkHit(SDL_Rect enemy);
private:

	int damage;
	int range;
	int speed;

	double pVelX, pVelY;
	double pposx, pposy;
	double pposw, pposh;

	SDL_Rect mCollider;
	int mType;
	int lifetime;
};