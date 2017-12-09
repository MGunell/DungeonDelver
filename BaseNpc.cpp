#include "BaseNpc.h"

SDL_Rect currentSprite[2];
LTexture gSpriteSheetTexture2;

BaseNpc::BaseNpc(int x, int y)
{
	frame = 0;
	nPosX = 0;
	nPosY = 0;
	clock = 0;
	v1 = 0;
	mCollider.x = x;
	mCollider.y = y;
	mCollider.w = 58;
	mCollider.h = 58;
	damaged = true;
	nVelX = 0;
	nVelY = 0;
	currentSprite;
	gSpriteSheetTexture2;

	maxHealth = 350;
	health = maxHealth;

	dead = false;

	
	healthbox.h = 5;
	healthbox.w = 60;
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
	int xscale, yscale;
	double scale = 2.5;
	double plX = player.getPosX();
	double plY = player.getPosY();
	if (((mCollider.x - plX) != 0 || (mCollider.y - plY) != 0) && !touchesPlayer(mCollider, player))
	{ 
		double angle = atan( ( abs(((mCollider.y-plY))  / abs((mCollider.x-plX)))) );
		//printf("%d", angle);

		if (mCollider.x >= plX && mCollider.y >= plY)
		{
			//this quadrant is bottom right, the object is top left
			xscale = -scale;
			yscale = -scale;
		}
		if (mCollider.x < plX && mCollider.y >= plY)
		{//object aboe and right
			xscale = scale;
			yscale = -scale;
		}
		if (mCollider.x >= plX && mCollider.y < plY) //object is left and below 
		{
			xscale = -scale;
			yscale = scale;
		}
		if (mCollider.x < plX && mCollider.y < plY)
		{
			yscale = scale;
			xscale = scale;
		}

		nVelY = (yscale *  (sin(angle)));
		nVelX = (xscale * (cos(angle)));
		
	}
	else
	{
		nVelY = 0.0;
		nVelX = 0.0;
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

void BaseNpc::targetedMove(Player& player, Tile* tiles[])
{
	setMoveDirections(player);
	
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
	if (frame  >= 60)
	{
		frame = 0;
	}
	if (frame >= 30) snum = 1;
	else snum = 0;

}

void BaseNpc::move(Player player, Tile* tiles[])
{
	if (clock == 0)
	{
		v1 = rand() % 50;
	}

	if (v1 == 3)
	{
		nVelX = 0;
		nVelY = 0;
		nVelX -= 3;
	}
	else
	{
		nVelX = 0;
		nVelY = 0;
	}

	mCollider.x += nVelX;

	if ((mCollider.x < 0) || (mCollider.x + 32 > LEVEL_WIDTH) || touchesWall(mCollider, tiles) || touchesPlayer(mCollider, player))
	{
		mCollider.x -= nVelX;
	}

	mCollider.y += nVelY;
	if ((mCollider.y < 0) || (mCollider.y + 32 > LEVEL_HEIGHT) || touchesWall(mCollider, tiles) || touchesPlayer(mCollider, player))
	{
		mCollider.y -= nVelY;
	}
	clock++;
	if (clock > 15) clock = 0;
	frame++;
	if ((frame >= 60))
	{
		frame = 0;
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
				healthbox.y = mCollider.y - camera.y + 60;
				healthbox.w = (health / maxHealth) * 60;

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &healthbox);

			}
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}
}

bool loadSlimeMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!gSpriteSheetTexture2.loadFromFile("images/characters.png", gRenderer))
	{
		printf("couldnt load slime stuff");
		success = false;
	}
	else
	{

		currentSprite[0].x = 126;
		currentSprite[0].y = 165;
		currentSprite[0].h = 27;
		currentSprite[0].w = 32;

		currentSprite[1].x = 159;
		currentSprite[1].y = 165;
		currentSprite[1].h = 27;
		currentSprite[1].w = 32;
	}

	return success;
}