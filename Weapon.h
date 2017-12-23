#ifndef __Weapon__
#define __Weapon__

#include "Projectile.h"
#include "LTexture.h"
#include "Renderable.h"

class Weapon : public Renderable
{
public:
	Weapon(int x1, int y1, int resolution, int clip, SDL_Renderer* gRenderer) : Renderable(x1, y1, resolution)
	{
		setSpriteFile("images/weapons.png", gRenderer);
		setSprite(0);
	}

	virtual void addProjectile();

private:
	LTexture* Sprite;
	Projectile* projectile;
	int damage;
	int Projectiles;
	double angle;

};



#endif