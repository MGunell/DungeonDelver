#pragma once
class SDL_Rect;
class EnemyManager;
class ProjectileManager;

#include "ProjectileManager.h"
#include "LTexture.h"
static SDL_Rect cubeSprites[27];
static LTexture gCubeTexture1;


class Enemy
{
public:
	Enemy(double x1, double y1, double radius1) : x(x1), y(y1), radius(radius1)
	{
		hp = 100; 
		mp = 100;
		hpMax = 100;
		mpMax = 100;

		facingAngle = 0.0;

		turnRate = 0.04;
		movespeed = 4.0;

		attackRadius = radius * 5;
		attackWidth = 3.14 / 5;
		attackDamage = 15;

		chargingFrames = 0;
		chargingFramesMax = 180;
		chargingAttack = false;
		moving = false;
		alive = true;
		invulnerable = false;
	};

	void render(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		if (alive)
		{
			SDL_Rect moving = { x + (radius*cos(facingAngle)) - camera.x, y + (radius*sin(facingAngle)) - camera.y, 10, 10 };
			renderCircle(gRenderer, camera);
			renderSprite(gRenderer, camera);
			renderInfo(gRenderer, camera);
			renderHealth(gRenderer, camera);
			renderMana(gRenderer, camera);
			SDL_RenderFillRect(gRenderer, &moving);
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		}
	}

	virtual void renderSprite(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
	}

