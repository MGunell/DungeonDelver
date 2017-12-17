#ifndef __Tile__
#define __Tile__

#include "SDL.h"
#include "LTexture.h"
#include <fstream>

class Tile
{
public:
	friend bool setTiles(Tile* tiles[]);
	Tile(int x, int y, int tileType);

	//shows tile
	void render(SDL_Rect& camera, SDL_Renderer* gRenderer);

	//get tile type
	int getType();
	void setType(int& type);

	//get collision box
	SDL_Rect getBox();

private:
	//attributes
	SDL_Rect mBox;

	//type
	int mType = 0;
};

bool loadLevelOneMedia(Tile* tileSet[], SDL_Renderer* gRenderer);


const int TOTAL_TILES = 16 * 12;
const int TOTAL_TILE_SPRITES = 1;

const int TILE_HEIGHT = 64;
const int TILE_WIDTH = 64;

static LTexture gTileTexture;
static SDL_Rect gLevelOneClips[10];

#endif
