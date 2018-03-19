#include "Player.h"
#include <math.h>
#include "Equipment_Inventory.h"
#include "InventoryRedux.h"
#include "Tile.h"
#include "Room.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Level.h"
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

	radius = 32;
	camera_offset = false;
	rotating = 0;
	talked = false;
	talkable = false;
	facing = 0;
	teleporting = false;
	moving = false;
	shooting = false;
	//initializing everything
	x = 1000.0;
	y = 1000.0;
	mCollider.x = 1000;
	mCollider.y = 1000;
	mPosY = 0;
	weaponTouch = false;
	//FireStaff1 firestaff(1, 5, 5);
	//equippedWeapon = firestaff;

	//set collision box for the player oooh
	mCollider.w = 26;
	mCollider.h = 34;

	panning = false;
	sliding = false;
	slideflag = false;

	mVelX = 0;
	mVelY = 0;
	health = 100; 
	maxHealth = 100;
	level = 1;
	damage = 100;
	dexterity = 10;
	swordRange = 75;

	experience = 0;
	experienceTotal = 100;
	experienceLeft = 100;
	experienceTotalPrevious = 0;

	targetedEnemy = NULL;
	strafeSpeed = 10;
	strafeRadius = 76;
	strafing = false;
	setStrafing = false;

	//drawing a chatbox
	chatBubble.w = P_WIDTH;
	chatBubble.h = P_HEIGHT;
	chatBubble.x = mCollider.x;
	chatBubble.y = mCollider.y - P_HEIGHT;

	maxHealthBox = { 5, 5, 302, 20 };
	healthBox = { 6	, 5, ((health / maxHealth) * 300), 20 };
	maxHealthBox1 = &healthBox;

	experienceBox = { 50, SCREEN_HEIGHT - 7, 0, 5 };
	experienceBoxMax = { 49, SCREEN_HEIGHT - 8, SCREEN_WIDTH - 100, 7 };

	cX2 = 0, cY2 = 0;

	shootangle = 0;
}

void Player::selectEnemy(Enemy* target)
{
	targetedEnemy = target;
}

void Player::unselectEnemy()
{
	targetedEnemy = NULL;
}

void Player::setAngle()
{
	if (targetedEnemy != NULL)
	{
		targetedAngle = atan2(y + mCollider.h - targetedEnemy->y, x + mCollider.w - targetedEnemy->x);
	}
}


void Player::strafe(Level* level,  EnemyManager& enemy)
{
	//move in a circle around the targeted enemy. this should be fluid and smooth;
	double tX, tY;

	tX = targetedEnemy->x;
	tY = targetedEnemy->y;

	double prevAngle;
	double turnAngle;

	if (setStrafing)
	{
		setStrafing = false;
		strafeRadius = sqrt(((tY - (y + mCollider.h*2) ) * (tY - (y + mCollider.h*2)) ) + ((tX - (x + mCollider.w) ) * (tX - (x + mCollider.w) )));
		targetedAngle = -atan2( (y + mCollider.h*2) - tY, (x + mCollider.w) - tX );
	}

	//now we have to move x and y separately and check for any collisions.
	//this movement is based soley off of the angle between the two;
	//targetedAngle = atan2(y + mCollider.h - tY, x + mCollider.w - tX);
	// = targetedAngle + strafeSpeed;
	
	
	turnAngle = strafeSpeed / strafeRadius;
	prevAngle = targetedAngle;
	
	if (y + mCollider.h * 2 < tY)
	{
		if (mVelX > 0 || mVelY > 0) targetedAngle -= turnAngle;
		if (mVelX < 0 || mVelY < 0) targetedAngle += turnAngle;
	}
	else
	{
		if (mVelX > 0 || mVelY > 0) targetedAngle += turnAngle;
		if (mVelX < 0 || mVelY < 0) targetedAngle -= turnAngle;
	}
	
	//std::cout << strafeSpeed << "\n";
	//std::cout << targetedAngle << "\n";

	if (mVelX != 0 || mVelY != 0)
	{
		
		x = tX + (strafeRadius * cos(targetedAngle)) - mCollider.w;
		y = tY - strafeRadius * sin(targetedAngle) - mCollider.h * 2;
		mCollider.x = x;
		mCollider.y = y;
		if (x <= level->_Level->rooms[0]->x * 64 || x > level->_Level->rooms[0]->x * 64 + level->_Level->rooms[0]->width * 64 || touchesWall(mCollider, level->_Level->rooms[0], 64) || checkCircleCollision(enemy, this) || y - radius <= level->_Level->rooms[0]->y * 64 || y > level->_Level->rooms[0]->y * 64 + level->_Level->rooms[0]->height * 64)
		{
			x = (tX + strafeRadius * cos(prevAngle)) - mCollider.w;
			mCollider.x = x;
			y = tY - (strafeRadius * sin(prevAngle)) - mCollider.h * 2;
			mCollider.y = y;
		}
	}

}

