#include "Player.h"
#include <math.h>

#define PI 3.14
	
void loadPlayerMedia(SDL_Renderer* gRenderer)
{
	bool success = true;

	if (!gSpriteSheetTexture.loadFromFile("images/characters.png", gRenderer))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		gSpriteClips[0].x = 21;
		gSpriteClips[0].y = 182;
		gSpriteClips[0].w = 12;
		gSpriteClips[0].h = 17;

		gSpriteClips[1].x = 39;
		gSpriteClips[1].y = 183;
		gSpriteClips[1].w = 12;
		gSpriteClips[1].h = 17;


		//test npc sprites
		gSpriteClips[2].x = 561;
		gSpriteClips[2].y = 382;
		gSpriteClips[2].w = 10;
		gSpriteClips[2].h = 17;

		gSpriteClips[3].x = 579;
		gSpriteClips[3].y = 383;
		gSpriteClips[3].w = 10;
		gSpriteClips[3].h = 17;

		//moving left
		gSpriteClips[4].x = 635;
		gSpriteClips[4].y = 422;
		gSpriteClips[4].w = 10;
		gSpriteClips[4].h = 17;

		gSpriteClips[5].x = 617;
		gSpriteClips[5].y = 423;
		gSpriteClips[5].w = 10;
		gSpriteClips[5].h = 17;

		//moving down
		gSpriteClips[6].x = 560;
		gSpriteClips[6].y = 402;
		gSpriteClips[6].w = 14;
		gSpriteClips[6].h = 17;

		gSpriteClips[7].x = 579;
		gSpriteClips[7].y = 402;
		gSpriteClips[7].w = 14;
		gSpriteClips[7].h = 17;

		//moving up
		gSpriteClips[8].x = 560;
		gSpriteClips[8].y = 362;
		gSpriteClips[8].w = 14;
		gSpriteClips[8].h = 17;

		gSpriteClips[9].x = 579;
		gSpriteClips[9].y = 362;
		gSpriteClips[9].w = 14;
		gSpriteClips[9].h = 17;

		//player sprites moving left
		gSpriteClips[10].x = 93;
		gSpriteClips[10].y = 222;
		gSpriteClips[10].w = 14;
		gSpriteClips[10].h = 17;

		gSpriteClips[11].x = 75;
		gSpriteClips[11].y = 223;
		gSpriteClips[11].w = 14;
		gSpriteClips[11].h = 17;

		//player sprites moving down
		gSpriteClips[12].x = 20;
		gSpriteClips[12].y = 202;
		gSpriteClips[12].w = 14;
		gSpriteClips[12].h = 17;

		gSpriteClips[13].x = 38;
		gSpriteClips[13].y = 202;
		gSpriteClips[13].w = 14;
		gSpriteClips[13].h = 17;

		//player sprites moving up
		gSpriteClips[14].x = 20;
		gSpriteClips[14].y = 162;
		gSpriteClips[14].w = 14;
		gSpriteClips[14].h = 17;

		gSpriteClips[15].x = 38;
		gSpriteClips[15].y = 162;
		gSpriteClips[15].w = 14;
		gSpriteClips[15].h = 17;

		gSpriteClips[16].x = 20;
		gSpriteClips[16].y = 152;
		gSpriteClips[16].w = 12;
		gSpriteClips[16].h = 8;

		gSpriteClips[17].x = 164;
		gSpriteClips[17].y = 202;
		gSpriteClips[17].w = 14;
		gSpriteClips[17].h = 16;

		/*gSpriteClips[0].x = 21;
		gSpriteClips[0].y = 182;
		gSpriteClips[0].w = 12;
		gSpriteClips[0].h = 17;

		gSpriteClips[1].x = 39;
		gSpriteClips[1].y = 183;
		gSpriteClips[1].w = 12;
		gSpriteClips[1].h = 17;


		//test npc sprites
		gSpriteClips[2].x = 561;
		gSpriteClips[2].y = 382;
		gSpriteClips[2].w = 10;
		gSpriteClips[2].h = 17;

		gSpriteClips[3].x = 579;
		gSpriteClips[3].y = 383;
		gSpriteClips[3].w = 10;
		gSpriteClips[3].h = 17;

		//moving left
		gSpriteClips[4].x = 635;
		gSpriteClips[4].y = 422;
		gSpriteClips[4].w = 10;
		gSpriteClips[4].h = 17;

		gSpriteClips[5].x = 617;
		gSpriteClips[5].y = 423;
		gSpriteClips[5].w = 10;
		gSpriteClips[5].h = 17;

		//moving down
		gSpriteClips[6].x = 560;
		gSpriteClips[6].y = 402;
		gSpriteClips[6].w = 14;
		gSpriteClips[6].h = 17;

		gSpriteClips[7].x = 579;
		gSpriteClips[7].y = 402;
		gSpriteClips[7].w = 14;
		gSpriteClips[7].h = 17;

		//moving up
		gSpriteClips[8].x = 560;
		gSpriteClips[8].y = 362;
		gSpriteClips[8].w = 14;
		gSpriteClips[8].h = 17;

		gSpriteClips[9].x = 579;
		gSpriteClips[9].y = 362;
		gSpriteClips[9].w = 14;
		gSpriteClips[9].h = 17;

		//player sprites moving left
		gSpriteClips[10].x = 93;
		gSpriteClips[10].y = 222;
		gSpriteClips[10].w = 14;
		gSpriteClips[10].h = 17;

		gSpriteClips[11].x = 75;
		gSpriteClips[11].y = 223;
		gSpriteClips[11].w = 14;
		gSpriteClips[11].h = 17;

		//player sprites moving down
		gSpriteClips[12].x = 20;
		gSpriteClips[12].y = 202;
		gSpriteClips[12].w = 14;
		gSpriteClips[12].h = 17;

		gSpriteClips[13].x = 38;
		gSpriteClips[13].y = 202;
		gSpriteClips[13].w = 14;
		gSpriteClips[13].h = 17;

		//player sprites moving up
		gSpriteClips[14].x = 20;
		gSpriteClips[14].y = 162;
		gSpriteClips[14].w = 14;
		gSpriteClips[14].h = 17;

		gSpriteClips[15].x = 38;
		gSpriteClips[15].y = 162;
		gSpriteClips[15].w = 14;
		gSpriteClips[15].h = 17;

		gSpriteClips[16].x = 20;
		gSpriteClips[16].y = 152;
		gSpriteClips[16].w = 12;
		gSpriteClips[16].h = 8;

		gSpriteClips[17].x = 164;
		gSpriteClips[17].y = 202;
		gSpriteClips[17].w = 14;
		gSpriteClips[17].h = 16;*/

	}
}
Player::Player()
{
	talked = false;
	talkable = false;
	facing = 0;
	teleporting = false;
	moving = false;
	shooting = false;
	//initializing everything
	mCollider.x = SCREEN_WIDTH / 2;
	mCollider.y = SCREEN_HEIGHT / 2;
	mPosY = 0;
	weaponTouch = false;
	//FireStaff1 firestaff(1, 5, 5);
	//equippedWeapon = firestaff;

	//set collision box for the player oooh
	mCollider.w = P_WIDTH;
	mCollider.h = P_HEIGHT;

	mVelX = 0;
	mVelY = 0;
	health = 33; 
	maxHealth = 100;
	level = 1;
	damage = 100;
	dexterity = 20;
	swordRange = 75;

	//drawing a chatbox
	chatBubble.w = P_WIDTH;
	chatBubble.h = P_HEIGHT;
	chatBubble.x = mCollider.x;
	chatBubble.y = mCollider.y - P_HEIGHT;

	maxHealthBox = { 875 - 1, (SCREEN_HEIGHT / 3) - 1, 302, 52 };
	healthBox = { 875, SCREEN_HEIGHT / 3, ((health / maxHealth) * 300), 50 };
	maxHealthBox1 = &healthBox;
}

