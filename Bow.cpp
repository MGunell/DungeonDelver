#include "Bow.h"
#include "Equipment_Inventory.h"
#include "Player.h"
#include "InventoryRedux.h"
#include "Room.h"

void Bow::setClips()
{
	for (int i = 0; i < 4; i++)
	{
		clips[i].x = i * width;
		clips[i].y = 0;
		clips[i].w = width;
		clips[i].h = height;
	}
}

void Bow::placeInBag(Inventory2* inv, SDL_Renderer* gRenderer)
{
	int i = inv->getEmptySlot();
	int j = inv->getEmptyBag();


	delete inv->bag[j];
	inv->bag[i] = new Bow(inv->slots[j].x, inv->slots[j].y, equipslot, getSprite(), gRenderer, getProjectile(), damage, range);
	inv->bag[i]->slot = j;
	//inv->slots[j].empty = false;
}

bool Bow::click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room)
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	double angle = player.getangle(mx + camera->x, my + camera->y); //+ room->rotation;
	double math;
	math = (projectiles - 1) / 2.0;
	angle -= (math * .15);
	angle -= room->rotation;
//	SDL_RenderDrawLine(gRenderer, player.mCollider.x + player.mCollider.w/2 - camera->x, player.mCollider.y + player.mCollider.h/2- camera->y, mx , my );
	if (player.shootable)
	{
		for (int i = 0; i < projectiles; i++)
		{
			double PVelY = speed * sin(angle);
			double PVelX = speed * cos(angle);
			pManager->insert(angle * 180/3.14, player.getPosX() + player.mCollider.w, player.getPosY() + player.mCollider.h*2, PVelX, PVelY, damage, range, projectile, speed);
			angle += .15;
		}
		player.shootingframes = 240;
	}
	return false;
}