void Player::renderBow(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
	if (equippedWeapon != NULL)
	{
		int x4, y4;
		SDL_GetMouseState(&x4, &y4);
		double angle4 = getangle(x4 + camera.x, y4 + camera.y);
		int x1, y1;
		x1 = x + mCollider.w/2;
		y1 = y ;
		int x2, y2;
		x2 = (radius-8) * cos(angle4);
		y2 = radius * sin(angle4);
		angle4 *= 180 / 3.14;
		if (!(angle4 < 90 && angle4 > -90))
		{
			angle4 -= 180;  
			if (shootangle < 0)
			{
				shootangle *= -1;
			}
		}

		equippedWeapon->render(x1 + x2 - camera.x, y1 + y2 - camera.y, gRenderer, angle4 + shootangle);
	}
}

void Player::LevelUp()
{
	level++;
	//sound.play();
	experienceTotalPrevious = experienceTotal;
	experienceTotal += experienceTotal + experienceTotal*.10;
	std::cout << experienceTotal << std::endl;
	std::cout << "Level Up" << std::endl;

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

	if (e.wheel.y == 1)
	{
		if (hotbar->selectedBox > 0)
			hotbar->selectedBox -= 1;
		
	}
	if (e.wheel.y == -1)
	{
		if (hotbar->selectedBox < hotbar->capacity - 1)
			hotbar->selectedBox += 1;
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
		case SDLK_q:
			rotating = 1;
			break;
		case SDLK_e:
			rotating = 2;
			break;
		case SDLK_t: camera_offset = !camera_offset; break;
		case SDLK_LSHIFT:
			setStrafing = true;
			strafing = true;
			panning = true;
			break;
		case SDLK_i: sliding = !sliding; slideflag = true;
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
		case SDLK_q: rotating = 0; break;
		case SDLK_e: shooting = true; break;
		case SDLK_LSHIFT: strafing = false;
			panning = true;
		}
		

	}
	if (mVelY != 0 || mVelX != 0) moving = true;
	else moving = false;
	if (mVelX > 0 && mVelY == 0) facing = 0;
	if (mVelX < 0 && mVelY == 0) facing = 10;
}



void Player::move(Level* level, EnemyManager& enemy)
{
	//move it lefet or right
	x += mVelX * cos(-level->rotation) + mVelY * -sin(-level->rotation);
	mCollider.x = x;
	//if it collided
	if ((mCollider.x < (level->_Level->rooms[0]->x * 64)) || (mCollider.x + P_WIDTH >(level->_Level->rooms[0]->x * 64 + level->_Level->rooms[0]->width * 64) ) || touchesWall(mCollider, level->_Level->rooms[0], 0) || checkCircleCollision(enemy, this))
	{
		//then move back
		x -= mVelX * cos(-level->rotation) + mVelY * -sin(-level->rotation);
		mCollider.x = x;

	}
	// later add in if functions for sprite boundaries hitting edge of screen which sets velocties to 0
	y += mVelY * cos(-level->rotation) + mVelX * sin(-level->rotation);
	mCollider.y = y;

	//if collided
	if ((mCollider.y < level->_Level->rooms[0]->y * 64) || (mCollider.y + mCollider.h*2 + radius > (level->_Level->rooms[0]->y * 64 + level->_Level->rooms[0]->height * 64) ) || touchesWall(mCollider, level->_Level->rooms[0], 0) ||  checkCircleCollision(enemy, this))
	{
		//mPosY -= mVelY;
		y -= mVelY * cos(-level->rotation) + mVelX * sin(-level->rotation);
		mCollider.y = y;
	}
}