void Player::LevelUp()
{
	level++;
	health += 20;
	damage += 40;
	if (dexterity < 200)
	dexterity += 1;

}

void Player::handleEvent(SDL_Event& e)
{
	//if key is pressed
	if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
	{
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			shooting = true;
			break;
		case SDL_BUTTON_RIGHT:
			teleporting = true;
			break;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP && e.key.repeat == 0)
	{
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			shooting = false;
			break;
		case SDL_BUTTON_RIGHT:
			teleporting = false;
			break;
		}
	}


	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//adjust velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY -= P_VEL; facing = 14; break;
		case SDLK_s: mVelY += P_VEL; facing = 12; break;
		case SDLK_a: mVelX -= P_VEL; facing = 10; break;
		case SDLK_d: mVelX += P_VEL; facing = 0; break;
		case SDLK_q: talked = true;
		}
	}
	//key release boi
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w: mVelY += P_VEL; break;
		case SDLK_s: mVelY -= P_VEL; break;
		case SDLK_a: mVelX += P_VEL; break;
		case SDLK_d: mVelX -= P_VEL; break;
		case SDLK_q: talked = false;
		}

	}
	if (mVelY != 0 || mVelX != 0) moving = true;
	else moving = false;
	if (mVelX > 0 && mVelY == 0) facing = 0;
	if (mVelX < 0 && mVelY == 0) facing = 10;
}