	virtual void renderCircle(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 120, 255);
		for (int w = 0; w < radius * 2; w++)
		{
			for (int h = 0; h < radius * 2; h++)
			{
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				if ((dx*dx + dy * dy) <= (radius * radius))
				{
					SDL_RenderDrawPoint(gRenderer, x + dx - camera.x, y + dy - camera.y);
				}
			}
		}
	}

	void setAgro(Player* player)
	{
		agroTarget = player;
	}

	double getAngle()
	{
		return atan2((agroTarget->y + agroTarget->mCollider.h * 2) - y, (agroTarget->x + agroTarget->mCollider.w) - x);
	}

	virtual void setName()
	{
		name = "Slime";
	}

	void setNameTexture(LTexture* src)
	{
		namesprite = src;
	}

	void setTexture(LTexture* src)
	{
		spritesheet = src;
	}

	void renderInfo(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		namesprite->render(x - radius - camera.x, y + radius - camera.y, NULL, gRenderer);
	}

	void renderHealth(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		double healthsize = radius * 2 * (hp / (hpMax * 1.0));

		SDL_Rect Healthbar = { x - radius - camera.x, y + radius - camera.y + 15, healthsize, 4 };
		SDL_Rect HealthbarLine = { x - radius - camera.x - 1, y + radius - camera.y + 14, radius * 2 + 2, 6 };

		SDL_SetRenderDrawColor(gRenderer, 255, 10, 10, 255);
		SDL_RenderFillRect(gRenderer, &Healthbar);
		SDL_RenderDrawRect(gRenderer, &HealthbarLine);

	}

	virtual void update()
	{
		//we need to agro onto player
		//if in range to perform an attack, try to attack
		//only boss monsters ill have multiple attacks
		//else we have to move closer
		if (hp < 0) alive = false;
		if (alive)
		{

			if ( !inRadius() && !chargingAttack/*not in range*/)
			{
				uncharge();
				rotate();
			}
			else //in range
			{
				chargeAttack();
			}
		}
		else
		{
			//die();
		}


	}

	void uncharge()
	{
		if (chargingFrames > 0)
		{
			chargingFrames = 0;
		}
	}

	void chargeAttack()
	{
		if (chargingFrames < chargingFramesMax)
		{
			chargingFrames++;
		}
		else
		{
			coneAttack();
			chargingFrames = 0;
			chargingAttack = false;
		}
	}

	bool inRadius()
	{
		int x2 = agroTarget->x + agroTarget->mCollider.w;
		int y2 = agroTarget->y + agroTarget->mCollider.h * 2;
		if (((x2 - x) * (x2 - x)) + ((y - y2) * (y - y2)) < (agroTarget->radius + attackRadius) * (agroTarget->radius + attackRadius))
		{
			return true;
		}
		else return false;
	}

	bool insideRadius()
	{
		int x2 = agroTarget->x + agroTarget->mCollider.w;
		int y2 = agroTarget->y + agroTarget->mCollider.h * 2;
		if (((x2 - x) * (x2 - x)) + ((y - y2) * (y - y2)) < (agroTarget->radius + radius + 2) * (agroTarget->radius + radius + 2))
		{
			return true;
		}
		else return false;
	}

	void dealDamage(int damage1)
	{
		if (!invulnerable)
		hp -= damage1;

		if (hp <= 0)
			alive = false;
	}

	void setXY(int x1, int y1)
	{
		x = x1;
		y = y1;
	}

	void move(int x1, int y1)
	{
		x += x1;
		y += y1;
	}

	void move()
	{
		x += movespeed * cos(facingAngle);

		y += movespeed * sin(facingAngle);
	}

	void moveTo(int x1, int y1)
	{
		if (moving)
		{
			double angle = atan2((y1)-y, (x1)-x);
			if (x != x1)
			{
				x += movespeed * cos(angle);
			}
			if (y != y1)
			{
				y += movespeed * sin(angle);
			}
			if (abs(x1 - x) <= movespeed)
			{
				x = x1;
			}
			if (abs(y1 - y) <= movespeed)
			{
				y = y1;
			}
			if (x == x1 && y == y1)
			{
				moving = false;
			}
		}

	}
	void coneAttack()
	{
		
		//first check to see if even in range
		if (    inRadius()  )
		{
			//we know player is in range of the attack
			//now we need to check if it's within the angleWidth of the attack based off facing direction
			double Angle = getAngle();
			if (Angle > facingAngle - attackWidth && Angle < facingAngle + attackWidth)
			{
				//the attack hits and we deal damage to the player
				agroTarget->dealDamage(attackDamage);
			}
		}
	}

	bool dead()
	{
		return alive;
	}

	void rotate()
	{
		//while facingAngle and player angle are different, rotate to face player according to cloeset
		double angle = atan2((agroTarget->y + agroTarget->mCollider.h * 2) - y, (agroTarget->x + agroTarget->mCollider.w) - x);
		if (abs(angle - facingAngle) > 3.14/50)
		{
			if (facingAngle < angle)
			{
				if (abs(angle - facingAngle) < 3.14 / 2)
				{
					if (facingAngle + turnRate > angle)
						facingAngle = angle;
					else
						facingAngle += turnRate;
				}
				else
				{
					if (facingAngle - turnRate < angle)
						facingAngle = angle;
					else
						facingAngle -= turnRate;
				}
			}
			else
			{
				if (abs(angle - facingAngle) < 3.14 / 2)
				{
					if (facingAngle - turnRate < angle)
						facingAngle = angle;
					else
						facingAngle -= turnRate;
				}
				else
				{
					if (facingAngle + turnRate > angle)
						facingAngle = angle;
					else
						facingAngle += turnRate;
				}
			}
			
		}
		else
		{
			move();
		}
	}

	void renderMana(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		double healthsize = radius*2 * (mp / (mpMax * 1.0));

		SDL_Rect Healthbar = { x - radius - camera.x, y + radius - camera.y + 23, healthsize, 4 };
		SDL_Rect HealthbarLine = { x - radius - camera.x - 1, y + radius - camera.y + 22, radius * 2 + 2, 6 };

		SDL_SetRenderDrawColor(gRenderer, 10, 10, 255, 255);
		SDL_RenderFillRect(gRenderer, &Healthbar);
		SDL_RenderDrawRect(gRenderer, &HealthbarLine);

	}
	int x, y;
	int attackDamage;
	unsigned int radius;
	int hp, mp;
	double movespeed;
	bool moving;
	//circle hitbox
	double facingAngle;

	std::string name;
	LTexture* namesprite;
	LTexture* spritesheet;
	SDL_Rect* spriteboxes;
	int boxselec;
	//sprite dimensions 
	//pointer to a sprite which is stored as an enemy sprite
	//which can be set with a function;
	LTexture* texture;
	Player* agroTarget;

	//info about the enemy
	
	int hpMax, mpMax;

	double turnRate;

	int attackRadius;
	
	double attackWidth;

	bool chargingAttack;
	int chargingFrames, chargingFramesMax;

	bool alive;
	bool invulnerable;

	ProjectileManager* pM;
	void setPM(ProjectileManager* src)
	{
		pM = src;
	}
	//each mob will have several attacks

	int shootingframes;
	int animFrames;

};



