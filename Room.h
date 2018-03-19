#pragma once

#include "Tile.h"
#include "SDL.h"
#include "Tile.h"
#include "Player.h"

class Vertex
{
public:
	Vertex()
	{};
	int x, y;
};

struct Line
{
	Line(int _x1, int _y1, int _x2, int _y2)
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	};

	void print()
	{
		std::cout << "(" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")\n";
	}

	int x1, y1;
	int x2, y2;
};


class Subroom
{
public:
	Subroom(int x = 0, int y = 0, int w = 0, int h = 0) : x(x), y(y), w(w), h(h) {
		tileset = NULL;
		ints = NULL;
		capacity = 0;
	};

	void setTiles()
	{
		Adjust();
		int i_ = 0;
		tileset = new Tile[capacity];
		for (int j = x; j < w + x; j++)
		{
			for (int i = y; i < h + y; i++)
			{
				tileset[i_] = Tile(j * 64, i * 64, ints[i_]);
				i_++;
			}
		}

		delete[] ints;
	}

	void renderMiniMap(SDL_Renderer* gRenderer, Player* player)
	{
		for (int i = 0; i < capacity; i++)
		{
			SDL_Rect miniGrid = { (tileset[i].mBox.x / 64)*4, (tileset[i].mBox.y / 64)*4, 3, 3 };
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 100, 255);
			SDL_RenderFillRect(gRenderer, &miniGrid);
		}

		if ((player->mCollider.x / 64 >= x && player->mCollider.x / 64 <= x + w) && player->mCollider.y / 64 >= y && player->mCollider.y/64 <= y + h)
		{
			SDL_Rect miniGrid = { (player->mCollider.x/64)*4, (player->mCollider.y/64) * 4, 3, 3 };
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(gRenderer, &miniGrid);
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	}

	void rotate(double angle)
	{
		for (int i = 0; i < capacity; i++)
		{
			tileset[i].mBox.x = tileset[i].mBox.x*cos(angle) - tileset[i].mBox.y*sin(angle);
			tileset[i].mBox.y = tileset[i].mBox.x*sin(angle) + tileset[i].mBox.y*cos(angle);
		}
	}

	void render(SDL_Renderer* gRenderer, SDL_Rect &camera, LTexture& target, double rotation, Player* player)
	{
		for (int i = 0; i < capacity; i++)
		{
			double x1, y1;

			x1 = (tileset[i].mBox.x - player->x)*cos(rotation) - (tileset[i].mBox.y - player->y)*sin(rotation);
			y1 = (tileset[i].mBox.x - player->x)*sin(rotation) + (tileset[i].mBox.y - player->y)*cos(rotation);
			
			x1 += player->x;
			y1 += player->y;
			//SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255);
			//SDL_RenderDrawPoint(gRenderer, x1, y1);
			tileset[i].renderRotation(x1, y1, camera, gRenderer, target, (rotation * 180 / 3.14159));
		/*	SDL_Rect grid = tileset[i].mBox;
			grid.x -= camera.x;
			grid.y -= camera.y;
			SDL_RenderDrawRect(gRenderer, &grid);*/
			
		}
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	}

	void setInts()
	{
		capacity = w * h;
		ints = new int[capacity];
		for (int i = 0; i < capacity; i++)
		{
			ints[i] = 14;
		}
	}

	void Adjust()
	{
		x++;
		y++;
	}

	int x, y;
	int w, h;

	Tile* tileset;
	int* ints;
	int capacity;
};

