#include "Sword.h"
#include "Player.h"
#include "Room.h"

void Sword::setClips()
{
	for (int i = 0; i < 4; i++)
	{
		clips[i].x = i * width;
		clips[i].y = 0;
		clips[i].w = width;
		clips[i].h = height;
	}
}

bool Sword::click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room)
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	double angle = player.getangle(mx + camera->x, my + camera->y); //+ room->rotation;
	double math;
	math = (projectiles - 1) / 2.0;
	angle -= (math * .15);
	angle -= room->rotation;
	SDL_RenderDrawLine(gRenderer, player.mCollider.x + player.mCollider.w / 2 - camera->x, player.mCollider.y + player.mCollider.h / 2 - camera->y, mx, my);
	if (player.shootable)
	{
		for (int i = 0; i < projectiles; i++)
		{
			double PVelY = 80 * sin(angle);
			double PVelX = 80 * cos(angle);
			double PVelY1 = speed * sin(angle);
			double PVelX1 = speed * cos(angle);
			angle = (angle * (180 / 3.14));
			pManager->insert(angle, PVelX +  player.getPosX() + player.mCollider.w, PVelY + player.getPosY() + player.mCollider.h - 15,PVelX1, PVelY1, damage, range, projectile, speed);
			angle = (angle) * (3.14 / 180);
			angle += .15;
		}
		player.shootingframes = 240;
	}
	return false;
}