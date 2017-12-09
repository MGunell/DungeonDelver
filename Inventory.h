#pragma once
#include "stdafx.h"
#include <iostream>

const int ITEMS = 10;
LTexture itemTexture;
SDL_Rect itemImage[ITEMS];


class Item {
 public:

	 Item(int x1 = 0, int y1 = 0, int width1 = 20, int height1 = 25) 
		 : x(x1), y(y1), width(width1), height(height1) {renderable = false;};
	int x, y, width, height;
	bool renderable;
	virtual bool getRenderable() {
		return renderable;
	};;
	virtual void click() {
		std::cout << "click" << std::endl;
	};
	virtual void render(SDL_Rect& camera, SDL_Renderer* gRenderer)
	{
		itemTexture.render(x, y, &itemImage[0], gRenderer);
	};
	//LTexture itemTexture;
	//SDL_Rect itemImage;//these will be the coordinates of the item in the spriteSheet;

};

class Potion : public Item {
public:
	Potion() { 
		renderable = true;
	}

	bool getRenderable()
	{
		return renderable;
	}
	void click() {
		std::cout << "you drank a potion and regained some hp" << std::endl;
	}

};

class Inventory {
public:
	Inventory() {
		x = 40;
		y = 40;
		rows = 10;
		columns = 2;
		capacity = new Item[maxCapacity];
		tileWidth = 32;
		tileHeight = 32;
		tilePadding = 10; // pixels inbetween each inventory slot;
		initSlot();
		inventory_open = true;
		mouseCollider = { 0, 0, 20, 20 };
		clicking = false;
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

	void handleMovement() {
		if (inventory_open) {
			int mem1 = -1, mem2 = -1, mem3 = -1;
			SDL_GetMouseState(&x, &y);
			mouseCollider.x = x;
			mouseCollider.y = y;
			int originalx, originaly;

			if (clicking == true) {
				std::cout << "we are clicking" << std::endl;
				std::cout << mouseCollider.x << " " << mouseCollider.y << std::endl;
				for (int i = 0; i < maxCapacity; i++)
				{
					if (getItem_Collision(mouseCollider, capacity[i]) == true)
					{
						std::cout << "We are colliding" << std::endl;
						mem1 = i;
						capacity[i].x = x;
						capacity[i].y = y;
					}

				}
			}
			if (activating)
			{
				activating = false;
				for (int i = 0; i < maxCapacity; i++)
				{
					if (mem1 >= 0)
					{
						if (getItem_Collision(mouseCollider, capacity[i]))
						{
							//swap the colliders as well as the renderers
							//for the items
							mem2 = capacity[mem1].x;
							capacity[mem1].x = capacity[i].x;
							capacity[i].x = mem2;

							mem3 = capacity[mem1].y;
							capacity[mem3].y = capacity[i].y;
							capacity[i].y = mem2;
						}
					}
				}	
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
		for (int i = 0; i < maxCapacity; i++)
		{
			if (capacity[i].getRenderable())
			{
				capacity[i].render(camera, gRenderer);
			}
		}
	}

	Item* capacity;
private:
	int x, y;
	int rows, columns;
	int tileWidth, tileHeight, tilePadding;
	void initSlot() {
		int tilePaddingReset = tilePadding;
		for (int x = 0; x < columns; x++) {
			for (int y = 0; y < rows; y++) {
				capacity[(x*10) + y].x = x * tileWidth +  (x *tilePadding);
				capacity[(x*10) + y].y = y * tileHeight + (y *tilePadding);
			}
		}
		for (int r = 0; r < maxCapacity; r++)
			std::cout << capacity[r].x << " " << capacity[r].y << std::endl;

	}
	const int maxCapacity = 20;
	SDL_Rect mouseCollider;
	bool clicking, activating, inventory_open;

};

void loadItemMedia(SDL_Renderer* gRenderer) {
	itemTexture.loadFromFile("images/levelone.png", gRenderer);
	itemImage[0].x = 839;
	itemImage[0].y = 867;
	itemImage[0].w = 20;
	itemImage[0].h = 25;
}