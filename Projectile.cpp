#include "Projectile.h"

Projectile::Projectile(bool alive1, double angle1, int x, int y, double VelX, double VelY, int damage1, int range1, int speed1, int mtype)
{
	pposx = x;
	pposy = y;
	pposw = 30;
	pposh = 18;
	angle = angle1;

	pVelX = VelX;
	pVelY = VelY;

	damage = damage1;
	range = 10;
	speed = 3;
	mType = 0;
	alive = alive1;
	lifetime = range * 64;

	clip = 0;
}

bool loadProjectileMedia(SDL_Renderer* gRenderer)
{
	
	bool success = true;

	if (!projectileSheets.loadFromFile("images/projectiles.png", gRenderer))
	{
		printf("failed the projectile png");
	}
	else
	{
		sprites1[1].x = 39;
		sprites1[1].y = 79;
		sprites1[1].w = 30;
		sprites1[1].h = 18;

		sprites1[2].x = 80;
		sprites1[2].y = 79;
		sprites1[2].w = 30;
		sprites1[2].h = 18;

		sprites1[3].x = 122;
		sprites1[3].y = 79;
		sprites1[3].w = 30;
		sprites1[3].h = 18;

		sprites1[0].x = 7;
		sprites1[0].y = 79;
		sprites1[0].w = 30;
		sprites1[0].h = 18;

		sprites1[4].x = 10;
		sprites1[4].y = 42;
		sprites1[4].w = 11;
		sprites1[4].h = 9;

		sprites1[5].x = 24;
		sprites1[5].y = 42;
		sprites1[5].w = 13;
		sprites1[5].h = 9;

		sprites1[6].x = 39;
		sprites1[6].y = 42;
		sprites1[6].w = 11;
		sprites1[6].h = 9;

		sprites1[7].x = 24;
		sprites1[7].y = 42;
		sprites1[7].w = 11;
		sprites1[7].h = 9;
	}

	return success;
}

void Projectile::renderProjectile(SDL_Rect& camera, SDL_Renderer* gRenderer, int clips)
{
	
		//show tile
		
		projectileSheets.render(pposx - camera.x, pposy - camera.y, &sprites1[clip + (4*clips)], gRenderer, angle);
	
}

bool Projectile::move(BaseNpc* enemy)
{
	lifetime -= speed;
	aliveLength++;
	if (lifetime > 0)
	{
		if (!checkHit(enemy->mCollider) || enemy->getAlive())
		{
			pposx += pVelX;
			pposy += pVelY;
			
			if (aliveLength % 20 == 0)
			{
				clip++;
				if (clip > 3) clip = 1;
			}

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

bool Projectile::enemyMove(Player& enemy)
{
	lifetime -= speed;
	aliveLength++;
	if (lifetime > 0)
	{
		if (!checkHit(enemy.mCollider))
		{
			pposx += pVelX;
			pposy += pVelY;

			if (aliveLength % 20 == 0)
			{
				clip++;
				if (clip > 3) clip = 1;
			}

			return true;
		}
		else
		{
			enemy.dealDamage(damage);
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