class HCBpawn : public Enemy
{
public:
	HCBpawn(int x1, int y1, int radius1) : Enemy(x1, y1, radius1)
	{
		hp = 500;
		hpMax = 500;
		invulnerable = true;
		movespeed = 8;
		animFrames = 0;
		//alive = false;
	}


	void update()
	{

	}

	void renderSprite(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		animate();
		gCubeTexture1.renderHalf(x - radius*3/2 - camera.x, y - radius*2 - camera.y, &cubeSprites[boxselec], gRenderer);

	}

	void renderCircle(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{

	}

	void shootVolley()
	{
		if (alive)
		{
			double Angle = getAngle();
			int projectilespeed1 = 4;

			shootingframes++;

			if (shootingframes % 80 == 0)
			{
				pM->insert(Angle * 180 / 3.14, x, y, projectilespeed1 * cos(Angle), projectilespeed1 * sin(Angle), 5, 12, 12);
			}
		}
	}

	void shoot(int x1, int y1)
	{
		if (alive)
		{
			shootingframes++;
			double Angle = atan2(y1 - y, x1 - x);
			int projectilespeed1 = 15;
			if (shootingframes % 2 == 0)
				pM->insert(Angle * 180 / 3.14, x, y, projectilespeed1 * cos(Angle), projectilespeed1 * sin(Angle), 25, 25, 13);
		}
	}

	void animate()
	{
		int loops = 6;
		int starts = 106;
		animFrames++;

		if (animFrames >= starts + 33 * loops)
		{
			animFrames = 0;
		}
		
		if (animFrames < starts) boxselec = 0;
		else if (animFrames < starts + 1 * loops) boxselec = 1;
		else if (animFrames < starts + 4 * loops) boxselec = 2;
		else if (animFrames < starts + 5 * loops) boxselec = 3;
		else if (animFrames < starts + 8 * loops) boxselec = 4;
		else if (animFrames < starts + 9 * loops) boxselec = 5;
		else if (animFrames < starts + 10 * loops) boxselec = 6;
		else if (animFrames < starts + 11 * loops) boxselec = 7;
		else if (animFrames < starts + 12 * loops) boxselec = 8;
		else if (animFrames < starts + 13 * loops) boxselec = 9;
		else if (animFrames < starts + 14 * loops) boxselec = 10;
		else if (animFrames < starts + 18 * loops) boxselec = 11;
		else if (animFrames < starts + 19 * loops) boxselec = 12;
		else if (animFrames < starts + 20 * loops) boxselec = 13;
		else if (animFrames < starts + 21 * loops) boxselec = 14;
		else if (animFrames < starts + 22 * loops) boxselec = 15;
		else if (animFrames < starts + 23 * loops) boxselec = 16;
		else if (animFrames < starts + 24 * loops) boxselec = 17;
		else if (animFrames < starts + 25 * loops) boxselec = 18;
		else if (animFrames < starts + 26 * loops) boxselec = 19;
		else if (animFrames < starts + 27 * loops) boxselec = 20;
		else if (animFrames < starts + 28 * loops) boxselec = 21;
		else if (animFrames < starts + 29 * loops) boxselec = 22;
		else if (animFrames < starts + 30 * loops) boxselec = 23;
		else if (animFrames < starts + 31 * loops) boxselec = 24;
		else if (animFrames < starts + 32 * loops) boxselec = 25;
		else if (animFrames < starts + 33 * loops) boxselec = 26;
	}



	void shootatpawn()
	{
		if (alive)
		{
			double Angle = atan2(pawntarget->y - y, pawntarget->x - x);
			int projectilespeed1 = 4;
			shootingframes++;

			if (shootingframes % 15 == 0)
			{
				pM->insert(Angle * 180 / 3.14, x, y, projectilespeed1 * cos(Angle), projectilespeed1 * sin(Angle), 5, 10, 12);
			}
		}
	}

	void setPawnTarget(HCBpawn* src)
	{
		pawntarget = src;
	}

	HCBpawn* pawntarget;


};

class hyperCubeBoss : public Enemy
{
public:
	hyperCubeBoss(int x1, int y1, int radius) : Enemy(x1, y1, radius)
	{
		hp = 3000;
		hpMax = 3000;

		phase = 0;
		frames = 0;
		shootingframes = 0;

		cubeAngles = 0;
		aliveCubes = 0;

		volleyCount = 0;
		spreading = false;
		lineSpreading = false;
		lineShooting = false;
		shootingVolley = false;
		linePhase = 0;
	}

