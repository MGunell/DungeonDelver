#include "InventoryRedux.h"
#include "Player.h"
#include "RPotion.h"
#include "Equipment_Inventory.h"
#include "Weapon.h"
#include "Room.h"

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
	y1 = SCREEN_HEIGHT - 210;

	initInv();
	setSprite("images/inventory.png", gRenderer);

	mouseCollider = { 0, 0, 5, 5 };
}

void Inventory2::initInv()
{
	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			slots[x + y * columns].x = (x * tileWidth + (x * tilePadding)) + x1;
			slots[x + y * columns].y = (y * tileWidth + (y * tilePadding)) + y1;
			//slots[x + y * columns].empty = true;
		}
	}

	for (int i = 0; i < maxCapacity; i++)
	{
		bag[i] = new Renderable(slots[i].x, slots[i].y);
		bag[i]->slot = i;
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
	else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_i:
			std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
			for (int i = 0; i < maxCapacity; i++)
			{
				if (bag[i]->renderable)
				{
					std::cout << "item: " << i << ":\n"
						//<< "empty: " << slots[bag[i]->slot].empty << std::endl
						<< "slot number: " << bag[i]->slot << std::endl
						<< "_________________________________________\n";

				}
			}
		}
	}
}

void Inventory2::handleMovement(Player& player, EquipInv& inv, SDL_Renderer* gRenderer)
{
	int mousexDelt, mouseyDelt;
	SDL_GetRelativeMouseState(&mousexDelt, &mouseyDelt);
	SDL_GetMouseState(&mouseCollider.x, &mouseCollider.y);

	if (clicking == true) {
		if (currentSelection < 0)
		{
			currentSelection = getMouse_Collision(mouseCollider.x, mouseCollider.y);
		}

		//if (currentSelection >= 0 && slots[bag[currentSelection]->slot].empty == false)
		{
			bag[currentSelection]->x += mousexDelt;
			bag[currentSelection]->y += mouseyDelt;
			//std::cout << "here: " << currentSelection << std::endl;
			//std::cout<< "Current: " << bag[currentSelection]->x << ", " << bag[currentSelection]->y << std::endl;
		}

		
	}
	

	if (activating)
	{
		activating = false;

//if (currentSelection > -1 && slots[bag[currentSelection]->slot].empty == false)
		{
			int movedx = slots[bag[currentSelection]->slot].x - bag[currentSelection]->x;
			int movedy = slots[bag[currentSelection]->slot].y - bag[currentSelection]->y;
			double dist = sqrt((movedx*movedx) + (movedy * movedy));
			if (dist < 2)
			{
				//bag[currentSelection]->click(player, &inv, gRenderer, this);
			//	slots[bag[currentSelection]->slot].empty == true;
				if (bag[currentSelection]->renderable == false)
				{
				//	bag[currentSelection] = new Renderable(slots[currentSelection].x, slots[currentSelection].y);
				//	slots[currentSelection].empty = true;
				}

			}

			int invNum = getInventoryNumber(*bag[currentSelection]);
			if (invNum > -1)
			{
				if (invNum == bag[currentSelection]->slot)
				{
					bag[currentSelection]->x = slots[bag[currentSelection]->slot].x;
					bag[currentSelection]->y = slots[bag[currentSelection]->slot].y;
					std::cout << bag[currentSelection]->x << ", " << bag[currentSelection]->y << std::endl;
				}
				else
				{

				//	if (slots[invNum].empty == false)
					{
						//here we swap positions of the two
						bag[currentSelection]->x = slots[invNum].x;
						bag[currentSelection]->y = slots[invNum].y;

						//next find the bag in that slot
						int switchingNum;
						for (int j = 0; j < maxCapacity; j++)
						{
							if (bag[j]->slot == invNum)
							{
								switchingNum = j;
								break;
							}

						}

						//swap x and y of this bag
						bag[switchingNum]->x = slots[bag[currentSelection]->slot].x;
						bag[switchingNum]->y = slots[bag[currentSelection]->slot].y;

						//next assign the new slots to them
						int temp = bag[currentSelection]->slot;
						bag[currentSelection]->slot = invNum;
						bag[switchingNum]->slot = temp;
					}
				//	else
					{
						bag[currentSelection]->x = slots[invNum].x;
						bag[currentSelection]->y = slots[invNum].y;
					//	slots[invNum].empty = false;
					//	slots[bag[currentSelection]->slot].empty = true;
						bag[currentSelection]->slot = invNum;

					}
				}
			}
			else
			{
				bag[currentSelection]->x = slots[bag[currentSelection]->slot].x;
				bag[currentSelection]->y = slots[bag[currentSelection]->slot].y;
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

	for (int z = 0; z < maxCapacity; z++) {
		
			leftA = bag[z]->x;
			rightA = leftA + tileWidth;
			topA = bag[z]->y;
			bottomA = topA + tileHeight;

			if ((bottomA <= topB) || (topA >= topB) || (rightA <= leftB) || (leftA >= leftB))
			{

			}
			else
			{
				return z;
			}
		
		
	}
	return -1;
}

void Inventory2::renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 140, 94, 4, 255);
	SDL_RenderFillRect(gRenderer, &UI);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	Sprite.renderInventory(x1, y1, &clip, gRenderer);
	for (int i = 0; i < maxCapacity; i++)
	{
		if (bag[i]->renderable) bag[i]->renderInv(gRenderer, camera);
	}

	if (!clicking)
	{
		currentSelection = getMouse_Collision(mouseCollider.x, mouseCollider.y);
		if (currentSelection > -1)
			bag[currentSelection]->displayInfo(gRenderer);
	}
}

void Inventory2::placePotion(SDL_Renderer* gRenderer)
{
		for (int i = 0; i < maxCapacity; i++)
		{
			if (bag[i]->renderable == false)
			{
				delete bag[i];
				for (int j = 0; j < maxCapacity; j++)
				{
				//	if (slots[j].empty == true)
					{
						bag[i] = new RPotion(slots[j].x, slots[j].y, 25, 1, gRenderer);
						bag[i]->slot = j;
					//	slots[j].empty = false;

						std::cout << "placed a potion in bag x and slot y: (" << i << ", "
							<< j << ")\n";
						return;
					}
				}
			}
			
		}
}

int Inventory2::getEmptySlot()
{
	for (int i = 0; i < maxCapacity; i++)
	{
		if (bag[i]->renderable == false)
		{
			return i;
		}
	}
}

int Inventory2::getEmptyBag()
{
	for (int j = 0; j < maxCapacity; j++)
	{
		//if (slots[j].empty == true)
		{
			return j;
		}
	}
}

void Inventory2::placeWeapon(SDL_Renderer* gRenderer, int slot, int spritenum, int projectilenum, int damage1, int range1)
{
	for (int i = 0; i < maxCapacity; i++)
	{
		if (bag[i]->renderable == false)
		{
			delete bag[i];
			for (int j = 0; j < maxCapacity; j++)
			{
			//	if (slots[j].empty == true)
				{
					//bag[i] = new Weapon(slots[j].x, slots[j].y, slot, spritenum, gRenderer, projectilenum, damage1, range1);
					bag[i]->slot = j;
				//	slots[j].empty = false;

					std::cout << "placed a weapon in bag x and slot y: (" << i << ", "
						<< j << ")\n";
					return;
				}
			}
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Inventory3::Inventory3(int x1, int y1, int rowWidth1, int rowHeight1)
{
	boxSize = { 0, 0, 64, 64};
	tileWidth = 64;
	capacity = rowWidth1 * rowHeight1;
	x = x1;
	y = y1;
	rowWidth = rowWidth1;
	rowHeight = rowHeight1;
	padding = 5;
	initInv();
	grabbedItem = -1;

	boxOutline = { 0, 0, 70, 70 };
	selectedBox = 0;
}

void Inventory3::moveX(int x)
{
	for (int i = 0; i < capacity; i++)
	{
		boxes[i]->x += x;
	}
}

void Inventory3::moveY(int x)
{
	for (int i = 0; i < capacity; i++)
	{
		boxes[i]->y += x;
	}
}

void Inventory3::render(SDL_Renderer* gRenderer, int mx, int my)
{
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
	for (int i = 0; i < capacity; i++)
	{
		if (i == selectedBox)
		{
			boxOutline.x = x + boxes[i]->x - 3;
			boxOutline.y = y + boxes[i]->y - 3;
			SDL_RenderFillRect(gRenderer, &boxOutline);
		}

		boxTexture->renderInventory(boxes[i]->x + x, boxes[i]->y + y, &boxSize, gRenderer);
		if (boxes[i]->object != NULL)
		{
			
			if (i == grabbedItem)
			{
				boxes[i]->object->render(mx, my, gRenderer);
			}
			else
			boxes[i]->object->render(x + boxes[i]->x + (64/2 - boxes[i]->object->width) , y + boxes[i]->y + (64 / 2 - boxes[i]->object->height), gRenderer);
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

void Inventory3::addItem(Renderable* target)
{
	for (int i = 0; i < capacity; i++)
	{
		if (boxes[i]->object == NULL)
		{
			boxes[i]->setObject(target);
			break;
		}
	}
}

void Inventory3::swapItemBoxes(int box1, int box2)
{
	Renderable* temp = NULL;
	temp = boxes[box1]->object;
	boxes[box1]->object = boxes[box2]->object;
	boxes[box2]->object = temp;
}

void Inventory3::clickItem(int box, Player* player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room)
{
	bool delete_ = boxes[box]->object->click(*player, equip, gRenderer, this, pManager, camera, room);

	if (delete_ == false)
	{
	//	delete boxes[box]->object;
	//	boxes[box]->object = NULL;
	}
}

int Inventory3::getBoxCollision()
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);

	int leftA, rightA;
	int topA, bottomA;
	for (int i = 0; i < capacity; i++)
	{
		if (boxes[i]->object != NULL)
		{
			leftA = boxes[i]->x + x;
			rightA = leftA + tileWidth;
			topA = boxes[i]->y + y;
			bottomA = topA + tileWidth;

			if ((bottomA <= my) || (topA >= my) || (rightA <= mx) || (leftA >= mx))
			{

			}
			else
			{
				return i;
			}
		}
	}
	return -1;
}

void Inventory3::setTileTextures(LTexture* target)
{
	for (int i = 0; i < capacity; i++)
	{
	//	boxes[i]->setBoxTexture(target);
	}
}


void Inventory3::initInv()
{

	int x1= 0;
	int y1 = 0;
	for (int i = 0; i < capacity; i++)
	{

		boxes[i] = new Boxes(x1, y1, tileWidth, i);

		x1 += (padding + tileWidth);
		if (x1 >= (padding + tileWidth) * rowWidth)
		{
			x1 = 0;
			y1 += padding + tileWidth;
			if (y1 >= (padding + tileWidth) * rowHeight) break;
		}
	}
}