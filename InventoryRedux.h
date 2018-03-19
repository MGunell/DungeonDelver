#ifndef __Inventory2__
#define __Inventory2__


class EquipInv;
class Player;
class Room;
#include "Ltexture.h"
#include "Renderable.h"

class Boxes
{
public:
	Boxes(int x1, int y1, int width1, int id1) {
		x = x1;
		y = y1;
		width = width1;
		id = id1;
		object = NULL;
	};

	Boxes()
	{
		object = NULL;

		id = 0;
		x = 0, y = 0;
		width = 0;
	}
	

	void setObject(Renderable* target)
	{
		object = target;
	}

	int id;
	int x, y;
	int width;
	Renderable* object;
};


//ideal way this should be coded is that we have an inventory of 15 or so objects;
//the objects can be hard coded so as to be at set slots. each slot needs to have a bool
//empty as well as a pointer to an actual renderable object;
//so we have objects spawn as a result of dying to a monster
//these objects will be added to a renderable manager. this manager looks at renderables and 
//moves them and can also add them into an inventory.
//moving them into inventory kills their screen rendering flag
//and then assigns an empty inventory slot to it. when we hand it off we delete the pointer in the manager to it
//but we don't delete the object later on, until it is used
//this in reality should be a very simple thing
//no need for the inventory to store actual objects in itself
class Inventory3
{
public:
	Inventory3(int x1, int y1, int rowWidth1, int rowHeight1);

	void setTileTextures(LTexture* target);

	void setBoxTexture(LTexture* target)
	{
		boxTexture = target;
	}

	void moveX(int x);
	void moveY(int x);

	int getBoxCollision();

	void addItem(Renderable* target);

	void clickItem(int box, Player* player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room);

	void swapItemBoxes(int box1, int box2);

	void render(SDL_Renderer* gRenderer, int mx, int my);

	void initInv();

	void grabIitem(int item) {
		grabbedItem = item;
	}

	void releaseItem()
	{
		grabbedItem = -1;
	}

	LTexture* boxTexture;
	Boxes* boxes[30];
	SDL_Rect boxSize;
	SDL_Rect boxOutline;
	int selectedBox;
	int grabbedItem;
	int capacity;
	int tileWidth;
	int x, y;
	int rowWidth, rowHeight;
	int padding;

};

class Inventory2
{
public:
	Inventory2(SDL_Renderer* gRenderer);
	~Inventory2() {  };

	void placeRenderable(Renderable* item);

	void setSprite(std::string path, SDL_Renderer* gRenderer);

	void handleEvent(SDL_Event& e);

	void handleMovement(Player& player, EquipInv& inv, SDL_Renderer* gRenderer);

	int getMouse_Collision(int x, int y);

	bool getItems_Collision(Renderable& a, Renderable& b);

	int getInventoryNumber(Renderable& a);

	void renderAll(SDL_Rect& camera, SDL_Renderer* gRenderer);

	void placePotion(SDL_Renderer* gRenderer);

	void placeWeapon(SDL_Renderer* gRenderer, int slot, int spritenum, int projectilenum, int damage1, int range1);

	int getEmptySlot();
	int getEmptyBag();

	Renderable* bag[31];
	Boxes* slots;
private:
	void initInv();

	LTexture Sprite;
	
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