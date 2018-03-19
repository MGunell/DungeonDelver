#include "Projectile.h"
#include "EnemyManager.h"
#include "Room.h"

Projectile::Projectile(bool alive1, double angle1, int x, int y, double VelX, double VelY, int damage1, int range1, int speed1, int mtype)
{
	pposx = x;
	pposy = y;
	pposw = sprites1[mtype].w;
	pposh = sprites1[mtype].h;
	angle = angle1;

	pVelX = VelX * speed1/3.0;
	pVelY = VelY * speed1/3.0;

	damage = damage1;
	range = range1;
	speed = speed1;
	mType = 0;
	alive = alive1;
	lifetime = range * 64;

	clip = mtype;

	
}

bool loadProjectileMedia(SDL_Renderer* gRenderer)
{
	
	bool success = true;

	if (!projectileSheets.loadFromFile("images/weaponProjectiles.png", gRenderer))
	{
		printf("failed the projectile png");
	}
	else
	{
		//arrow projectiles
		//blue
		sprites1[0].x = 22;
		sprites1[0].y = 0;
		sprites1[0].w = 22;
		sprites1[0].h = 5;
		//red
		sprites1[1].x = 0;
		sprites1[1].y = 0;
		sprites1[1].w = 22;
		sprites1[1].h = 5;
		//green
		sprites1[2].x = 0;
		sprites1[2].y = 5;
		sprites1[2].w = 22;
		sprites1[2].h = 5;
		//yellow
		sprites1[3].x = 22;
		sprites1[3].y = 5;
		sprites1[3].w = 22;
		sprites1[3].h = 5;

		//broadsword projectiles
		//blue
		sprites1[4].x = 44;
		sprites1[4].y = 0;
		sprites1[4].w = 12;
		sprites1[4].h = 28;
		//red
		sprites1[5].x = 56;
		sprites1[5].y = 0;
		sprites1[5].w = 12;
		sprites1[5].h = 28 ;
		//green	
		sprites1[6].x = 80;
		sprites1[6].y = 0;
		sprites1[6].w = 12;
		sprites1[6].h = 28;
		//yellow
		sprites1[7].x = 68;
		sprites1[7].y = 0;
		sprites1[7].w = 12;
		sprites1[7].h = 28;

		//shortsword projectiles
		//blue
		sprites1[8].x = 92;
		sprites1[8].y = 0;
		sprites1[8].w = 7;
		sprites1[8].h = 8;
		//red
		sprites1[9].x = 92;
		sprites1[9].y = 8;
		sprites1[9].w = 7;
		sprites1[9].h = 8;
		//green	
		sprites1[10].x = 99;
		sprites1[10].y = 0;
		sprites1[10].w = 7;
		sprites1[10].h = 8;
		//yellow
		sprites1[11].x = 99;
		sprites1[11].y = 8;
		sprites1[11].w = 7;
		sprites1[11].h = 8;

		//staff projectiles
		//blue
		sprites1[12].x = 106;
		sprites1[12].y = 0;
		sprites1[12].w = 14;
		sprites1[12].h = 10;
		//red
		sprites1[13].x = 106;
		sprites1[13].y = 10;
		sprites1[13].w = 14;
		sprites1[13].h = 10;
		//green	
		sprites1[14].x = 120;
		sprites1[14].y = 10;
		sprites1[14].w = 14;
		sprites1[14].h = 10;
		//yellow
		sprites1[15].x = 120;
		sprites1[15].y = 0;
		sprites1[15].w = 14;
		sprites1[15].h = 10;
	}

	return success;
}

void Projectile::renderProjectile(SDL_Rect& camera, SDL_Renderer* gRenderer, Player* player, double rotation, int clips)
{
	
		//show tile
		/*double x1, y1;

		x1 = (pposx - player->x)*cos(rotation) - (pposy - player->y)*sin(rotation);
		y1 = (pposx - player->x)*sin(rotation) + (pposy - player->y)*cos(rotation);

		x1 += player->x;
		y1 += player->y;*/

		SDL_Point point = { pposw, pposh/2 };
		projectileSheets.render( pposx - camera.x, pposy - camera.y, &sprites1[clip + (4*clips)], gRenderer, angle + (rotation*180/3.14), &point);
		//SDL_Rect box = { pposx - camera.x, pposy - camera.y, pposw*4, pposh*4};
		//SDL_RenderDrawRect(gRenderer, &box);
	
}

bool Projectile::move(Room* room)
{
	lifetime -= speed;
	aliveLength++;
	if (lifetime > 0)
	{
		//pposy += pVelX * sin(-room->rotation) + pVelY * cos(-room->rotation);
		//pposx += pVelX * cos(-room->rotation) - pVelY * sin(-room->rotation);
		pposx += pVelX;
		pposy += pVelY;

		if (aliveLength % 20 == 0)
		{
			//clip++;
			//if (clip > 3) clip = 1;
		}

	}
	return false;
}

bool Projectile::checkCollide(EnemyManager* eM)
{
	node* temp = new node;
	temp = eM->head;
	while (temp != NULL)
	{
		if (checkHit(*temp->enemy) && alive)
		{
			temp->enemy->dealDamage(damage);
			lifetime = 0;
			alive = false;
			return true;
		}
		temp = temp->next;
	}
	if (lifetime < 1)
	{
		alive = false;
		return true;
	}
	return false;
}


Projectile* makeProjectile()
{
	return new Projectile(true, 180, 100, 100, 0, 5);
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

bool Projectile::checkHit(Enemy& enemy)
{
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	leftA = enemy.x - enemy.radius;
	rightA = enemy.x + enemy.radius;
	topA = enemy.y - enemy.radius;
	bottomA = enemy.y + enemy.radius;

	leftB = pposx;
	rightB = pposx + pposw;
	topB = pposy;
	bottomB = pposy + pposh;

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

