#ifndef __equipinv__
#define __eqiupinv__

class Inventory2;
class Projectile;
class Player;
#include "LTexture.h"
#include "Renderable.h"

struct Boxes1
{
	int x, y;
	bool empty;
};

class EquipInv
{
public:
	EquipInv(int x, int y);

	int getInventoryNumber(Renderable& a);

	int getMouse_Collision(int x, int y);

	void handleEvent(SDL_Event& e);

	void handleMovement(Player& player, Inventory2& inventory, SDL_Renderer* gRenderer);

	void loadSprite(std::string filename, SDL_Renderer* gRenderer);

	void render(SDL_Rect& camera, SDL_Renderer* gRenderer);

	void placeHelemt(SDL_Renderer* gRenderer);

	void placeWeapon(SDL_Renderer* gRenderer);

	void renderModularItems(Player& player, SDL_Renderer* gRenderer, SDL_Rect& camera);

	int getProjectile();

	Renderable* equips[5];
	Boxes1* slots;

private:
	int slotSize, padding;
	int x_, y_;
	int width_, height_;
	int currentSelection;
	int rows, columns;

	LTexture spriteSheet;
	SDL_Rect clips[5];
	SDL_Rect mouseCollider;

	bool clicking, activating;



	void initEquip();

};


#endif