#include "HyperCube.h"

#define PI 3.14

HyperCube::HyperCube(int x, int y) : BaseNpc(x, y)
{
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = 32;
	mCollider.h = 32;

	maxHealth = 500;
	health = maxHealth;

	damage = 20;
	shootingFrames = 0;
}

void HyperCube::shoot(Player& player, ProjectileManager& p) {
	int scale = 12;

	double angle = getAngle(player.mCollider.x + (player.mCollider.w * 2), player.mCollider.y + (player.mCollider.w * 2));
	double PVelY = scale * sin(angle);
	double PVelX = scale * cos(angle);

	angle = (angle * (180 / PI)) + 170 + (rand() % 20);


	if (frame > 106 + 22 * 6)
	{
		if (shootingFrames % 12 == 0)
		{
			p.insert(angle, (mCollider.x + mCollider.w), (mCollider.y + mCollider.h), PVelX / 2, PVelY / 2, damage);
		}
	}
}

void HyperCube::setMoveDirections(Player& player)
{
	//turrets dont move
}

void HyperCube::targetedMove(Player& player, Tile* tiles[], ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
{
	//mCollider.x += nVelX;
	if ((mCollider.x < 0) || (mCollider.x + 60 >  LEVEL_WIDTH) || touchesWall(mCollider, tiles))
	{
		mCollider.x -= nVelX;
	}

	//mCollider.y += nVelY;
	if ((mCollider.y < 00) || (mCollider.y + 60 > LEVEL_HEIGHT) || touchesWall(mCollider, tiles))
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


	if (getAlive()) die(r, gRenderer);
	shootingFrames++;
}


void HyperCube::render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip) //SDL_Rect& camera)
{
	if (!dead) {
		if (checkCollision(camera, mCollider))
		{
			gCubeTexture.renderHalf(mCollider.x - camera.x, mCollider.y - camera.y, &cubeSprites[snum], gRenderer, angle, center, flip);
			if (damaged) {

				healthbox.x = mCollider.x - camera.x;
				healthbox.y = mCollider.y - camera.y + mCollider.h * 2 + 5;
				healthbox.w = (health / maxHealth) * 50;

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, healthbox1);

			}
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}
}
bool loadCubeMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!gCubeTexture.loadFromFile("images/hypercube.png", gRenderer))
	{
		printf("couldnt load slime stuff");
		success = false;
	}
	else
	{
		cubeSprites[0].x = 0;
		cubeSprites[0].y = 0;
		cubeSprites[0].h = 32;
		cubeSprites[0].w = 32;

		cubeSprites[1].x = 32;
		cubeSprites[1].y = 0;
		cubeSprites[1].h = 32;
		cubeSprites[1].w = 32;

		cubeSprites[2].x = 64;
		cubeSprites[2].y = 0;
		cubeSprites[2].h = 32;
		cubeSprites[2].w = 32;

		cubeSprites[3].x = 96;
		cubeSprites[3].y = 0;
		cubeSprites[3].h = 32;
		cubeSprites[3].w = 32;

		cubeSprites[4].x = 128;
		cubeSprites[4].y = 0;
		cubeSprites[4].h = 32;
		cubeSprites[4].w = 32;

		cubeSprites[5].x = 160;
		cubeSprites[5].y = 0;
		cubeSprites[5].h = 32;
		cubeSprites[5].w = 32;

		cubeSprites[6].x = 192;
		cubeSprites[6].y = 0;
		cubeSprites[6].h = 32;
		cubeSprites[6].w = 32;

		cubeSprites[7].x = 224;
		cubeSprites[7].y = 0;
		cubeSprites[7].h = 32;
		cubeSprites[7].w = 32;

		cubeSprites[8].x = 256;
		cubeSprites[8].y = 0;
		cubeSprites[8].h = 32;
		cubeSprites[8].w = 32;

		cubeSprites[9].x = 0;
		cubeSprites[9].y = 32;
		cubeSprites[9].h = 32;
		cubeSprites[9].w = 32;

		cubeSprites[10].x = 32;
		cubeSprites[10].y = 32;
		cubeSprites[10].h = 32;
		cubeSprites[10].w = 32;

		cubeSprites[11].x = 64;
		cubeSprites[11].y = 32;
		cubeSprites[11].h = 32;
		cubeSprites[11].w = 32;

		cubeSprites[12].x = 96;
		cubeSprites[12].y = 32;
		cubeSprites[12].h = 32;
		cubeSprites[12].w = 32;

		cubeSprites[13].x = 128;
		cubeSprites[13].y = 32;
		cubeSprites[13].h = 32;
		cubeSprites[13].w = 32;

		cubeSprites[14].x = 160;
		cubeSprites[14].y = 32;
		cubeSprites[14].h = 32;
		cubeSprites[14].w = 32;

		cubeSprites[15].x = 192;
		cubeSprites[15].y = 32;
		cubeSprites[15].h = 32;
		cubeSprites[15].w = 32;

		cubeSprites[16].x = 224;
		cubeSprites[16].y = 32;
		cubeSprites[16].h = 32;
		cubeSprites[16].w = 32;

		cubeSprites[17].x = 256;
		cubeSprites[17].y = 32;
		cubeSprites[17].h = 32;
		cubeSprites[17].w = 32;

		cubeSprites[18].x = 0;
		cubeSprites[18].y = 64;
		cubeSprites[18].h = 32;
		cubeSprites[18].w = 32;

		cubeSprites[19].x = 32;
		cubeSprites[19].y = 64;
		cubeSprites[19].h = 32;
		cubeSprites[19].w = 32;

		cubeSprites[20].x = 64;
		cubeSprites[20].y = 64;
		cubeSprites[20].h = 32;
		cubeSprites[20].w = 32;

		cubeSprites[21].x = 96;
		cubeSprites[21].y = 64;
		cubeSprites[21].h = 32;
		cubeSprites[21].w = 32;

		cubeSprites[22].x = 128;
		cubeSprites[22].y = 64;
		cubeSprites[22].h = 32;
		cubeSprites[22].w = 32;

		cubeSprites[23].x = 160;
		cubeSprites[23].y = 64;
		cubeSprites[23].h = 32;
		cubeSprites[23].w = 32;

		cubeSprites[24].x = 192;
		cubeSprites[24].y = 64;
		cubeSprites[24].h = 32;
		cubeSprites[24].w = 32;

		cubeSprites[25].x = 224;
		cubeSprites[25].y = 64;
		cubeSprites[25].h = 32;
		cubeSprites[25].w = 32;

		cubeSprites[26].x = 256;
		cubeSprites[26].y = 64;
		cubeSprites[26].h = 32;
		cubeSprites[26].w = 32;

	}

	return success;
}
