#ifndef __RPotion__
#define __RPotion__

class Inventory;
#include "Renderable.h"
class RPotion : public Renderable
{
public: 
	RPotion(int x1, int y1, int resolution, int clip, SDL_Renderer* gRenderer) : Renderable(x1, y1, resolution) {
		setSpriteFile("images/potions2.png", gRenderer);
		setSprite(clip);
		renderable = true;
	}

	void placeItem(Inventory& inv);

	void click(Player& player);
};

#endif
