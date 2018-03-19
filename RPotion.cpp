#include "RPotion.h"
#include "Inventory.h"
#include "Equipment_Inventory.h"

void RPotion::placeItem(Inventory& inv)
{
	inv.placePotion(1);
}

bool RPotion::click(Player* player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager)
{
	player->heal(healAmount);
	return false;
	//delete the object from inventory
}