	void setPawn(HCBpawn* enemy, int num)
	{
		cubeProtectors[num] = enemy;
	}


	void lineFormation()
	{
		//we want cubes to line up in a row on opposite sides of the main boss
		//so one goes x + radius, one goes x - radius;
		//then for y it is y + radius, y + radius/2
		//                 y - radius, y - radius/2

			cubeProtectors[0]->moveTo(x - radius*12, y + radius*9);
			cubeProtectors[1]->moveTo(x - radius*12, y - radius*9);
			cubeProtectors[2]->moveTo(x - radius*10, y + radius*11);
			cubeProtectors[3]->moveTo(x + radius*10, y - radius*11);

			int donecount = 0;
			for (int i = 0; i < aliveCubes; i++)
			{
				if (cubeProtectors[i]->moving == false)
				{
					donecount++;
				}
			}

			if (donecount == 4)
			{
				lineShooting = true;
				lineSpreading = false;
			}
		
	}

	void lineShoot()
	{
		cubeProtectors[0]->shoot(cubeProtectors[0]->x+100, cubeProtectors[0]->y);
		cubeProtectors[1]->shoot(cubeProtectors[1]->x+100, cubeProtectors[1]->y);
		cubeProtectors[2]->shoot(cubeProtectors[2]->x, cubeProtectors[2]->y-100);
		cubeProtectors[3]->shoot(cubeProtectors[3]->x, cubeProtectors[3]->y+100);
		shootingframes++;
		if (shootingframes == 1200)
		{
			shootingframes = 0;
			lineShooting = false;
			spreading = true;
		}
	}

	void cubeLineMove()
	{
		if (!lineSpreading)
		{
			if (linePhase == 0)
			{
				if (cubeProtectors[2]->x < x + radius * 7)
				{
					cubeProtectors[2]->move(3, 0);
				}
				else
				{
					linePhase = 1;
				}
			}

			if (linePhase == 1)
			{
				if (cubeProtectors[2]->x > x - radius * 7)
				{
					cubeProtectors[2]->move(-3, 0);
					if (cubeProtectors[3]->x > x - radius * 3)
					{
						cubeProtectors[3]->move(-3, 0);
					}
				}
				else
				{
					linePhase = 2;
				}
			}

			if (linePhase == 2)
			{
				if (cubeProtectors[3]->x < x + radius * 10)
				{
					cubeProtectors[2]->move(3, 0);
					cubeProtectors[3]->move(3, 0);
				}
				else linePhase = 1;
			}
		}
	}

	

	void setEM(EnemyManager* src)
	{
		eM1 = src;
	}

	void setTargets()
	{
		cubeProtectors[0]->setPawnTarget(cubeProtectors[1]);
		cubeProtectors[1]->setPawnTarget(cubeProtectors[2]);
		cubeProtectors[2]->setPawnTarget(cubeProtectors[3]);
		cubeProtectors[3]->setPawnTarget(cubeProtectors[0]);
	}

	void moveAll()
	{
		for (int i = 0; i < aliveCubes; i++)
		{
			cubeProtectors[i]->moving = true;
		}
	}
	void moveCubes(int x1, int y1)
	{
		cubeAngles += (.025);
		double Angle = 0;
		for (int i = 0; i < aliveCubes; i++)
		{
			cubeProtectors[i]->setXY(x + x1 * cos(cubeAngles + Angle), y + y1 * sin(cubeAngles + Angle));
			Angle += 6.28 / 4;
		}
	}

