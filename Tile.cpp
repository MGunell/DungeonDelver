#include "Tile.h"

LTexture gTileTexture;
SDL_Rect gLevelOneClips[10];


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
	//if (checkCollision(camera, mBox))
	//{
		//show tile
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gLevelOneClips[mType], gRenderer);
	//}
}

int Tile::getType()
{
	return mType;
}

void Tile::setType(int& type) {
	mType = type;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

bool setTiles(Tile* tiles[])
{
	bool tilesLoaded = true;

	int x = 0;
	int y = 0;

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
			if (x >= (16 * TILE_WIDTH))
			{
				x = 0;
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

			gLevelOneClips[4].x = 480;
			gLevelOneClips[4].y = 896;
			gLevelOneClips[4].w = 32;
			gLevelOneClips[4].h = 32;

			gLevelOneClips[5].x = 512;
			gLevelOneClips[5].y = 896;
			gLevelOneClips[5].w = 32;
			gLevelOneClips[5].h = 32;

			gLevelOneClips[6].x = 544;
			gLevelOneClips[6].y = 896;
			gLevelOneClips[6].w = 32;
			gLevelOneClips[6].h = 32;

			gLevelOneClips[7].x = 704;
			gLevelOneClips[7].y = 288;
			gLevelOneClips[7].w = 32;
			gLevelOneClips[7].h = 32;

			//gLevelOneClips[8].x = 640;
			//gLevelOneClips[8].y = 256;
			//gLevelOneClips[8].w = 32;
			//gLevelOneClips[8].h = 32;

			//gLevelOneClips[9].x = 640;
			//gLevelOneClips[9].y = 256;
			//gLevelOneClips[9].w = 32;
			//gLevelOneClips[9].h = 32;
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

