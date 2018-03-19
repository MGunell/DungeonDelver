#include "Weapon.h"
#include "Equipment_Inventory.h"
#include "Player.h"
#include "InventoryRedux.h"
#include "ProjectileManager.h"

bool Weapon::click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera)
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	double angle = player.getangle(mx + camera->x, my + camera->y);
	double math;
	math = (projectiles - 1) / 2.0;
	angle -= (math * .2);
	if (player.shootable)
	{
		for (int i = 0; i < projectiles; i++)
		{
			double PVelY = speed * sin(angle);
			double PVelX = speed * cos(angle);
			angle = (angle * (180 / 3.14));
			pManager->insert(angle, player.getPosX() + player.mCollider.w / 2, player.getPosY() + player.mCollider.h / 2, PVelX, PVelY, damage, range, projectile);
			angle = (angle) * (3.14 / 180);
			angle += .2;
		}
		player.shootingframes = 240;
	}
	return false;
}

void Weapon::displayInfo(SDL_Renderer* gRenderer)
{
	int x, y;
	SDL_GetGlobalMouseState(&x, &y);
	x += -360;
	y += -90;

	displayBox.w = messageSprite.getWidth();

	displayBox.h = messageSprite.getHeight();
	displayBox.x = x - displayBox.w;
	displayBox.y = y - displayBox.h;

	SDL_SetRenderDrawColor(gRenderer, 100, 100, 50, 255);
	SDL_RenderFillRect(gRenderer, &displayBox);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	messageSprite.render(x - displayBox.w, y - displayBox.h, NULL, gRenderer, NULL, 0);

}

void Weapon::placeInBag(Inventory2* inv, SDL_Renderer* gRenderer)
{
	int i = inv->getEmptySlot();
	int j = inv->getEmptyBag();

	//delete inv.bag[i];
	//inv->bag[i] = new Weapon(inv->slots[j].x, inv->slots[j].y, slot, getSprite(), gRenderer, getProjectile(), damage, range);
	inv->bag[i]->slot = j;
//	inv->slots[j].empty = false;
}

void Weapon::setClips() {
	{
		clips[18].x = 50;
		clips[18].y = 50;
		clips[18].w = 11;
		clips[18].h = 25;

		clips[19].x = 0;
		clips[19].y = 50;
		clips[19].w = 25;
		clips[19].h = 25;
	}
}