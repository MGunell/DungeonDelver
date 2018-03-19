#pragma once
//#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

class LevelMap
{
public: 

	LevelMap(int x, int y)
	{

		tileSize = { 0, 0, 32, 32 };

		rowsMax = x;
		columnsMax = y;
		Level = new int*[rowsMax];
		for (int i = 0; i < rowsMax; i++)
		{
			Level[i] = new int[columnsMax];
			for (int j = 0; j < columnsMax; j++)
			{
				Level[i][j] = 0;
			}
		}
	};


	//LevelMap& operator=(LevelMap& target)
	//{
	//	rowsMax = target.rowsMax;
	//	columnsMax = target.columnsMax;
	//	Level = new int*[rowsMax];
	//	for (int i = 0; i < target.rowsMax; i++)
	//	{
	//		Level[i] = new int[columnsMax];
	//		for (int j = 0; j < target.columnsMax; j++)
	//		{
	//			Level[i][j] = target.Level[i][j];
	//		}
	//	}
	//	return *this;
	//}

	void print()
{
		std::cout << rowsMax << ", " << columnsMax << '\n';
		for (int i = 0; i < rowsMax; i++)
		{
			for (int j = 0; j < columnsMax; j++)
			{
				std::cout << Level[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void randomizeMapGen()
	{
		std::srand(std::time(nullptr));

		//first pick a starting direction, (1,0) = from right, (-1,0) = from left, (0,1) from top (0,-1) from bottom
		int x = std::rand() % 3; 
		int y = std::rand() % 3;
		x++; y++;
			
		Level[x][y] = 1;
		std::srand(std::time(nullptr));
		int moves = (std::rand() % 4) + 3;
		while (moves > 0)
		{
			int choice = std::rand() % 3;
			std::cout << choice << '\n';
			switch (choice)
			{
			case 0:
				if (x + 1 < columnsMax && Level[x + 1][y] != 1 )
				{
					Level[x + 1][y] = 1;
					x++;
					break;
				}
			case 1:
				if (x > 0 && Level[x - 1][y] != 1)
				{
					Level[x - 1][y] = 1;
					x--;
					break;
				}
			case 2:
				if (y + 1 < rowsMax && Level[x][y + 1] != 1 )
				{
					Level[x][y + 1] = 1;
					y++;
					break;
				}
			case 3:
				if (y > 0 && Level[x][y - 1] != 1)
				{
					Level[x][y - 1] = 1;
					y--;
					break;
				}
			}

			moves--;
		}
	}

	void setColor(SDL_Renderer* gRenderer, int selection)
	{
		switch (selection)
		{
		case 0:
			SDL_SetRenderDrawColor(gRenderer, 0, 100, 0, 255);
			break;
		case 1:
			SDL_SetRenderDrawColor(gRenderer, 100, 0, 0, 255);
			break;
		case 2:
			SDL_SetRenderDrawColor(gRenderer, 50, 200, 0, 255);
			break;
		case 3:
			SDL_SetRenderDrawColor(gRenderer, 200, 50, 50, 255);
			break;
		case 4:
			SDL_SetRenderDrawColor(gRenderer, 50, 100, 0, 255);
			break;
		case 5:
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			break;
		case 6:
			SDL_SetRenderDrawColor(gRenderer, 100, 100, 0, 255);
			break;
		case 7:
			SDL_SetRenderDrawColor(gRenderer, 0, 100, 100, 255);
			break;
		case 8:
			SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);
			break;
		case 9:
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 100, 255);
			break;
		}
	}

	void render(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		SDL_RenderClear(gRenderer);
		tileSize.x = 0 - camera.x;
		tileSize.y = 0 - camera.y;
		for (int i = 0; i < rowsMax; i++)
		{
			
			for (int j = 0; j < columnsMax; j++)
			{
				
				setColor(gRenderer, Level[i][j]);
				if (Level[i][j] == 9 || Level[i][j] == 8)
				{
					SDL_RenderFillRect(gRenderer, &tileSize);
				}
				SDL_RenderDrawRect(gRenderer, &tileSize);

				
				tileSize.x += tileSize.w;
			}
			tileSize.y += tileSize.h;
			
			tileSize.x = 0 - camera.x;
		}
		//tileSize.x += camera.x;
		//tileSize.y += camera.y;
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderPresent(gRenderer);
	}

	int getVertices(int tilex, int tiley)
	{
		int attaches = 0;

		for (int i = 0; i < 4; i++)
		{
			if (tilex == 0)
			{
			
					if (Level[tilex][tiley + 1] == 0) attaches++;
					if (Level[tilex+1][tiley] == 0) attaches++;
				return attaches+1;
			}
			else if (tiley == 0) {
				if (Level[tilex][tiley + 1] == 0) attaches++;
				if (Level[tilex + 1][tiley] == 0) attaches++;
				return attaches + 1;
			}
			else
			switch (i)
			{
			case 0:
				if (Level[tilex][tiley + 1] == 1) attaches++;
				break;
			case 1:
				if (Level[tilex][tiley - 1] == 1) attaches++;
				break;
			case 2:
				if (Level[tilex + 1][tiley] == 1) attaches++;
				break;
			case 3:
				if (Level[tilex-1][tiley] == 1) attaches++;
			}
		}
		return attaches;
	}

	void cull(LevelMap& src)
	{
		for (int i = 0; i < rowsMax - 1; i++)
		{
			for (int j = columnsMax-1; j > 0; j--)
			{
				if ( src.getVertices(i, j) < 2)
					src.Level[i][j] = 0;
			}
		}
	}


	int getWall(int src)
	{
		if (src == 1) return 1;
		return 0;
	}

	LevelMap& getGround(LevelMap& src)
	{
		LevelMap temp(src.rowsMax, src.columnsMax);
		temp = src;
		int count = 0;
		for (int i = 0; i < src.rowsMax; i++)
		{
			for (int j = 0; j < src.columnsMax; j++)
			{
				if (Level[i][j] == 1) count++;
				else
				count--;
			}
		}
		if (count > 0) return temp;
		else return temp.inverse(src);
	}

	LevelMap& inverse(LevelMap& src)
	{
		LevelMap temp(src.rowsMax, src.columnsMax);
		for (int i = 0; i < src.rowsMax; i++)
		{
			for (int j = 0; j < columnsMax; j++)
			{
				if (src.Level[i][j] == 1) temp.Level[i][j] = 0;
				else temp.Level[i][j] = 1;
			}
		}

		return temp;
	}

	LevelMap& makeWallMap( const LevelMap& src) {
		LevelMap temp((src.rowsMax-2)/5, (src.columnsMax-2)/5);

		for (int i = 0; i < temp.rowsMax; i++)
		{
			for (int j = 0; j < temp.columnsMax; j++)
			{
				temp.Level[i][j] = getWall(src.Level[(i*5)+1][5*j+1]);
			}
		}
		return temp;
	}

	LevelMap& build()
	{
		LevelMap* temp;
		temp = new LevelMap(rowsMax * 5, columnsMax * 5);
		for (int i = 0; i < rowsMax; i++)
		{
			for (int j = 0; j < columnsMax; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					for (int l = 0; l < 5; l++)
					{
						if (k == 2 && l == 2)
						{
							temp->Level[(i * 5) + k][(j * 5) + l] = 9;
						}
						//else if (k == 0 || k == 4 || l == 0 || l == 4)
						//{
							//temp->Level[(i * 5) + k][(j * 5) + l] = 8;
						//}
						else
						temp->Level[(i * 5) + k][(j * 5) + l] = Level[i][j];
					}

				}

			}

		}
		return *temp;
	}

	LevelMap& addBorders()
	{
		LevelMap temp(rowsMax + 2, columnsMax + 2);
		for (int i = 0; i < temp.rowsMax; i++)
		{
			for (int j = 0; j < temp.columnsMax; j++)
			{
				if (j == 0 || i == 0 || i == temp.rowsMax - 1|| j == temp.columnsMax - 1)
				{
					temp.Level[i][j] = 8;
				}
				else
				{
					temp.Level[i][j] = Level[i-1][j-1];
				}
			}
		}
		return temp;
	}


		int rowsMax, columnsMax;
		int** Level;
		SDL_Rect tileSize;

};



void makeTiles()
{

}