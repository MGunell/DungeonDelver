#include "HyperCube.h"

#define PI 3.14

HyperCube::HyperCube(int x, int y) : BaseNpc(x, y)
{
	name = "cube";
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = 30;
	mCollider.h = 30;

	maxHealth = 500;
	health = maxHealth;

	damage = 20;
	shootingFrames = 0;
}

void HyperCube::shoot(Player& player, ProjectileManager& p) {
	int scale = 7;

	double angle = getAngle(player.mCollider.x + (player.mCollider.w) , player.mCollider.y + (player.mCollider.w));
	double PVelY = scale * sin(angle);
	double PVelX = scale * cos(angle);

	angle = (angle * (180 / PI));


	if (frame > 106 + 22 * 6)
	{
		if (shootingFrames % 12 == 0)
		{
			p.insert(angle, (mCollider.x + mCollider.w), (mCollider.y + mCollider.h), PVelX, PVelY, damage, 5, 12);
		}
	}
}

void HyperCube::setMoveDirections(Player& player)
{
	//turrets dont move
}

void HyperCube::targetedMove(Player& player, Room* room, ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
{
	//mCollider.x += nVelX;
	if ((mCollider.x < 0) || (mCollider.x + 60 >  LEVEL_WIDTH) || touchesWall(mCollider, room, 64))
	{
		mCollider.x -= nVelX;
	}

	//mCollider.y += nVelY;
	if ((mCollider.y < 00) || (mCollider.y + 60 > LEVEL_HEIGHT) || touchesWall(mCollider, room, 64))
	{
		mCollider.y -= nVelY;
	}

	int loops = 6;
	int starts = 106;
	frame++;

	if (frame >= starts + 33 * loops)
	{
		frame = 0;
	}

	if (frame < starts) snum = 0;
	else if (frame < starts + 1 * loops) snum = 1;
	else if (frame < starts + 4 * loops) snum = 2;
	else if (frame < starts + 5 * loops) snum = 3;
	else if (frame < starts + 8 * loops) snum = 4;
	else if (frame < starts + 9 * loops) snum = 5;
	else if (frame < starts + 10 * loops) snum = 6;
	else if (frame < starts + 11 * loops) snum = 7;
	else if (frame < starts + 12 * loops) snum = 8;
	else if (frame < starts + 13 * loops) snum = 9;
	else if (frame < starts + 14 * loops) snum = 10;
	else if (frame < starts + 18 * loops) snum = 11;
	else if (frame < starts + 19 * loops) snum = 12;
	else if (frame < starts + 20 * loops) snum = 13;
	else if (frame < starts + 21 * loops) snum = 14;
	else if (frame < starts + 22 * loops) snum = 15;
	else if (frame < starts + 23 * loops) snum = 16;
	else if (frame < starts + 24 * loops) snum = 17;
	else if (frame < starts + 25 * loops) snum = 18;
	else if (frame < starts + 26 * loops) snum = 19;
	else if (frame < starts + 27 * loops) snum = 20;
	else if (frame < starts + 28 * loops) snum = 21;
	else if (frame < starts + 29 * loops) snum = 22;
	else if (frame < starts + 30 * loops) snum = 23;
	else if (frame < starts + 31 * loops) snum = 24;
	else if (frame < starts + 32 * loops) snum = 25;
	else if (frame < starts + 33 * loops) snum = 26;


	if (getAlive()) die(r, gRenderer, &player);
	shootingFrames++;
}


void HyperCube::render(SDL_Rect& camera, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip) //SDL_Rect& camera)
{
	if (!dead) {
		if (checkCollision(camera, mCollider, 0))
		{
			//gCubeTexture.renderHalf(mCollider.x - camera.x, mCollider.y - camera.y, &cubeSprites[snum], gRenderer, angle, center, flip);
			if (damaged) {

				healthbox.x = mCollider.x - camera.x;
				healthbox.y = mCollider.y - camera.y + mCollider.h*2 + 8;
				healthbox.w = (health / maxHealth) * 50;

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, healthbox1);

			}
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}
}

