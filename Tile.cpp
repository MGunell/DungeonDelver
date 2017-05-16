#include "Tile.h"

LTexture gTileTexture;
SDL_Rect gLevelOneClips[4];

Tile::Tile(int x, int y, int tileType)
{
	mBox.x = x;
	mBox.y = y;

	//collision size of each tile
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	mType = tileType;
	//0 = walk thru, 1 = wall, 2 = ... 
}

void Tile::render(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	if (checkCollision(camera, mBox))
	{
		//show tile
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gLevelOneClips[mType], gRenderer);
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

bool setTiles(Tile* tiles[])
{
	bool tilesLoaded = true;

	int x = 50;
	int y = 100;

	//open map
	std::ifstream map("maps/levelone.map");

	if (!map.is_open())
	{
		tilesLoaded = false;
	}
	else
	{
		for (int i = 0; i < TOTAL_TILES; i++)
		{
			int tileType = -1;

			map >> tileType;

			if (map.fail())
			{
				tilesLoaded = false;
				break;
			}

			if (tileType >= 0)
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			else
			{
				tilesLoaded = false;
				break;
			}

			//move to next spot
			x += TILE_WIDTH;
			if (x >= (16 * TILE_WIDTH)+50)
			{
				x = 50;
				y += TILE_HEIGHT;
			}
		}
		if (tilesLoaded)
		{
			gLevelOneClips[0].x = 640;
			gLevelOneClips[0].y = 0;
			gLevelOneClips[0].w = 32;
			gLevelOneClips[0].h = 32;

			gLevelOneClips[1].x = 672;
			gLevelOneClips[1].y = 224;
			gLevelOneClips[1].w = 32;
			gLevelOneClips[1].h = 32;

			gLevelOneClips[2].x = 672;
			gLevelOneClips[2].y = 192;
			gLevelOneClips[2].w = 32;
			gLevelOneClips[2].h = 32;

			gLevelOneClips[3].x = 640;
			gLevelOneClips[3].y = 256;
			gLevelOneClips[3].w = 32;
			gLevelOneClips[3].h = 32;
		}
	}

	map.close();

	return tilesLoaded;
}

bool loadLevelOneMedia(Tile* tileSet[], SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!gTileTexture.loadFromFile("images/levelone.png", gRenderer))
	{
		printf("couldnt load level one textures");
		success = false;
	}

	if (!setTiles(tileSet))
	{
		printf("couldnt set tiles");
		success = false;
	}

	

	return success;
}

