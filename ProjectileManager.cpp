#include "ProjectileManager.h"
#include <cassert>
int Slimes = 1;

ProjectileManager::ProjectileManager()
{
	used = 0;
	index = 0;
	projectiles = new Projectile[50];
}

void ProjectileManager::start() {
	 index = 0;
}

void ProjectileManager::advance()
{
	assert(index < 30);
	index++;
}

void ProjectileManager::renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, BaseNpc* enemy[])
{
		for (int i = 0; i < used; i++)
		{		
			for (int j = 0; j < 3; j++)
			{
				if (projectiles[i].move(enemy[j]) == true)
				{
					projectiles[i].renderProjectile(camera, gRenderer);
				}

				else
				{
					if (i != used - 1)
					{
						projectiles[i] = projectiles[used - 1];
						used--;
						index--;
						//move the last projectile in the list into the first unused one
					}
				}
			}
		}
			
}

void ProjectileManager::renderAllEnemy(SDL_Rect& camera, SDL_Renderer* gRenderer, Player& player)
{
	for (int i = 0; i < used; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			if (projectiles[i].enemyMove(player))
			{
				projectiles[i].renderProjectile(camera, gRenderer, 0);
			}

			else
			{
				if (i != used - 1)
				{
					projectiles[i] = projectiles[used - 1];
					used--;
					index--;
					//move the last projectile in the list into the first unused one
				}
			}
		}
	}

}

void ProjectileManager::insert(double angle, int x, int y, double velX, double velY, int damage, int range1)
{
	projectiles[index] = Projectile(true, angle-180, x - projectiles[index].pposw, y - projectiles[index].pposh, velX, velY, damage, range1);
	//projectiles[index].setAngle(angle - 90);
	used++;
	index++;
	if (index >= capacity)
	{
		index = 0;
	}
	//std::cout << "insterted a projectile" << "used " << used << " index " << index-1 << std::endl;
}