	void shootCubes()
	{
		for (int i = 0; i < aliveCubes; i++)
		{
			cubeProtectors[i]->shootVolley();
		}	
	}

	void shootCubesTarget()
	{
		for (int i = 0; i < aliveCubes; i++)
		{
			cubeProtectors[i]->shootatpawn();
		}
	}

	void spreadCubes(int dist)
	{
		if (spreading)
		{
			double Angle = 0;
			int doneCount = 0;
			for (int i = 0; i < aliveCubes; i++)
			{
				cubeProtectors[i]->moveTo(x + dist * cos(cubeAngles + Angle), y + dist * sin(cubeAngles + Angle));
				if (cubeProtectors[i]->moving == false)
				{
					doneCount++;
				}
				Angle += 6.28 / 4;
			}
			if (doneCount == 4)
			{
				spreading = false;
			}
		}
	}

	void shootVolley()
	{
		if (shootingframes == 0)
		{
			volleyAngle = getAngle() + 6.28/9;
		}

		int projectilespeed = 3;
		if (shootingframes % 10 == 0)
		{
			double angleOffset = (6.28 / 60)*volleyCount;
			//we need to enter 20 projectiles radially, with a gap that starts at the player;
			for (int i = 0; i < 20; i++)
			{
				pM->insert((volleyAngle + angleOffset)*180/3.14, x, y, projectilespeed * cos(volleyAngle + angleOffset), projectilespeed * sin(volleyAngle + angleOffset), 10, 15, 11);
				angleOffset += 6.28 / 26;
			}
			volleyCount++;
		}

		shootingframes++;

		if (shootingframes == 600)
		{
			shootingframes = 0;
			shootingVolley = false;
			spreading = true;
			volleyCount = 0;
		}
		
		
	}

	void shootCircleVolley()
	{
		int projectilespeed = 2;
		if (shootingframes % 40 == 0)
		{
			double angleOffset = (6.28/12)*(shootingframes%15);
			for (int i = 0; i < 6; i++)
			{
				pM->insert(angleOffset * 180 / 3.14, x, y, projectilespeed*cos(angleOffset), projectilespeed*sin(angleOffset), 10, 10, 11);
				angleOffset += 6.28/6;
			}
		}

		shootingframes++;
	}

	void setPawnsInvul()
	{
		for (int i = 0; i < aliveCubes; i++)
		{
			cubeProtectors[i]->invulnerable = true;
		}
	}

	void setPawnsVul()
	{
		for (int i = 0; i < aliveCubes; i++)
		{
			cubeProtectors[i]->invulnerable = false;
		}
	}

	void checkPawns()
	{
		int alive = 0;
		for (int i = 0; i < aliveCubes; i++)
		{
			if (cubeProtectors[i]->alive == false)
				alive++;
		}
		if (alive == 4)
		{
			revivePawns();
		}
	}

	void shootTriVolley()
	{
		if (shootingframes == 0)
		{
			volleyAngle = getAngle();
		}
		int projectilespeed = 4;
		if (shootingframes % 5 == 0)
		{
			double angleOffset = (6.28 / 50) * volleyCount;

			for (int i = 0; i < 3; i++)
			{
				pM->insert((volleyAngle + angleOffset) * 180 / 3.14, x, y, projectilespeed * cos(volleyAngle + angleOffset), projectilespeed * sin(volleyAngle + angleOffset), 10, 15, 11);
				angleOffset += 6.28 / 3;
			}
			volleyCount++;
		}
		shootingframes++;

		if (shootingframes == 600)
		{
			shootingframes = 0;
			spreading = true;	
			shootingVolley = false;
			volleyCount = 0;
		}
		
	}

	void update();
	void revivePawns();


	HCBpawn* cubeProtectors[4];
	int aliveCubes;
	int phase;
	bool shootingVolley;
	double volleyChange;
	double volleyAngle;
	int volleyCount;
	int frames;
	double cubeAngles;
	bool spreading;
	bool lineSpreading;
	bool lineShooting;
	int linePhase;

	EnemyManager* eM1;
};



bool loadHyperCubeMedia(SDL_Renderer* gRenderer);