#ifndef __Renderable__
#define __Renderable__

class EquipInv;
class Player;
class Inventory2;
class Inventory3;
class Item;
class ProjectileManager;
class Room;
#include "SDL.h"
#include "LTexture.h"
#include <fstream>
#include <string>


class Renderable
{
public:

	//opens the file to grab sprites from
	// will  then set clips to grab sprites in a row just moving width length along
	Renderable(int x1, int y1);

	~Renderable();

	void setSpriteFile(std::string filename, SDL_Renderer* gRenderer);

	void waveMove();

	void render(SDL_Renderer* gRenderer, SDL_Rect& camera);
	void render(int x, int y, SDL_Renderer* gRenderer, double angle = 0.0);

	void renderInv(SDL_Renderer* gRenderer, SDL_Rect& camera);

	void setSprite(int num) { spriteNum = num; };

	int getSprite() { return spriteNum; }

	bool getAlive() { if (lifetime > 0) return true; else return false; };

	friend bool PickUp(Renderable& a, Player& p);

	void setXY(int x1, int y1) { x = x1; y = y1; };

	virtual void displayInfo(SDL_Renderer* gRenderer) {};

	virtual void placeItem(Inventory3* inv);

	virtual void placeInBag(Inventory2* inv, SDL_Renderer* gRenderer) {};

	virtual int getProjectile() { return NULL; }

	//virtual Item* placeSelf(int x, int y);

	virtual bool click(Player& player, EquipInv* equip, SDL_Renderer* gRenderer, Inventory3* inventory, ProjectileManager* pManager, SDL_Rect* camera, Room* room)
	{
		return false;
		//false means we delete the object
		std::cout << "clicked\n";
	};
	virtual void setClips();


	int lifetime;

	double x, y;
	int width, height;

	int slot;
	bool renderable;
	LTexture sprite;


	SDL_Rect clips[20];

	SDL_Color textColor = { 0, 0, 0 };
	TTF_Font* gFont1;

	std::string  message;
	std::string nonModularMessage;
	LTexture messageSprite;

	SDL_Rect displayBox;
private:
	
	SDL_Rect hitBox;
	int spriteNum;
	double angle;


};

#endif