#ifndef __Tile__
#define __Tile__

#include "SDL.h"
#include "LTexture.h"
#include <fstream>


class Tile
{
public:
	friend bool setTiles(Tile* tiles[], std::string levelname);
	friend void setTiles_();
	Tile(int x = -30000, int y = -30000, int tileType = 0);

	//shows tile
	void renderRotation(double x1, double y1, SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& target, double rotation);
	void render(SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& target, double rotation);

	//get tile type
	int getType();
	void setType(int type);

	//get collision box
	SDL_Rect getBox();
	SDL_Rect mBox;

private:
	//attributes
	

	//type
	int mType = 0;
};

bool loadLevelOneMedia(Tile* tileSet[], SDL_Renderer* gRenderer, std::string levelname);


const int TOTAL_TILES = 16 * 12;
const int TOTAL_TILE_SPRITES = 11;

const int TILE_HEIGHT = 64;
const int TILE_WIDTH = 64;

static LTexture gTileTexture;
static SDL_Rect gLevelOneClips[15];

#endif
