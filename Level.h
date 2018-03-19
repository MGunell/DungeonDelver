#pragma once

class LevelGenerator;
class PlayerManager;
class EnemyManager;
class ProjectileManager;
class TileManager;

class Tile;
#include "Tile.h"
#include "Room.h"
#include "TileManager.h"
#include "EnemyManager.h"
#include"ProjectileManager.h"
#include "PlayerManager.h"
#include "LevelGenerator.h"
class gridNode
{
public:
	gridNode()
	{

		numerator = 0;

		_P = NULL;
		tiles = NULL;
		enemies = NULL;
		projectiles = nullptr;
		walls = NULL;
	}


	void update(SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& target, double rotation, Player& player)
	{
		//players->update();
		//enemies->moveAll();
		//projectiles->update();
		//walls->update();

		if (tiles != NULL)
		{
			tiles->renderAll(camera, gRenderer, &player, target, rotation);
		}
		if (walls != NULL)
		{
			walls->renderWallsTop(camera, gRenderer, &player, target, rotation);

		}
		if (_P != NULL)
		{
			_P->render(camera, _P->getClip(), gRenderer);
		}
		if (walls != NULL)
		{
			walls->renderWallsBottom(camera, gRenderer, &player, target, rotation);
		}

	}

	void insertTiles(Room* level, int x, int y)
	{
		bool created = false;
		bool created2 = false;
		for (int i = 0; i < level->roomCapacity; i++)
		{
			for (int j = 0; j < level->subrooms[i].capacity; j++)
			{
				//x * gridSize, start with 10*64

				if ((level->subrooms[i].tileset[j].mBox.x >= (x * 3640)) && (level->subrooms[i].tileset[j].mBox.x < ((x + 1) * 3640)))
					if (level->subrooms[i].tileset[j].mBox.y >= y * 3640 && level->subrooms[i].tileset[j].mBox.y < (y + 1) * 3640)
					{
						if (!created)
						{
							tiles = new TileManager;
							created = true;
						}
						tiles->insertEnemy(&(level->subrooms[i].tileset[j]));
					}
			}
		}

		for (int i = 0; i < level->wallsCapacity; i++)
		{
			if (level->walls[i].mBox.x >= (x * 3000) && level->walls[i].mBox.x < ((x+1) * 3000))
				if (level->walls[i].mBox.y >= (y * 3000)-32 && level->walls[i].mBox.y < ((y + 1) * 3000)-32)
				{
					if (!created2)
					{
						walls = new TileManager;
						created2 = true;
					}
					walls->insertEnemy(&(level->walls[i]));
				}
		}

	}

	void insertEnemies(EnemyManager* em, int x, int y)
	{
		bool created = false;
		node* temp;
		temp = em->head;

		while (temp != NULL)
		{
			if (temp->enemy->x > x * 3000 && temp->enemy->x < (x+1)*3000)
				if (temp->enemy->y > y * 3000 && temp->enemy->y > (y + 1) * 3000)
				{
					if (!created)
					{
						enemies = new EnemyManager;
						created = true;
					}
					enemies->insertEnemy(temp->enemy);
				}

			temp = temp->next;
		}

	}
	void insertPlayer(Player* p, int x, int y)
	{
		if (p->x > x * 3000 && p->x < (x + 1) * 3000)
		{
			if (p->y > y * 3000 && p->y < (y + 1) * 3000)
			{
				_P = p;
			}
		}
	}


	//PlayerManager* players;
	Player* _P;
	EnemyManager* enemies;
	ProjectileManager* projectiles;
	TileManager* tiles;
	TileManager* walls;
	int numerator;
};

class Level
{
public:
	Level(EnemyManager* Em, Player* player)
	{
		enemies = Em;
		players = player;
		rotation = 0.0;

		gX = 1;
		gY = 1;

		_Level = new LevelGenerator();
		LevelGrid = new gridNode*[8];
		for (int i = 0; i < 8; i++)
		{
			LevelGrid[i] = new gridNode[8];
		}

		for (int i = 0; i < gX; i++)
		{
			for (int j = 0; j < gY; j++)
			{
				LevelGrid[j][i].insertTiles(_Level->rooms[0], j, i);
				LevelGrid[j][i].insertEnemies(enemies, j, i);
				LevelGrid[j][i].insertPlayer(player, j, i);
			}
		}
		// we have made the floor and overlaying grid
		// now we need a way to insert tiles, players, enemies into these grids
		//then we run through and only do hit collision testing on grids the player is inside
		
	}

	void renderNodes(SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& target)
	{
		for (int i = 0; i < 1; i++ )
		{
			for (int j = 0; j < 1; j++)
			{
				LevelGrid[j][i].update(camera, gRenderer, target, rotation, *players);
			}
		}
	}

	void rotate(double amount)
	{
		rotation += amount;
	}
	double rotation;
	LevelGenerator* _Level;
private:
	
	int level;
	gridNode** LevelGrid;
	int gX, gY;

	Player* players;
	EnemyManager* enemies;


};