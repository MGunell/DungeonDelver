#ifndef __Potion__
#define __Potion__

class Player;
class Item;

#include "Item.h"
class Potion : public Item {
public:
	Potion(int x, int y, int textureClip) : Item(x, y, textureClip) {
		renderable = true;
		width = 18;
		height = 30;
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
#endif