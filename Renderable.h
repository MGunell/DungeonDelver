#ifndef __Renderable__
#define __Renderable__

class Player;
class Inventory2;
class Item;
#include "SDL.h"
#include "LTexture.h"
#include <fstream>


class Renderable
{
public:

	//opens the file to grab sprites from
	// will  then set clips to grab sprites in a row just moving width length along
	Renderable(int x1, int y1, int resolution);

	~Renderable();

	void setSpriteFile(std::string filename, SDL_Renderer* gRenderer);

	void waveMove();

	void render(SDL_Renderer* gRenderer, SDL_Rect& camera);

	void renderInv(SDL_Renderer* gRenderer, SDL_Rect& camera);

	void setSprite(int num) { spriteNum = num; };

	int getSprite() { return spriteNum; }

	bool getAlive() { if (lifetime > 0) return true; else return false; };

	friend bool PickUp(Renderable& a, Player& p);

	void setXY(int x1, int y1) { x = x1; y = y1; };

	virtual void placeItem(Inventory2& inv, SDL_Renderer* gRenderer);

	//virtual Item* placeSelf(int x, int y);

	virtual void click(Player& player)
	{
		std::cout << "clicked\n";
	};

	int lifetime;

	double x, y;
	int width, height;

	int slot;
	bool renderable;

private:
	void setClips();

	SDL_Rect clips[20];
	SDL_Rect hitBox;
	int spriteNum;
	double angle;
	LTexture sprite;
};

#endif