#include "Equipment_Inventory.h"
#include "InventoryRedux.h"
#include "RPotion.h"
#include "Weapon.h"
#include "Player.h"


EquipInv::EquipInv(int x, int y)
{
	x_= x; y_ = y;
	slotSize = 97;
	padding = 26;
	rows = 3; columns = 3;
	for (int i = 0; i < 5; i++)
	{
		equips[i] = new Renderable(-100, -100);
	}
	slots = new Boxes1[5];

	mouseCollider = { 0, 0, 5, 5 };

	clicking = activating = false;

	currentSelection = -1;

	initEquip();
}

void EquipInv::initEquip()
{
	
	slots[0].x = x_ + padding + slotSize;
	slots[0].y = y_;
	slots[0].empty = true;
	
	for (int i = 1; i < 4; i++)
	{
		slots[i].x = x_ + padding * (i - 1) + slotSize * (i - 1);
		slots[i].y = y_ + padding + slotSize;
		slots[i].empty = true;
	}

	slots[4].x = x_ + padding + slotSize;
	slots[5].y = y_ + padding * 2 + slotSize * 2;
	slots[4].empty = true;
}

int EquipInv::getInventoryNumber(Renderable& a) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	if (a.renderable != NULL) {
		leftB = a.x;
		rightB = a.x + a.width;
		topB = a.y;
		bottomB = a.y + a.height;
	}
	else return -1;

	for (int x = 0; x < 5; x++) {
			leftA = slots[x].x;
			rightA = slots[x].x + slotSize;
			topA = slots[x].y;
			bottomA = slots[x].y + slotSize;

			if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB))
			{

			}
			else
			{

				return x;
			}
	}
	return -1;
}

int EquipInv::getMouse_Collision(int x, int y) {
	int leftA, leftB;
	int rightA;
	int topA, topB;
	int bottomA;

	leftB = x;
	topB = y;


	for (int x = 0; x < 5; x++) {
		leftA = slots[x].x;
		rightA = slots[x].x + slotSize;
		topA = slots[x].y;
		bottomA = slots[x].y + slotSize;

		if ((bottomA <= topB) || (topA >= topB) || (rightA <= leftB) || (leftA >= leftB))
		{

		}
		else
		{

			return x;
		}
	}

	return -1;
}

int EquipInv::getProjectile()
{
	if (equips[1]->renderable)
	return equips[1]->getProjectile();
}

void EquipInv::loadSprite(std::string filename, SDL_Renderer* gRenderer)
{
	spriteSheet.loadFromFile(filename, gRenderer);
	for (int i = 0; i < 5; i++)
	{
		clips[i].x = 0 + slotSize * i;
		clips[i].y = 0;
		clips[i].w = clips[i].h = slotSize;
	}
}

void EquipInv::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
	{
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			clicking = true;
			break;
		case SDL_BUTTON_RIGHT:
			break;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP && e.key.repeat == 0)
	{
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			break;
		case SDL_BUTTON_RIGHT:

			break;
		}
	}
}

void EquipInv::handleMovement(Player& player, Inventory2& inventory, SDL_Renderer* gRenderer)
{
	if (clicking)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		clicking = false;
		int equipBox = getMouse_Collision(x, y);
		if (equipBox > -1 && equips[equipBox]->renderable)
		{
			equips[equipBox]->placeInBag(&inventory, gRenderer);

			delete equips[equipBox];
			equips[equipBox] = new Renderable(-100, -100);
		}
	}
}

void EquipInv::render(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	SDL_Rect placeHolder = { 0, 0, 345, 345 };

	spriteSheet.renderInventory(x_, y_, &placeHolder, gRenderer);
	for (int i = 0; i < 5; i++)
	{
		if (equips[i]->renderable)
			equips[i]->renderInv(gRenderer, camera);
	}
}

void EquipInv::placeHelemt(SDL_Renderer* gRenderer)
{
	//equips[0] = new Weapon(slots[0].x, slots[0].y, 0, 3, gRenderer);
}

//void EquipInv::placeWeapon(SDL_Renderer* gRenderer)
//{
	//equips[1] = new Weapon(slots[1].x, slots[1].y, 1, gRenderer);
//}

void EquipInv::renderModularItems(Player& player, SDL_Renderer* gRenderer, SDL_Rect& camera)
{ 

	if (equips[1]->renderable)
	{
	}
	//equips[1]->sprite.render(player.getPosX() - camera.x, player.getPosY() - camera.y, &clips[0], gRenderer);
}

