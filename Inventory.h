#ifndef __Inventory__
#define __Inventory__

class Player;
#include <iostream>
#include "LTexture.h"
#include "SDL.h"
#include "Player.h"


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

const int ITEMS = 10;
static LTexture inventoryTexture;
static LTexture itemTexture;
static SDL_Rect itemImage[ITEMS];


struct invBoxes
{
	int x, y;
	bool empty;
};


class Item {
 public:

	 Item(int x1 = -100, int y1 = -100, int textureClip = 1, bool empty1 = true, int width1 = 50, int height1 = 50)
		 :x(x1), y(y1), width(width1), height(height1), textureClip(textureClip), empty(empty1) {
		 renderable = false;
		 originalx = x;
		 originaly = y;
		 boundary = { x, y, width, height };
	 };
	int x, y, width, height;
	int textureClip;
	bool renderable;
	SDL_Rect ok = { 0, 0, 25, 25 };

	int slot = -1;

	int originalx, originaly;
	bool empty;

	virtual bool getRenderable() {
		return renderable;
	};
	virtual void click(Player& player) {
		std::cout << "click" << std::endl;
	};
	virtual void render(SDL_Renderer* gRenderer)
	{
		//std::cout << x << ", " << y << std::endl;
		//std::cout << ok.x << ok.w;
		itemTexture.render(x + 4, y + 2, &ok, gRenderer);

		//SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255);
		//SDL_RenderFillRect(gRenderer, &itemImage[1]);
	};

	virtual void renderDrops(SDL_Rect& camera, SDL_Renderer* gRenderer)
	{
		itemTexture.render(x - camera.x, y - camera.y, &itemImage[textureClip], gRenderer);
	};

	virtual void addItem(Item* items[])
	{
		for (int i = 0; i < 30; i++)
		{
			if (items[i]->empty == true)
			{

			}
				
		}
	}
	//LTexture itemTexture;
	SDL_Rect boundary;//these will be the coordinates of the item in the spriteSheet;

};
extern Item* droppedItems[30];

static int getEmpty(Item* items[]) {
	for (int i = 0; i < 30; i++) {
		if (items[i]->empty == true) return i;
	}
	return -1;
}


class Potion : public Item {
public:
	Potion(int x, int y, int textureClip) : Item(x, y, textureClip) { 
		renderable = true;
		width = 25;
		height = 25;
		healingAmount = 25;
	}

	bool getRenderable()
	{
		return renderable;
	}

	virtual void click(Player& player) {
		std::cout << "you drank a potion and regained some hp" << std::endl;
		player.heal(healingAmount);
	}

	void addItem(Item* items[])
	{
		int empty = getEmpty(items);
		delete items[empty];
		items[empty] = new Potion(x, y, textureClip);
	}

	int healingAmount;

};

class Inventory {
public:
	Inventory() {
		rows = 3;
		columns = 5;
		for (int i = 0; i < maxCapacity; i++)
		capacity[i] = new Item;
		slots = new invBoxes[maxCapacity];
		UI.w = (SCREEN_WIDTH / 4) + 45;
		UI.h = SCREEN_HEIGHT;
		UI.y = 0;
		UI.x = SCREEN_WIDTH - UI.w;

		x1 = UI.x + 4;
		y1 = SCREEN_HEIGHT / 2;
		tileWidth = 55;
		tileHeight = 55;
		tilePadding = 15; // pixels inbetween each inventory slot;
		tilePaddingy = 15;
		initSlot();
		inventory_open = true;
		mouseCollider = { 0, 0, 5, 5 };
		clicking = false;
		activating = false;
	}

