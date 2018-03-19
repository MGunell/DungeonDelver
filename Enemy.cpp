#include "Enemy.h"
#include "EnemyManager.h"


void hyperCubeBoss::revivePawns()
{
	for (int i = 0; i < aliveCubes; i++)
	{
		cubeProtectors[i]->hp = cubeProtectors[i]->hpMax;
		cubeProtectors[i]->alive = true;
		eM1->insertEnemy(cubeProtectors[i]);
	}
}
void hyperCubeBoss::update()
{
	//here we have the multiple phases
	
	//phase 1, main cube doesn't move, and other cubes move around in a circle// they are immine to damage, but reflecct projectile, main boss can take damage
	if (phase == 0)
	{
		//every 10 seconds shoot a volley of spiral missiles for 5 seconds
		//as health gets lower summon more cubes
		//first one spawns at 80%, then 60%, then 40%, then 20%
		if (frames == 600)
		{
			shootingVolley = true;
		}
		if (shootingVolley)
		{
			shootVolley();
		}
		else
		{
		//	shootCircleVolley();
		}
		double hpratio = hp / (hpMax * 1.0);
		if (hpratio < .8 && aliveCubes == 0)
		{
			aliveCubes++;
			eM1->insertEnemy( cubeProtectors[0] );
		}
		if (hpratio < .6 && aliveCubes == 1)
		{
			aliveCubes++;
			eM1->insertEnemy( cubeProtectors[1] );
		}
		if (hpratio < .4 && aliveCubes == 2)
		{
			aliveCubes++;
			eM1->insertEnemy( cubeProtectors[2] );
		}
		if (hpratio < .2 && aliveCubes == 3)
		{
			aliveCubes++;
			eM1->insertEnemy( cubeProtectors[3] );
		}
		moveCubes(radius * 2, radius * 2);
		shootCubes();
		frames++;
		if (hpratio < .005)
		{
			hp = hpMax;
			alive = true;
			phase++;
			moveAll();
			spreading = true;
			frames = 0;
		}
		if (frames >= 1200) frames = 0;
	}
	if (phase == 1)
	{
		//now, spread the cubes pretty far out
		if (spreading)
		{
			setTargets();
			spreadCubes(radius * 10);
		}
		else if (lineSpreading)
		{
			lineFormation();
		}
		else
		{
			if (frames == 600)
			{
				shootingVolley = true;
				spreading = true;
			}
			if (frames == 1800)
			{
				lineSpreading = true;
				moveAll();
			}

			if (lineShooting && !lineSpreading)
			{
				cubeLineMove();
				lineShoot();
			}
			else if (shootingVolley && !spreading)
			{
				shootTriVolley();
				shootCubesTarget();
			}
			else if (!spreading && !lineSpreading)
			{
				moveCubes(radius * 10, radius * 10);
				shootCubes();
			}
			frames++;
		}
		if (frames >= 3000) frames = 0;
	}
	checkPawns();
}

bool loadHyperCubeMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!gCubeTexture1.loadFromFile("images/hypercube.png", gRenderer))
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