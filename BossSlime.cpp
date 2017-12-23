#include "BossSlime.h"
#include <math.h>


#define PI 3.14

BossSlime::BossSlime(int x, int y) : BaseNpc(x, y)
{
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = 48;
	mCollider.h = 46;

	maxHealth = 1000;
	health = maxHealth;

	damage = 15;
	shootingFrames = 0;
}

void BossSlime::shoot(Player& player, ProjectileManager& p) {
	int scale = 12;

	double angle = getAngle(player.mCollider.x + (player.mCollider.w*2), player.mCollider.y + (player.mCollider.h*2));
	double PVelY = scale * sin(angle);
	double PVelX = scale * cos(angle);
	
	angle = (angle * (180 / PI)) + 170 + (rand()%20);
	

	if (shootingFrames % 35 == 0)
	{
		p.insert(angle, (mCollider.x + mCollider.w / 2), (mCollider.y + mCollider.h / 2), PVelX / 3, PVelY / 3, damage);
	}
}

void BossSlime::setMoveDirections(Player& player)
{
	//tan(theta) = y height away/x height away
	//so actual angle = 
	//slime = (50,50)
	//player = (0,0)
	double scale = 3;
	double plX = player.getPosX();
	double plY = player.getPosY();
	if (((mCollider.x - plX) != 0 || (mCollider.y - plY) != 0) && !touchesPlayer(mCollider, player))
	{
		double angle = atan2(((plY + player.mCollider.h*2) - (mCollider.y + mCollider.h)), ((plX + player.mCollider.w*2) - (mCollider.x + mCollider.w)));
		//printf("%d", angle);

		nVelY = scale * (sin(angle));
		nVelX = scale * (cos(angle));
	}
	else
	{
		nVelY = 0.0;
		nVelX = 0.0;
	}



}

void BossSlime::targetedMove(Player& player, Tile* tiles[], ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
{

	mCollider.x += nVelX;
	
	if ((mCollider.x < 0) || (mCollider.x + 60 >  LEVEL_WIDTH) || touchesWall(mCollider, tiles) || touchesPlayer(mCollider, player))
	{
		mCollider.x -= nVelX;
		
	}

	mCollider.y += nVelY;

	if ((mCollider.y < 00) || (mCollider.y + 60 > LEVEL_HEIGHT) || touchesWall(mCollider, tiles) || touchesPlayer(mCollider, player))
	{
		mCollider.y -= nVelY;
	
	}

	frame++;
	if (frame >= 74)
	{
		frame = 0;
	}
	if (frame < 50) snum = 11;
	else if (frame < 58) snum = 12;
	else if (frame < 66) snum = 13;
	else if (frame < 74) snum = 12;

	shootingFrames++;

	if (getAlive()) die(r, gRenderer);

}


BossSlime::~BossSlime()
{
}