void Player::knockback(Level* level, EnemyManager& enemy1, Enemy& enemy)
{
	//here the angle we are moving is the angle between the player and enemy.
	double angle2 = atan2(enemy.y - (y + mCollider.h * 2), enemy.x - (x + mCollider.w));
	knockX = x + 50 * cos(-angle2) + 50 * -sin(-angle2);
	//if it collided
	if ((mCollider.x < (level->_Level->rooms[0]->x * 64)) || (mCollider.x + P_WIDTH >(level->_Level->rooms[0]->x * 64 + level->_Level->rooms[0]->width * 64)) || touchesWall(mCollider, level->_Level->rooms[0], 0) || checkCircleCollision(enemy1, this))
	{
		//then move back
		x -= 50 * cos(-angle2) + 50 * -sin(-angle2);
		mCollider.x = x;

	}
	// later add in if functions for sprite boundaries hitting edge of screen which sets velocties to 0
	y += 50 * cos(-angle2) + 50 * sin(-angle2);
	mCollider.y = y;

	//if collided
	if ((mCollider.y < level->_Level->rooms[0]->y * 64) || (mCollider.y + mCollider.h * 2 + radius >(level->_Level->rooms[0]->y * 64 + level->_Level->rooms[0]->height * 64)) || touchesWall(mCollider, level->_Level->rooms[0], 0) || checkCircleCollision(enemy1, this))
	{
		//mPosY -= mVelY;
		y -= 50 * cos(-angle2) + 50 * sin(-angle2);
		mCollider.y = y;
	}
}

void Player::update(Level* level, ProjectileManager* p, SDL_Rect* camera, EquipInv* inv, SDL_Renderer* gRenderer, EnemyManager& enemy)
{
	//selectEnemy(&enemy);
	if (!strafing)
	{
		move(level, enemy);
		//if (targetedEnemy != NULL)
		
	}
	else
	{
		strafe(level, enemy);	
	}

	
	if (shooting)
	{
		leftClick(inv, gRenderer, p, camera, level->_Level->rooms[0]);
	}
	if (teleporting)
	{
	//	teleport(x + camera->x, y + camera->y);
	}
	if (attacking)
	{
		//attack(x + camera.x, y + camera.y);
	}
	//if (rotating == 1) level->rotate((2 * 3.14159 / 96)); 
	//if (rotating == 2) level->rotate(-(2 * 3.14159 / 96)); 
	

	
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

void Player::giveExperience(int amount)
{
	
	experience += amount;
	std::cout << experience << std::endl;
	std::cout << experienceTotal << std::endl;
	if (experience >= experienceTotal)
	{
		LevelUp();
	}
	experienceLeft = experienceTotal - experience;
	double percent = (experience - experienceTotalPrevious) / ((experienceTotal - experienceTotalPrevious)/1.0);
	std::cout << percent << "\n";
	experienceBox.w = percent * (SCREEN_WIDTH - 100);
}

void Player::renderBars(SDL_Renderer* gRenderer)
{
	//renderhealthbox
	healthBox.w = (health / (maxHealth / 1.0)) * 300;

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, maxHealthBox1);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(gRenderer, &maxHealthBox);
	
	//render hotbar
	if (slideflag)
	{
		if (sliding)
		{
			hotbarSlide(SCREEN_WIDTH * 2 / 3, 100);
		}
		if (!sliding)
		{
			hotbarSlide(SCREEN_WIDTH + 25, 100);
		}
	}

	hotbar->render(gRenderer, 0, 0);


	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &experienceBoxMax);
	SDL_SetRenderDrawColor(gRenderer, 66, 244, 238, 255);
	SDL_RenderFillRect(gRenderer, &experienceBox);

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
}

void Player::hotbarSlide(int x, int y)
{
	double angle = atan2(y-hotbar->y, x-hotbar->x);
	if (hotbar->x != x)
	{
		hotbar->x += 20 * cos(angle);
		std::cout << hotbar->x << '\n';
	}
	if (hotbar->y != y)
	{
		hotbar->y += 20 * sin(angle);
	}
	if (hotbar->x - x < 10 && hotbar->x - x > -10 && hotbar->y - y < 10 && hotbar->y - y > -10)
	{
		slideflag = false;
		hotbar->x = x;
		hotbar->y = y;
	}
}

void Player::render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* clip2) //SDL_Rect& camera)
{
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(gRenderer, x + dx - camera.x + mCollider.w, y + mCollider.h * 2 + dy - camera.y);
			}
		}
	}
	gSpriteSheetTexture.render(x - camera.x, y - camera.y, clip, gRenderer, angle, center, flip);
	if (talkable == true)
	{
		gSpriteSheetTexture.render(x - camera.x, (y - 8 * scale) - camera.y, clip2,gRenderer, angle, center, flip);
	}
	
}

