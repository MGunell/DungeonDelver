#pragma once
class Inventory3;
#include "Weapon.h"
class Sword : public Weapon
{
public:

	Sword(int x1, int y1, int slot1, int spritenum, SDL_Renderer* gRenderer, int projectilenum, int damage1, int range1, int projectiles1 = 1, int speed1 = 3) : Weapon(x1, y1, slot1, spritenum, gRenderer, projectilenum, damage1, range1, speed1)
	{
		projectiles = 1;
		Renderable::width = 15;
		Renderable::height = 38;
		setSpriteFile("images/swords1.png", gRenderer);
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
			message = "An old wooden shortsword.\n";
			break;
		case 1:
			message = "A regal sword from a simpler time.\n";
			break;
		case 2:
			message = ".....\n";
			break;
		case 3:
			message = "A sword used by the hero of old.\n";
			break;
		}
		nonModularMessage = "damage = " + std::to_string(damage) + "\nrange = " + std::to_string(range) + "\nprojectiles = " + std::to_string(projectiles);
		message += nonModularMessage;
		messageSprite.loadFromRenderedTextWrapped(message, textColor, gRenderer, gFont1);
	}

	void setClips();

	bool click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room);

	//void placeInBag(Inventory2* inv, SDL_Renderer* gRenderer);

	//bool click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera);

	int angle = 20;
};