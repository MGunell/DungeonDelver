#include "RPotion.h"
#include "Inventory.h"

void RPotion::placeItem(Inventory& inv)
{
	inv.placePotion(1);
}

void RPotion::click(Player& player)
{
	player.heal(25);
}