bool checkCircleCollision(EnemyManager& enemy, Player* player, double angle)
{
	int x1, x2;
	int y1, y2;
	int r1, r2;

	x1 = player->x + player->mCollider.w;
	y1 = player->y + player->mCollider.h * 2;
	r1 = player->radius;
	node* temp = enemy.head;
	while (temp != NULL)
	{

		x2 = temp->enemy->x;
		y2 = temp->enemy->y;
		r2 = temp->enemy->radius;

		if ((x2 - x1) * (x2 - x1) + ((y1 - y2) * (y1 - y2)) < (r1 + r2) * (r1 + r2))
		{
			return true;
		}
		temp = temp->next;
	}

	return false;
}

void Player::leftClick(EquipInv* equip, SDL_Renderer* gRenderer, ProjectileManager* pManager, SDL_Rect* camera, Room* room)
{
	
	if (hotbar->boxes[hotbar->selectedBox]->object != NULL)
	{
		
		hotbar->clickItem(hotbar->selectedBox, this, equip, gRenderer, hotbar, pManager, camera, room);
	}
}

void Player::shoot(ProjectileManager& pManager, int x3, int y3, EquipInv& inv)
{
	if (shootable && inv.equips[1]->renderable)
	{
	int scale = 2.0;

	int mX = x3, mY = y3;

	double angle = getangle(x3, y3);

	double PVelY = scale * sin(angle);
	double PVelX = scale * cos(angle);
	angle = (angle * (180 / PI))+180;
	
		pManager.insert(angle, (mCollider.x + mCollider.w), (mCollider.y + mCollider.h*2), PVelX, PVelY, damage, 10, inv.equips[1]->getProjectile());
		shootingframes = 240;
	}
}

double Player::getangle(int x1, int y1)
{
	return atan2(y1 - (mCollider.y + mCollider.h*2), x1 - (mCollider.x + mCollider.w));
}

void Player::setCamera(SDL_Rect& camera)
{
	if (!strafing)
	{
		if (!camera_offset)
		{
			cX2 = (x + (P_WIDTH / 2)) - (SCREEN_WIDTH) / 2;
			cY2 = (y + (P_HEIGHT / 2)) - SCREEN_HEIGHT / 2;
			cameraPan(camera);
			if (!panning)
			{
				camera.x = (x + (P_WIDTH / 2)) - (SCREEN_WIDTH) / 2;
				camera.y = (y + (P_HEIGHT / 2)) -  SCREEN_HEIGHT / 2;
			}
		}
		else
		{
			camera.x = (x + (P_WIDTH / 2)) - (SCREEN_WIDTH) / 2;
			camera.y = (y + (P_HEIGHT / 2)) - 2 * SCREEN_HEIGHT / 3;
		}
	}
	else
	{
		cX2 = targetedEnemy->x - SCREEN_WIDTH/2;
		cY2 = targetedEnemy->y - SCREEN_HEIGHT/2;
		cameraPan(camera);
		if (!panning)
		{
			camera.x = (targetedEnemy->x) - (SCREEN_WIDTH) / 2;
			camera.y = (targetedEnemy->y) -  SCREEN_HEIGHT / 2;
		}
	}

	//keep camera in bounds
	/*if (camera.x < -camera.w/2)
	{
		camera.x = 0;
	}
	if (camera.y < -camera.h/2)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w/2)
	{
		camera.x = LEVEL_WIDTH - camera.w/2;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h/2)
	{
		camera.y = LEVEL_HEIGHT - camera.h/2;
	}*/
}

void Player::cameraPan(SDL_Rect& camera)
{
	double angle = atan2(cY2 - camera.y, cX2 - camera.x);
	if (panning)
	{
		{
			camera.x += 10 * cos(-angle);
		}
		if (camera.y != cY2)
		{
			camera.y += 10 * sin(angle);
		}
	}
	if (cX2 - camera.x < 10 && cX2 - camera.x > -10 && cY2 - camera.y < 10 && cY2 - camera.y > -10)
		panning = false;
}

SDL_Rect Player::getChatBubble()
{
	return chatBubble;
}

void Player::incrementFrames()
{
	if (shootingframes > 0)
	{
		if (shootangle < 100 && shootangle > -100)
		shootangle += 10;
		shootingframes -= dexterity;
		shootable = false;
	}
	else 
	{
		shootable = true;
		shootingframes = 0;
		shootangle = 0;
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