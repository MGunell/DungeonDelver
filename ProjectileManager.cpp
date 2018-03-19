#include "ProjectileManager.h"
#include "Room.h"
#include "EnemyManager.h"
#include <cassert>
int Slimes = 1;

ProjectileManager::ProjectileManager()
{
	used = 0;
	index = 0;
	projectiles = new Projectile[1000];
}

void ProjectileManager::start() {
	 index = 0;
}

void ProjectileManager::advance()
{
	assert(index < 30);
	index++;
}

void ProjectileManager::renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer, EnemyManager* eM, Room* room, Player* player)
{
		for (int i = 0; i < used; i++)
		{	
			projectiles[i].move(room);
				if (projectiles[i].checkCollide(eM) ==false)
				{
					projectiles[i].renderProjectile(camera, gRenderer, player, room->rotation);
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
			


void ProjectileManager::renderAllEnemy(SDL_Rect& camera, SDL_Renderer* gRenderer, Player& player, Room* room)
{
	for (int i = 0; i < used; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			if (projectiles[i].enemyMove(player))
			{
				projectiles[i].renderProjectile(camera, gRenderer, &player, room->rotation);
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

void ProjectileManager::insert(double angle, int x, int y, double velX, double velY, int damage, int range1, int mtype1, int speed)
{
	
	projectiles[index] = Projectile(true, angle, x, y , velX, velY, damage, range1, speed, mtype1);
	//projectiles[index].setAngle(angle - 90);
	used++;
	index++;
	if (index >= capacity)
	{
		index = 0;
	}
	//std::cout << "insterted a projectile" << "used " << used << " index " << index-1 << std::endl;
}

void ProjectileManager::insert(Projectile* projectile)
{
	projectiles[index] = *projectile;
	used++;
	index++;
	if (index >= capacity)
	{
		index = 0;
	}
}