class Room
{
public:
	Room(SDL_Rect boxes[], int capacity)
	{
		rotation = 0;
		subrooms = new Subroom[capacity];
		width = 0;
		height = 0;
		x = 0;
		y = 0;
		roomCapacity = capacity;


		int tempxmin = 100;
		int tempymin = 100;
		int tempxmax = 0;
		int tempymax = 0;
		for (int i = 0; i < roomCapacity; i++)
		{
			subrooms[i] = Subroom(boxes[i].x, boxes[i].y, boxes[i].w, boxes[i].h);			
			subrooms[i].setInts();
			subrooms[i].setTiles();
			//if larger than current width
			if (boxes[i].x < tempxmin)
			{
				tempxmin = boxes[i].x;
			}
			if (boxes[i].x + boxes[i].w > tempxmax)
			{
				tempxmax = boxes[i].x + boxes[i].w;
			}
			if (boxes[i].y < tempymin)
			{
				tempymin = boxes[i].y;
			}
			if (boxes[i].y + boxes[i].h > tempymax)
				tempymax = boxes[i].y + boxes[y].h;
		}
		x = tempxmin;
		y = tempymin;
		width = tempxmax - tempxmin + 2;
		height = tempymax - tempymin +2;
		ints = new int*[height];
		for (int i = 0; i < height; i++)
		{
			ints[i] = new int[width];
		}

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				ints[y][x] = 0;
			}
		}

		composeMap();
	}

	void rotateAll(double angle)
	{
		rotation += angle;
		std::cout << -(rotation * 180 / 3.14159) << " ";
	}

	void renderWalls(SDL_Renderer* gRenderer, SDL_Rect& camera, LTexture& src, Player* player)
	{
		for (int i = 0; i < wallsCapacity; i++)
		{
			double x1, y1;

			x1 = (walls[i].mBox.x - player->x)*cos(rotation) - (walls[i].mBox.y+32 - player->y)*sin(rotation);
			y1 = (walls[i].mBox.x- player->x)*sin(rotation) + (walls[i].mBox.y+32 - player->y)*cos(rotation);

			x1 += player->x;
			y1 += player->y;
			//SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255);
			//SDL_RenderDrawPoint(gRenderer, x1, y1);
			walls[i].renderRotation(x1, y1, camera, gRenderer, src, (rotation * 180 / 3.14159));
		}
	}

	void composeMap()
	{
		wallsCapacity = 0;
		for (int i = 0; i < roomCapacity; i++)
		{
			int x_ = subrooms[i].x;
			int y_ = subrooms[i].y;
			for (int j = 0; j < subrooms[i].capacity; j++)
			{
				ints[y_][x_] = subrooms[i].tileset[j].getType();
				x_++;
				if (x_ >= subrooms[i].w + subrooms[i].x)
				{
					y_++;
					x_ = subrooms[i].x;
				}
			}
		}

		for (int i = 0; i < roomCapacity; i++)
		{
			int x_ = subrooms[i].x;
			int y_ = subrooms[i].y;
			for (int j = 0; j < subrooms[i].capacity; j++)
			{

				//we need to check the tiles above, below, left and right.
				// as well as diagnals to understand the wall type to place
				//fundamentally we will have several types
				//
				if (ints[y_ + 1][x_] == NULL && ints[y_ + 1][x_ + 1] < 14 && ints[y_ + 1][x_ - 1] < 14)
				{
					ints[y_ + 1][x_] = 1;
					wallsCapacity++;
				}

				if (ints[y_ - 1][x_] == NULL && ints[y_ - 1][x_+1] < 14 && ints[y_ - 1][x_-1] < 14)
				{
					ints[y_ - 1][x_] = 2;
					wallsCapacity++;
				}
				if (ints[y_][x_ + 1] == NULL && ints[y_ + 1][x_ + 1] < 14 && ints[y_ - 1][x_ + 1] < 14)
				{
					ints[y_][x_ + 1] = 3;
					wallsCapacity++;
				}
				if (ints[y_][x_ - 1] == NULL && ints[y_ + 1][x_ - 1] < 14 && ints[y_ - 1][x_ - 1] <14)
				{
					ints[y_][x_ - 1] = 4;
					wallsCapacity++;
				}
				//now we have to do some fun diaganol stuff

				//this is if the diaganol is inside

					//inside


				//top left
				if (ints[y_ - 1][x_ - 1] == NULL) 
				{
					if (ints[y_ - 1][x_] > 13 && ints[y_][x_ - 1] > 13)
					{
						ints[y_ - 1][x_ - 1] = 5;
						wallsCapacity++;
					}
					if (ints[y_ - 1][x_] < 14 && ints[y_][x_ - 1] < 14)
					{
						ints[y_ - 1][x_ - 1] = 6;
					wallsCapacity++;
					}
				}
				//top right
				if (ints[y_ - 1][x_ + 1] == NULL)
				{
					if (ints[y_ - 1][x_] > 13 && ints[y_][x_ + 1] > 13)
					{
						ints[y_ - 1][x_ + 1] = 7;
						wallsCapacity++;
					}
					if (ints[y_ - 1][x_] < 14 && ints[y_][x_ + 1] < 14)
					{
						ints[y_ - 1][x_ + 1] = 8;
						wallsCapacity++;
					}
					
				}
				//bottom left
				if (ints[y_ + 1][x_ - 1] == NULL)
				{
					if (ints[y_ + 1][x_] > 13 && ints[y_][x_ - 1] > 13)
					{	
						ints[y_ + 1][x_ - 1] = 9;
						wallsCapacity++;
					}
					if (ints[y_ + 1][x_] < 14 && ints[y_][x_ - 1] < 14)
					{
						ints[y_ + 1][x_ - 1] = 10;
						wallsCapacity++;
					}
				}
				//bottom right
				if (ints[y_ + 1][x_ + 1] == NULL)
				{
					if (ints[y_ + 1][x_] > 13 && ints[y_][x_ + 1] > 13)
					{
						ints[y_ + 1][x_ + 1] = 11;
						wallsCapacity++;
					}	
					if (ints[y_ + 1][x_] < 14 && ints[y_][x_ + 1] < 14)
					{
						ints[y_ + 1][x_ + 1] = 12;
						wallsCapacity++;
					}
					
				}
				

				x_++;
				if (x_ >= subrooms[i].w + subrooms[i].x)
				{
					y_++;
					x_ = subrooms[i].x;
				}
			}
		}
		walls = new Tile[wallsCapacity]; 
		int counte = 0;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (ints[i][j] > 0 && ints[i][j] < 14)
				{
					walls[counte] = Tile((j) * 64, ((i) * 64)-32, ints[i][j]);
					counte++;
				}
			}
		}
		//deleteInts();
		//printInts();
	}

	void deleteInts()
	{
		for (int i = 0; i < height; i++)
		{
			delete[] ints[i];
		}
		delete[] ints;
	}

	void renderSubRooms(SDL_Renderer* gRenderer, SDL_Rect& camera, LTexture& target, Player* player)
	{
		for (int i = 0; i < roomCapacity; i++)
		{
			subrooms[i].render(gRenderer, camera, target, rotation, player);
			//SDL_RenderDrawLine(gRenderer, lines[i]->x1 - camera.x, lines[i]->y1 - camera.y, lines[i]->x2 - camera.x, lines[i]->y2 - camera.y);
			//lines[i]->print();
		}
	}

	//void renderMiniMap(SDL_Renderer* gRenderer, SDL_Rect& camera, )

	void printInts()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (ints[i][j] > 0 && ints[i][j] < 14)
				{
					std::cout << ints[i][j] << " ";
				}
				else
					std::cout << "_" << " ";
			}
			std::cout << std::endl;
		}
	}

	void renderMiniMap(SDL_Renderer* gRenderer, Player* player)
	{
		for (int i = 0; i < roomCapacity; i++)
		{
			subrooms[i].renderMiniMap(gRenderer, player);
		}
	}

	void render(SDL_Renderer* gRenderer, SDL_Rect& camera, LTexture& target, Player* player)
	{
		SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);
		
		renderSubRooms(gRenderer, camera, target, player);
		//renderWalls(gRenderer, camera, target);
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	}


	double rotation;
	int x, y;
	int width, height;

	Subroom* subrooms;
	int roomCapacity;

	Tile* walls;
	int wallsCapacity;

	int** ints;
};