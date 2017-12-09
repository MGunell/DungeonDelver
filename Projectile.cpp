#include "Projectile.h"

LTexture projectileSheets;
SDL_Rect sprites1[1];

Projectile::Projectile(double angle1, int x, int y, double VelX, double VelY, int damage1, int range1, int speed1, int mtype)
{
	pposx = x;
	pposy = y;
	pposw = 5;
	pposh = 6;
	angle = angle1;

	pVelX = VelX;
	pVelY = VelY;

	damage = damage1;
	range = 10;
	speed = 3;
	mType = 0;
	alive = true;
	lifetime = range * 64;
}

bool loadProjectileMedia(SDL_Renderer* gRenderer)
{
	
	bool success = true;

	if (!projectileSheets.loadFromFile("images/characters.png", gRenderer))
	{
		printf("failed the projectile png");
	}
	else
	{
		sprites1[0].x = 18;
		sprites1[0].y = 261;
		sprites1[0].w = 5;
		sprites1[0].h = 6;
	}

	return success;
}

void Projectile::renderProjectile(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	
		//show tile
		
		projectileSheets.render(pposx - camera.x, pposy - camera.y, &sprites1[0], gRenderer, angle);
	
}

bool Projectile::move(BaseNpc* enemy)
{
	lifetime -= speed;
	if (lifetime > 0)
	{
		if (!checkHit(enemy->mCollider) || enemy->getAlive())
		{
			pposx += pVelX;
			pposy += pVelY;

			return true;
		}
		else
		{
			enemy->dealDamage(damage);
			lifetime = 0;	
		}
	}
	alive = false;
	return false;

}

bool Projectile::checkHit(SDL_Rect a)
{
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = pposx;
	rightB = pposx + pposw;
	topB = pposy ;
	bottomB =pposy + pposh;

	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

