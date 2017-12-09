#pragma once
#include "Weapon.h"
#include "LTexture.h"

class BaseNpc;

class Projectile
{
public:
	Projectile(double angle1 = 0, int x = -100, int y = -100, double VelX = 0, double VelY = 0, int damage1 = 25.0, int range1 = 10, int speed1 = 5, int mtype = 0);
	bool move(BaseNpc* enemy);
	friend bool loadProjectileMedia(SDL_Renderer* gRenderer);
	void renderProjectile(SDL_Rect& camera, SDL_Renderer* gRenderer);
	bool alive;

	Projectile operator= (Projectile& target)
	{
		pposx = target.pposx, pposy = target.pposy;
		pposw = target.pposw, pposh = target.pposw;
		angle = target.angle;
		pVelX = target.pVelX, pVelY = target.pVelY;

		damage = target.damage;
		range = target.range;
		speed = target.speed;
		mType = target.mType;
		alive = target.alive;
		lifetime = target.lifetime;

		return *this;
	}


	bool checkHit(SDL_Rect enemy);
	double getAngle() { return angle; }
	void setAngle(double angle1) { angle = angle1; }
private:
	int damage;
	int range;
	int speed;

	double angle;

	double pVelX, pVelY;
	double pposx, pposy;
	double pposw, pposh;

	SDL_Rect mCollider;
	int mType;
	int lifetime;
};