#include "BaseNpc.h"
#include "RenderableManager.h"
#include <math.h>
#define PI 3.14

//extern Item* droppedItems[30];

BaseNpc::BaseNpc(int x, int y)
{
	drops = false;
	frame = 0;
	nPosX = 0;
	nPosY = 0;
	clock = 0;
	v1 = 0;
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = 48;
	mCollider.h = 46;
	damaged = true;
	nVelX = 0;
	nVelY = 0;
	currentSprite;
	gSpriteSheetTexture2;

	totalDistance = 12;

	maxHealth = 350;
	health = maxHealth;

	dead = false;

	healthbox.x = mCollider.x;
	healthbox.y = mCollider.y;
	healthbox.h = 5;
	healthbox.w = 60;
	healthbox1 = &healthbox;
	angle_ = 0;
}

double BaseNpc::getAngle(int x, int y)
{
	double plX = mCollider.x;
	double plY = mCollider.y;

	double angle = atan2(y - (plY + mCollider.h), x - (plX + mCollider.w));

	return angle;
}

void BaseNpc::die(RenderableManager& r, SDL_Renderer* gRenderer)
{
	if (!drops)
	{
		drops = true;
		srand(time(NULL));
		int whatItem = rand() % 2;
		int randx = rand() % 12;
		int randx2 = rand() % 12;
		int randy2 = rand() % 12;
		int randy = rand() % 12;
		int randyf = (randy - randy2) * 3;
		int randxf = (randx - randx2) * 3;
		switch (whatItem)
		{
		case 0:
			r.addRenderablePotion(mCollider.x + randxf, mCollider.y + randyf, 25, gRenderer);
			break;
		case 1:
			r.addRenderableManaPotion(mCollider.x + randxf, mCollider.y + randyf, 25, gRenderer);
			break;
		}
	}
}

double BaseNpc::getxDirection(Player& player) 
{
	return player.getPosX();
}

double BaseNpc::getyDirection(Player& player)
{
	return player.getPosY();
}

void BaseNpc::setMoveDirections(Player& player)
{
	//tan(theta) = y height away/x height away
	//so actual angle = 
	//slime = (50,50)
	//player = (0,0)
	double scale = 2.5;
	double plX = player.getPosX();
	double plY = player.getPosY();
	bool bouncing = touchesPlayer(mCollider, player);
	double angle = atan2(((plY + player.P_HEIGHT) - (mCollider.y + mCollider.h/2)), ((plX + player.P_WIDTH) - (mCollider.x + mCollider.w/2)));
	if (!bouncing)
	{ 
		//printf("%d", angle);
		nVelY = scale *  (sin(angle));
		nVelX = scale * (cos(angle));
		//std::cout << nVelX << ", " << nVelY << std::endl;
		
	}
	if (bouncing && !smoothFlag)
	{
		player.dealDamage(20);
		totalDistance = 80;
		smoothFlag = true;
		angle_ = angle;
		frame = 0;
		xDest = mCollider.x + radius * -cos(angle_);
		yDest = mCollider.y + radius * -sin(angle_);
	}
	

	if (smoothFlag)
	{
		nVelX = xDest - (radius * -cos(angle_));
		nVelY = yDest - (radius * -sin(angle_));
	}
	
}

