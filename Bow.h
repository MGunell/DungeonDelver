#pragma once
class Inventory3;
#include "Weapon.h"

class Bow : public Weapon
{
public:
	//   (x, y, slot sprite projectilenum dmg range projectiles speed)
	Bow(int x1, int y1, int slot1, int spritenum, SDL_Renderer* gRenderer, int projectilenum, int damage1, int range1, int projectiles1 = 1, int speed1 = 3) : Weapon(x1, y1, slot1, spritenum, gRenderer, projectilenum, damage1, range1, speed1)
	{
		projectiles = projectiles1;
		std::cout << "\ncrerated bow\n";
		Renderable::width = 11;
		Renderable::height = 25;
		setSpriteFile("images/bows.png", gRenderer);
		renderable = true;
		setMessage(spritenum, gRenderer);
		setClips();
		setSprite(spritenum);
	}

	void setMessage(int spritenum, SDL_Renderer* gRenderer)
	{
		switch (spritenum)
		{
		case 0:
			message = "An old and unusal bow.\n";
			break;
		case 1:
			message = "A bow forged from ancient dwarves in the heart of Trondheim.\n";
			break;
		case 2:
			message = "An elven bow forged in the heart of Indelai.\n";
			break;
		case 3:
			message = "A bow used by the hero of old.\n";
			break;
		}
		nonModularMessage = "damage = " + std::to_string(damage) + "\nrange = " + std::to_string(range) + "\nprojectiles = " + std::to_string(projectiles);
		message += nonModularMessage;
		messageSprite.loadFromRenderedTextWrapped(message, textColor, gRenderer, gFont1);
	}

	void setClips();

	void placeInBag(Inventory2* inv, SDL_Renderer* gRenderer);

	bool click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room);

	int angle = 20;
};