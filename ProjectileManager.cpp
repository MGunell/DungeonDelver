#include "ProjectileManager.h"
#include <cassert>

ProjectileManager::ProjectileManager()
{
	used = -1;
	index = 0;
	projectiles = new Projectile[50];
}

void ProjectileManager::start() {
	if (used == 0) index = 1;
	else index = 0;
}

void ProjectileManager::advance()
{
	assert(index < 30);
	index++;
}

void ProjectileManager::renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, BaseNpc* enemy[])
{
	if (used > -1) {
		for (int i = 0; i < used; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (projectiles[i].move(enemy[j]) == true)
				{
					projectiles[i].renderProjectile(camera, gRenderer);

				}
			}
			
		}
	}
			
}

void ProjectileManager::insert(double angle, int x, int y, double velX, double velY, int damage)
{
	projectiles[index] = Projectile(angle - 90, x, y, velX, velY, 25 + damage);
	//projectiles[index].setAngle(angle - 90);
	if (used <= 0) used = 1;
	else used++;
	index++;
	if (index >= 10)//capacity - 1)
	{
		index = 0;
	}
}


