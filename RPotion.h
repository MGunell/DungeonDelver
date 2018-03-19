#ifndef __RPotion__
#define __RPotion__

class EquipInv;
class Inventory;
#include "Renderable.h"
class RPotion : public Renderable
{
public: 
	RPotion(int x1, int y1, int resolution, int clip, SDL_Renderer* gRenderer) : Renderable(x1, y1) {
		setSpriteFile("images/potions2.png", gRenderer);
		setSprite(clip);
		renderable = true;
		healAmount = 25;
		message = "A small health potion.\n";
		nonModularMessage = "heal amount = " + std::to_string(healAmount); 
		message += nonModularMessage;
		messageSprite.loadFromRenderedTextWrapped(message, textColor, gRenderer, gFont1);
		Renderable::width = 11;
		Renderable::height = 12;
		setClips();
	}

	void placeItem(Inventory& inv);

	void displayInfo(SDL_Renderer* gRenderer) {
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
	};

	bool click(Player* player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager);

private:
	int healAmount;
};

#endif
