#ifndef __Inventory2__
#define __Inventory2__



class Player;
#include "Ltexture.h"
#include "Renderable.h"

struct Boxes
{
	int x, y;
	bool empty;
};

class Inventory2
{
public:
	Inventory2(SDL_Renderer* gRenderer);
	~Inventory2() {  }

	void placeRenderable(Renderable* item);

	void setSprite(std::string path, SDL_Renderer* gRenderer);

	void handleEvent(SDL_Event& e);

	void handleMovement(Player& player);

	int getMouse_Collision(int x, int y);

	bool getItems_Collision(Renderable& a, Renderable& b);

	int getInventoryNumber(Renderable& a);

	void renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer);

	void placePotion(SDL_Renderer* gRenderer);

private:
	void initInv();

	LTexture Sprite;
	Renderable* bag[15];
	Boxes* slots;
	int maxCapacity;
	int used;
	int rows, columns;
	int tileWidth, tilePadding, tileHeight;
	int currentSelection;
	SDL_Rect clip;
	SDL_Rect UI;
	SDL_Rect mouseCollider;

	int x1, y1;

	bool clicking, activating;

};

#endif