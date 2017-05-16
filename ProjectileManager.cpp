#include "ProjectileManager.h"
#include <cassert>

ProjectileManager::ProjectileManager()
{
	used = 0;
	index = 0;
	projectiles = new Projectile[100];
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

void ProjectileManager::renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, BaseNpc& enemy)
{
	if (used > -1) {
		for (int i = 0; i < capacity; i++)
		{
			if (projectiles[i].move(enemy) == true)
			{
				projectiles[i].renderProjectile(camera, gRenderer);
			}
			
		}
	}
			
}

void ProjectileManager::insert(int x, int y, double velX, double velY)
{
	projectiles[index] = Projectile(x, y, velX, velY);
	index++;
	used++;
	if (index >= capacity)
	{
		index = 0;
	}
}