	void handleEvent(SDL_Event& e)
	{
		//if key is pressed
		if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				clicking = true;
				int x, y;
				SDL_GetRelativeMouseState(&x, &y);
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


		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//adjust velocity
			//switch (e.key.keysym.sym)
			{
				//case SDLK_q: talked = true;
			}
		}
		//key release boi
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_l:
				inventory_open = !inventory_open;
				break;
			}

		}
	}

	void placePotion(int clip)
	{
		for (int i = 0; i < maxCapacity; i++)
		{
			if (slots[i].empty == true)
			{
				//delete capacity[i];
				int x = slots[i].x;
				int y = slots[i].y;
				capacity[i] = new Potion(x, y, clip);
				capacity[i]->slot = i;	

				slots[i].empty = false;
				break;
			}

		}
	}


	void debugItem(SDL_Renderer* grenderer) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		int box = getMouse_Collision(x, y);
		if (box > -1) {
			SDL_Rect squareHere = { slots[box].x, slots[box].y , tileWidth, tileHeight };
			SDL_SetRenderDrawColor(grenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(grenderer, &squareHere);
			SDL_SetRenderDrawColor(grenderer, 0x00, 0x00, 0x00, 0xFF);
			//if( capacity[box]== Potion)
			//}
		}
	}


		void handleMovement(Player& player) {
			if (inventory_open) {
				int mousexDelt, mouseyDelt;
				SDL_GetRelativeMouseState(&mousexDelt, &mouseyDelt);
				SDL_GetMouseState(&mouseCollider.x, &mouseCollider.y);

				if (clicking == true) {
					for (int i = 0; i < maxCapacity; i++)
					{
						if (capacity[i]->renderable && mem1 < 0)
						{
							if (getItem_Collision(mouseCollider, *capacity[i]) == true)
							{
								mem1 = i;
							}
						}
					};
					if (mem1 >= 0)
					{
						capacity[mem1]->x += mousexDelt;
						capacity[mem1]->y += mouseyDelt;
					}
				}

				if (activating)
				{
					activating = false;
					
					if (mem1 > -1)
					{
						int movedx = slots[capacity[mem1]->slot].x - capacity[mem1]->x;
						int movedy = slots[capacity[mem1]->slot].y - capacity[mem1]->y;
						double dist = sqrt((movedx*movedx) + (movedy * movedy));
						if (dist < 4)
						{
							capacity[mem1]->click(player);
							delete capacity[mem1];
							capacity[mem1] = new Item(slots[mem1].x, slots[mem1].y);
							slots[mem1].empty = true;

						}

						for (int i = 0; i < maxCapacity; i++)
						{
							if (mem1 >= 0 && mem1 != i)//&& capacity[i].renderable)
							{
								if (getItems_Collision(*capacity[mem1], *capacity[i]) && capacity[i]->empty == true)
								{
									//std::cout << "we have activated and two items have collided";
									//to swap the second objects x and y become original x and y of first obj
									//after that we need to set the
									/*mem2 = capacity[i].x;
									mem3 = capacity[i].y;

									capacity[i].x = capacity[mem1].originalx;
									capacity[i].y = capacity[mem1].originaly;

									capacity[mem1].x = mem2;
									capacity[mem1].y = mem3;

									//now we need to update original x and y pos for both objects
									capacity[i].originalx = capacity[i].x;
									capacity[i].originaly = capacity[i].y;
									capacity[mem1].originalx = capacity[mem1].x;
									capacity[mem1].originaly = capacity[mem1].y;*/

								}

							}
						}
						int invNum = getInventoryNumber(*capacity[mem1]);
						if (invNum > -1)
						{
							if (invNum == capacity[mem1]->slot)
							{
								std::cout << "staying in place, slot: " << capacity[mem1]->slot + 1 << std::endl;
								capacity[mem1]->x = slots[capacity[mem1]->slot].x;
								capacity[mem1]->y = slots[capacity[mem1]->slot].y;
							}
							else
							{

								if (slots[invNum].empty == true)
								{
									capacity[mem1]->x = slots[invNum].x;
									capacity[mem1]->y = slots[invNum].y;
									slots[invNum].empty = false;
									slots[capacity[mem1]->slot].empty = true;
									capacity[mem1]->slot = invNum;
									std::cout << invNum + 1 << std::endl;
								}
								else if (slots[invNum].empty == false)
								{
									//here we swap positions of the two
									capacity[mem1]->x = slots[invNum].x;
									capacity[mem1]->y = slots[invNum].y;

									int itemNum;
									int itemNum2 = capacity[mem1]->slot;
									for (int i = 0; i < maxCapacity; i++)
									{
										if (capacity[i]->slot == invNum)
											itemNum = i;
									}
									capacity[itemNum]->x = slots[itemNum2].x;
									capacity[itemNum]->y = slots[itemNum2].y;

									capacity[itemNum]->slot = itemNum2;
									capacity[mem1]->slot = invNum;

									std::cout << "grabbedItem slot: " << invNum << "replaced item new slot: "
										<< itemNum2 << std::endl;
								}
							}
						}
					}

				}

				if (clicking == false && mem1 > -1)
				{
					//capacity[mem1].originalx = capacity[mem1].x;
					//capacity[mem1].originaly = capacity[mem1].y;
					//std::cout << "we have stopped clicking and set the original x,y: ";
					//std::cout << capacity[mem1].originalx << ", " << capacity[mem1].originaly << std::endl;
					mem1 = -1; mem2 = -1; mem3 = -1;
				}
			}
		}

		bool getItem_Collision(SDL_Rect& a, Item& b) {
			int leftA, leftB;
			int rightA, rightB;
			int topA, topB;
			int bottomA, bottomB;

			leftA = a.x;
			rightA = a.x + a.w;
			topA = a.y;
			bottomA = a.y + a.h;

			leftB = b.x;
			rightB = b.x + b.width * 2;
			topB = b.y;
			bottomB = b.y + b.height * 2;


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

		int getMouse_Collision(int x, int y) {
			int leftA, leftB;
			int rightA;
			int topA, topB;
			int bottomA;

			leftB = x;
			topB = y;

			for (int x = 0; x < columns; x++) {
				for (int y = 0; y < rows; y++) {
					//break here
					leftA = (x * tileWidth + (x *tilePadding)) + x1;
					rightA = leftA + tileWidth;
					topA = (y * tileHeight + (y *tilePaddingy)) + y1;
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

		int getInventoryNumber(Item& a) {
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
					topA = (y * tileHeight + (y *tilePaddingy)) + y1;
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

		bool getItems_Collision(Item& a, Item& b) {
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

		void renderItems(SDL_Rect& camera, SDL_Renderer* gRenderer)
		{
			SDL_SetRenderDrawColor(gRenderer, 140, 94, 4, 255);
			SDL_RenderFillRect(gRenderer, &UI);
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			inventoryTexture.renderInventory(UI.x + 5, SCREEN_HEIGHT / 2, &itemImage[0], gRenderer);
			for (int i = 0; i < maxCapacity; i++)
			{
				/*SDL_Rect hbox = { capacity[i]->x, capacity[i]->y, capacity[i]->width, capacity[i]->height };
				SDL_RenderFillRect(gRenderer, &hbox);*/
				if (capacity[i]->getRenderable())
				{
					capacity[i]->render(gRenderer);
				}
			}
		}

		Item* capacity[15];
		invBoxes* slots;
private:
	SDL_Rect UI;
	int x1, y1;
	int rows, columns;
	int tileWidth, tileHeight, tilePadding, tilePaddingy;
	void initSlot() {
		for (int x = 0; x < columns; x++) {
			for (int y = 0; y < rows; y++) {
				//break here
				//capacity[x + y * columns].x = (x * tileWidth + (x *tilePadding)) + x1;
				//capacity[x + y * columns].y = (y * tileHeight + (y *tilePaddingy)) + y1;
				slots[x + y * columns].x = (x * tileWidth + (x *tilePadding)) + x1;
				slots[x + y * columns].y = (y * tileHeight + (y *tilePaddingy)) + y1;
				slots[x + y * columns].empty = true;
			}
		}
		//for (int r = 0; r < 15; r++) std::cout << capacity[r].x << " " << capacity[r].y << std::endl;
		mem1 = -1; mem2 = -1; mem3 = -1;
	}
	const int maxCapacity = 15;
	SDL_Rect mouseCollider;
	bool clicking, activating, inventory_open;
	int mem1, mem2, mem3;

	};

static void loadItemMedia(SDL_Renderer* gRenderer) {
	{
		inventoryTexture.loadFromFile("images/inventory.png", gRenderer);
		itemImage[0].x = 0;
		itemImage[0].y = 0;
		itemImage[0].w = 335;
		itemImage[0].h = 195;
	}		
};

static void loadPotionMedia(SDL_Renderer* gRenderer)
{
	{
		itemTexture.loadFromFile("images/potions2.png", gRenderer);
		itemImage[1].x = 0;
		itemImage[1].y = 0;
		itemImage[1].w = 25;
		itemImage[1].h = 25;

		itemImage[2].x = 26;
		itemImage[2].y = 0;
		itemImage[2].w = 25;
		itemImage[2].h = 25;
	}

}

#endif