void Player::move(Tile* tiles[], ProjectileManager& p, SDL_Rect& camera)
{
	//move it lefet or right
	//mPosX += mVelX;
	mCollider.x += mVelX;

	//if it collided
	//if ((mPosX < 0) || (mPosX + P_WIDTH > SCREEN_WIDTH) || checkCollision(mCollider, wall))
	if ((mCollider.x <0)|| (mCollider.x + P_WIDTH > LEVEL_WIDTH) || touchesWall(mCollider, tiles))
	{
		//then move back
		//mPosX -= mVelX;
		mCollider.x -= mVelX;
	}
	// later add in if functions for sprite boundaries hitting edge of screen which sets velocties to 0
	//mPosY += mVelY;
	mCollider.y += mVelY;
	//if collided
	//if ((mPosY < 0) || (mPosY + P_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, wall))
	if ((mCollider.y <00)|| (mCollider.y + P_HEIGHT*3/2 > LEVEL_HEIGHT) || touchesWall(mCollider, tiles))
	{
		//mPosY -= mVelY;
		mCollider.y -= mVelY;
	}

	//managing talking
	/*if (touchesNPCChat(mCollider, npcs))
	{
		talkable = true;
	}
	else if (!touchesNPCChat(mCollider, npcs))
	{
		talkable = false;
	}
	chatBubble.x = mCollider.x;
	chatBubble.y = mCollider.y - chatBubble.h;*/

	if (shooting)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		shoot(p, x + camera.x, y + camera.y);
	}
	if (teleporting)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		teleport(x + camera.x, y + camera.y);
	}
	if (attacking)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		//attack(x + camera.x, y + camera.y);
	}

}

void Player::attack(const SDL_Rect& A, const SDL_Rect& B, int x, int y)
{
	if (attackable)
	{
		double angle = getangle(x, y);
	}

}

