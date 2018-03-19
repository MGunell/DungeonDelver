#ifndef __Weapon__
#define __Weapon__
class Projectile;
class Player;
class SDL_Font;
class EquipInv;
class Inventory2;
#include "Renderable.h"
#include "SDL_ttf.h"
#include "SDL_Image.h"

class Weapon : public Renderable
{
public:
	Weapon(int x1, int y1, int slot1, int spritenum, SDL_Renderer* gRenderer, int projectilenum, int damage1, int range1, int speed1) : Renderable(x1, y1)
	{
		//width = 25;
		//height = 50;
		speed = speed1;
		damage = damage1;
		range = range1;
		projectiles = 1;
		Weapon::setClips();
		setSpriteFile("images/swords.png", gRenderer);
		renderable = true;
		setSprite(spritenum);
		equipslot = slot1;
		setProjectile(projectilenum);
		//setMessage(spritenum, gRenderer);
	}

	virtual void setMessage(int spritenum, SDL_Renderer* gRenderer)
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

	void displayInfo(SDL_Renderer* gRenderer);

	virtual void setClips();

	void setMessage(std::string newMessage, SDL_Renderer* gRenderer) { 
		
		message = newMessage;
		message += message + nonModularMessage;
		messageSprite.loadFromRenderedText(message, textColor, gRenderer, gFont1);
	}

	int getProjectile() {return projectile;}

	void setProjectile(int projectilenum)
	{
		projectile = projectilenum;
	}

	virtual bool click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera);
	
	virtual void placeInBag(Inventory2* inv, SDL_Renderer* gRenderer);

protected:
	LTexture* Sprite;
	
	int speed;
	int projectile;
	int damage;
	int range;
	int projectiles;
	double angle;
	int equipslot;

};

#endif