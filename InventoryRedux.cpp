#include "InventoryRedux.h"
#include "Player.h"
#include "RPotion.h"

Inventory2::Inventory2(SDL_Renderer* gRenderer)
{
	maxCapacity = 15;
	slots = new Boxes[maxCapacity];
	
	
	rows = 3;
	columns = 5;
	UI.w = (SCREEN_WIDTH / 4) + 45;
	UI.h = SCREEN_HEIGHT;
	UI.y = 0;
	UI.x = SCREEN_WIDTH - UI.w;

	tileWidth = 55;
	tileHeight = 55;
	tilePadding = 15;
	x1 = UI.x + 4;
	y1 = SCREEN_HEIGHT / 2;

	initInv();
	setSprite("images/inventory.png", gRenderer);

	mouseCollider = { 0, 0, 5, 5 };

	for (int i = 0; i < maxCapacity; i++)
	{
		bag[i] = new Renderable(-100, -100, 25);
	}
}

void Inventory2::initInv()
{
	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			slots[x + y * columns].x = (x * tileWidth + (x * tilePadding)) + x1;
			slots[x + y * columns].y = (y * tileWidth + (y * tilePadding)) + y1;
			slots[x + y * columns].empty = true;
		}
	}

	currentSelection = -1;
	clicking = false;
	activating = false;
}

void Inventory2::setSprite(std::string path, SDL_Renderer* gRenderer)
{
	Sprite.loadFromFile(path, gRenderer);

	clip.x = 0;
	clip.y = 0;
	clip.w = 335;
	clip.h = 195;
}

void Inventory2::handleEvent(SDL_Event& e)
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
			clicking = false;
			activating = true;
			break;
		case SDL_BUTTON_RIGHT:

			break;
		}
	}
}

void Inventory2::handleMovement(Player& player)
{
	int mousexDelt, mouseyDelt;
	SDL_GetRelativeMouseState(&mousexDelt, &mouseyDelt);
	SDL_GetMouseState(&mouseCollider.x, &mouseCollider.y);

	if (clicking == true) {
		if (currentSelection < 0)
		{
			currentSelection = getMouse_Collision(mouseCollider.x, mouseCollider.y);
		}

		if (currentSelection >= 0 && slots[currentSelection].empty == false)
		{
			bag[currentSelection]->x += mousexDelt;
			bag[currentSelection]->y += mouseyDelt;
		}
	}



	if (activating)
	{
		activating = false;

		if (currentSelection > -1 && slots[currentSelection].empty == false)
		{
			int movedx = slots[bag[currentSelection]->slot].x - bag[currentSelection]->x;
			int movedy = slots[bag[currentSelection]->slot].y - bag[currentSelection]->y;
			double dist = sqrt((movedx*movedx) + (movedy * movedy));
			if (dist < 4)
			{
				bag[currentSelection]->click(player);
				delete bag[currentSelection];
				bag[currentSelection] = new Renderable(slots[currentSelection].x, slots[currentSelection].y, 25);
				slots[currentSelection].empty = true;

			}

			int invNum = getInventoryNumber(*bag[currentSelection]);
			if (invNum > -1)
			{
				if (invNum == bag[currentSelection]->slot)
				{
					bag[currentSelection]->x = slots[bag[currentSelection]->slot].x;
					bag[currentSelection]->y = slots[bag[currentSelection]->slot].y;
				}
				else
				{

					if (slots[invNum].empty == true)
					{
						bag[currentSelection]->x = slots[invNum].x;
						bag[currentSelection]->y = slots[invNum].y;
						slots[invNum].empty = false;
						slots[bag[currentSelection]->slot].empty = true;
						bag[currentSelection]->slot = invNum;
						std::cout << invNum + 1 << std::endl;
					}
					else if (slots[invNum].empty == false)
					{
						//here we swap positions of the two
						bag[currentSelection]->x = slots[invNum].x;
						bag[currentSelection]->y = slots[invNum].y;

						int itemNum;
						int itemNum2 = bag[currentSelection]->slot;
						for (int i = 0; i < maxCapacity; i++)
						{
							if (bag[i]->slot == invNum)
								itemNum = i;
						}
						bag[itemNum]->x = slots[itemNum2].x;
						bag[itemNum]->y = slots[itemNum2].y;

						bag[itemNum]->slot = itemNum2;
						bag[currentSelection]->slot = invNum;

						std::cout << "grabbedItem slot: " << invNum << "replaced item new slot: "
							<< itemNum2 << std::endl;
					}
				}
			}
		}

		if (clicking == false && currentSelection > -1)
		{
			currentSelection = -1;
		}
	}
}

bool Inventory2::getItems_Collision(Renderable& a, Renderable& b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.width;
	topA = a.y;
	bottomA = a.y + a.height;

	leftB = b.x;
	rightB = b.x + b.width;
	topB = b.y;
	bottomB = b.y + b.height;


	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

int Inventory2::getInventoryNumber(Renderable& a) {
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

	for (int x = 0; x < columns; x++) {
		for (int y = 0; y < rows; y++) {
			//break here
			leftA = (x * tileWidth + (x *tilePadding)) + x1;
			rightA = leftA + tileWidth;
			topA = (y * tileHeight + (y *tilePadding)) + y1;
			bottomA = topA + tileHeight;

			if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB))
			{

			}
			else
			{
				return x + y * columns;
			}
		}
	}
	return -1;
}

int Inventory2::getMouse_Collision(int x, int y) {
	int leftA, leftB;
	int rightA;
	int topA, topB;
	int bottomA;

	leftB = x;
	topB = y;

	for (int x = 0; x < columns; x++) {
		for (int y = 0; y < rows; y++) {
			//break here
			leftA = (x * tileWidth + (x * tilePadding)) + x1;
			rightA = leftA + tileWidth;
			topA = (y * tileHeight + (y * tilePadding)) + y1;
			bottomA = topA + tileHeight;

			if ((bottomA <= topB) || (topA >= topB) || (rightA <= leftB) || (leftA >= leftB))
			{

			}
			else
			{
				return x + y * columns;
			}
		}
	}
	return -1;
}

void Inventory2::renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 140, 94, 4, 255);
	SDL_RenderFillRect(gRenderer, &UI);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	Sprite.renderInventory(UI.x + 5, SCREEN_HEIGHT / 2, &clip, gRenderer);
	for (int i = 0; i < maxCapacity; i++)
	{
		if (bag[i]->renderable)
			bag[i]->renderInv(gRenderer, camera);
	}
}

void Inventory2::placePotion(SDL_Renderer* gRenderer)
{
		for (int i = 0; i < maxCapacity; i++)
		{
			if (slots[i].empty == true)
			{
				//delete bag[i];
				int x = slots[i].x;
				int y = slots[i].y;
				bag[i] = new RPotion(x, y, 25, 0, gRenderer);
				bag[i]->slot = i;

				slots[i].empty = false;
				break;
			}

		}
}