void Player::teleport(int x, int y)
{

	if (teleportable)
	{
		double plX = mCollider.x;
		double plY = mCollider.y;
		int xscale = 5, yscale = 5;
		int distance = 150;

		int mX = x, mY = y;

		float angle = atanf(abs((plY - mY)) / abs((plX - mX)));

		if (plX >= mX && plY >= mY)
		{
			//this quadrant is bottom right, the object is top left
			xscale = -distance;
			yscale = -distance;
		}
		if (plX < mX && plY >= mY)
		{//object aboe and right
			xscale = distance;
			yscale = -distance;
		}
		if (plX >= mX && plY < mY) //object is left and below 
		{
			xscale = -distance;
			yscale = distance;
		}
		if (plX < mX && plY < mY)
		{
			yscale = distance;
			xscale = distance;
		}

		mCollider.x += cos(angle) * xscale;
		mCollider.y += sin(angle) * yscale;
		teleportingframes = 600;
	}
}

void Player::render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* clip2) //SDL_Rect& camera)
{
	gSpriteSheetTexture.renderHalf(mCollider.x - camera.x, mCollider.y - camera.y, clip, gRenderer, angle, center, flip);
	if (talkable == true)
	{
		gSpriteSheetTexture.renderHalf(mCollider.x - camera.x, (mCollider.y - 8 * scale) - camera.y, clip2,gRenderer, angle, center, flip);
	}

	
	healthBox.w = (health * 3); 
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, maxHealthBox1);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(gRenderer, &maxHealthBox);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
}

void Player::shoot(ProjectileManager& pManager, int x, int y)
{
	if (shootable)
	{
	int scale = 5;

	int mX = x, mY = y;

	double angle = getangle(x, y);

	double PVelY = scale * sin(angle);
	double PVelX = scale * cos(angle);
	angle = (angle * (180 / PI))+180;
	
		pManager.insert(angle, (mCollider.x + mCollider.w/2), (mCollider.y + mCollider.h/2), PVelX, PVelY, damage);
		shootingframes = 240;
	}
}

double Player::getangle(int x, int y)
{
	double plX = mCollider.x;
	double plY = mCollider.y;

	double angle = atan2(y- (plY + mCollider.h) , x - (plX + mCollider.w));
	
	return angle;
}

void Player::setCamera(SDL_Rect& camera)
{
	camera.x = (mCollider.x + (P_WIDTH/2)) - SCREEN_WIDTH/2 ;
	camera.y = (mCollider.y + (P_HEIGHT/2)) - SCREEN_HEIGHT/2;

	//keep camera in bounds
	if (camera.x < -camera.w/2)
	{
		camera.x = 0;
	}
	if (camera.y < -camera.h/2)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w/2)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h/2)
	{
		camera.y = LEVEL_HEIGHT - camera.h/2;
	}
}

SDL_Rect Player::getChatBubble()
{
	return chatBubble;
}

void Player::incrementFrames()
{
	if (shootingframes > 0)
	{
		shootingframes -= dexterity;
		shootable = false;
	}
	else 
	{
		shootable = true;
		shootingframes = 0;
	}

	if (teleportingframes > 0)
	{
		teleportingframes -= dexterity;
		teleportable = false;
	}
	else if (teleportingframes == 0)
	{
		teleportable = true;
		teleportingframes = 0;
	}
	frames++;
	//if (frames / 8 <= 3)frames = 1;
	if (frames / 8 >= 2) frames = 0;
}

SDL_Rect* Player::getClip()
{
	if (moving)
	{
		//return &gSpriteClips[(frames/2 % 2) ];
		return &gSpriteClips[(frames / 8) + facing];
	}
	else
	{
		return &gSpriteClips[facing];
	}
}

int Player::getDamage()
{
	return damage;
}

void Player::dealDamage(int damage) {
	health -= damage;
}

int Player::getHealth()
{
	return health;
}

int Player::getLevel()
{
	return level;
}

bool Player::getTalkable()
{
	return talkable;
}

bool Player::getTalked()
{
	return talked;
}

int Player::getpFacing()
{
	return facing;
}

bool Player::getMoving()
{
	return moving;
}

SDL_Rect Player::getBox()
{
	return mCollider;
}

int Player::getPosX()
{
	return mCollider.x;
}

int Player::getPosY()
{
	return mCollider.y;
}