void BaseNpc::smoothMove(Player& player, Tile* tiles[], ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
{
	//first get x and y distance away
	if (smoothFlag)
	{
		if (totalDistance > 0 )
		{
			
			totalDistance -= 1;
			angle_ += 2.2 * 3.14 / 180;
			mCollider.x = nVelX;
			mCollider.y = nVelY;
			//mCollider.x += (flagX - mCollider.x) % 6;
			//mCollider.y += (flagY - mCollider.y) % 6;
		}
		else
		{
			std::cout << frame;
			smoothFlag = false;
		}

		frame++;
		if (frame >= 80)
		{
			frame = 0;
		}
		if (frame < 6) snum = 3;
		else if (frame < 12) snum = 4;
		else if (frame < 18) snum = 5;
		else if (frame < 24) snum = 7;
		else if (frame < 30) snum = 8;
		else if (frame < 36) snum = 9;
		else if (frame < 42) snum = 10;
		else if (frame < 48) snum = 9;
		else if (frame < 54) snum = 8;
		else if (frame < 60) snum = 7;
		else if (frame < 66) snum = 5;
		else if (frame < 72) snum = 4;
		else snum = 3;
	}

	if (!smoothFlag)
	{
		setMoveDirections(player);
		targetedMove(player, tiles, p, r, gRenderer);
	}

}

void BaseNpc::dealDamage(int pdamage)
{
	if (!damaged) damaged = true;
	health -= pdamage;
	if (health < 0)
	{
		dead = true;
	}
}

void BaseNpc::targetedMove(Player& player, Tile* tiles[], ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
{
	mCollider.x += nVelX;
	if ((mCollider.x < 0) || (mCollider.x + 60 >  LEVEL_WIDTH) || touchesWall(mCollider, tiles))
	{
		mCollider.x -= nVelX;
	}

	mCollider.y += nVelY;
	if ((mCollider.y < 00) || (mCollider.y + 60 > LEVEL_HEIGHT) || touchesWall(mCollider, tiles))
	{
		mCollider.y -= nVelY;
	}

	int loops = 18;
	int starts = 106;
	frame++;

	if (frame  >= starts + 3*loops)
	{
		frame = 0;
	}
	
	if (frame < starts) snum = 0;
	else if (frame < starts + 1 * loops) snum = 1;
	else if (frame < starts + 2 * loops) snum = 2;
	else if (frame < starts + 3 * loops) snum = 1;
	
	

	if (getAlive()) die(r, gRenderer);
}

void BaseNpc::move(Player& player, Tile* tiles[], ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
{
	if (!dead)
	{
		setMoveDirections(player);
		shoot(player, p);
		smoothMove(player, tiles, p, r, gRenderer);
	}
	else
	{
		die(r, gRenderer);
	}

}

bool BaseNpc::getAlive()
{
	return dead;
}

void BaseNpc::render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip) //SDL_Rect& camera)
{
	if (!dead) {
		if (checkCollision(camera, mCollider))
		{
			gSpriteSheetTexture2.render(mCollider.x - camera.x, mCollider.y - camera.y, &currentSprite[snum], gRenderer, angle, center, flip);
			if (damaged) {
				
				healthbox.x = mCollider.x - camera.x;
				healthbox.y = mCollider.y - camera.y + mCollider.h + 5;
				healthbox.w = (health / maxHealth) * 50;

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, healthbox1);

			}
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}
}

void BaseNpc::RenderBatch(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	render(camera, clip, gRenderer, angle, center, flip);
}

bool loadSlimeMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!gSpriteSheetTexture2.loadFromFile("images/Slime.png", gRenderer))
	{
		printf("couldnt load slime stuff");
		success = false;
	}
	else
	{

		currentSprite[0].x = 0;
		currentSprite[0].y = 0;
		currentSprite[0].h = 46;
		currentSprite[0].w = 48;

		currentSprite[1].x = 0;
		currentSprite[1].y = 46;
		currentSprite[1].h = 46;
		currentSprite[1].w = 48;

		currentSprite[2].x = 0;
		currentSprite[2].y = 92;
		currentSprite[2].h = 46;
		currentSprite[2].w = 48;

		currentSprite[3].x = 145;
		currentSprite[3].y = 1;
		currentSprite[3].h = 43;
		currentSprite[3].w = 42;

		currentSprite[4].x = 145;
		currentSprite[4].y = 44;
		currentSprite[4].h = 43;
		currentSprite[4].w = 42;

		currentSprite[5].x = 145;
		currentSprite[5].y = 87;
		currentSprite[5].h = 43;
		currentSprite[5].w = 42;

		currentSprite[6].x = 145;
		currentSprite[6].y = 130;
		currentSprite[6].h = 43;
		currentSprite[6].w = 42;

		currentSprite[7].x = 187;
		currentSprite[7].y = 1;
		currentSprite[7].h = 43;
		currentSprite[7].w = 42;

		currentSprite[8].x = 187;
		currentSprite[8].y = 44;
		currentSprite[8].h = 43;
		currentSprite[8].w = 42;

		currentSprite[9].x = 187;
		currentSprite[9].y = 87;
		currentSprite[9].h = 43;
		currentSprite[9].w = 42;

		currentSprite[10].x = 187;
		currentSprite[10].y = 130;
		currentSprite[10].h = 43;
		currentSprite[10].w = 42;

		currentSprite[11].x = 330;
		currentSprite[11].y = 0;
		currentSprite[11].h = 46;
		currentSprite[11].w = 48;

		currentSprite[12].x = 330;
		currentSprite[12].y = 46;
		currentSprite[12].h = 46;
		currentSprite[12].w = 48;

		currentSprite[13].x = 330;
		currentSprite[13].y = 92;
		currentSprite[13].h = 46;
		currentSprite[13].w = 48;		
	}

	return success;
}