#pragma once
#include "stdafx.h"
#include <SDL_ttf.h>
#include "Tile.h"
class Selected
{
	//this class will allow the system to store a selection, 
	//as well as a currently selected texture, which we can then
	//apply directly to our screen based on a for looped set * increment
	//most likely this means we need to write to a textFile named
	//the level, as well as specify a level size.
	//we can do X*x and then spawn a row of 0's 
	//the mouse class will monitor it's position as a camera
	//which we will track vs the level sizes grid doing matrix subtraction
	//on a matrix of {M0...Mn1, N0...Nn} : n1 = X, n2 = x;
	//and m(n1) = 
	//or we can just hold the level's top left (x,y)
	//as well as the mouse (x,y) separately.
	//if mouse == (0,0) at spawn if we move mouse down the window (0,-200)
	//then mousepPs = 
	//(origen(0,0) - (0, (-200/scale_size_y((window_height/number_of_grids(10))
	//the reason for this is so we can move out of bounds of the level editor by default
	// we can say that if pos of grid# > X then grids id is 0xFFFFFF
	// otherwise id is NULL, until assigned otherwise
	// as we move the mouse around, it tracks the current grid number, 
	//which is also the levels (-x,-y)+mousePos() the origin should also normally be
	//(0,0) + levels(-x,-y) and that will be where we spawn the levels position
	//in relation to
	//so as we click we assign a value inside the text file where the cursor
	//iterates n rows and n columns down, leading to directly on the id at that
	//digit and changing it to the mouses currently selected id.
	//on each loop through the program we render that grid which is being manipulated
	//on heap/stack and not being read through each loop.
	//when we save we rewrite the rext document.
	//sounds easy lets implement it.

	const int max = 20;
	int m_selected = 1;
	LTexture* m_Available = new LTexture[20];
	int* tileID = new int[20];
	int selectorX = 0; 
	int selectorY = 0;
	SDL_Rect EditorTileClips[5];
	//Tile editorTiles[5];
	bool setTilesGo; 
	int grid[10][10];
	
	
	//to do a selector for map tiles with multiple heights we can do something 
	//that i personally think is really cool
	//so we have a matrix with an {x,y,z} a different layer will spawn it
	//so it is slightly higher up, if we hit q or e, we swivel them around
	//so that  we multiply a {1x1} matrix that is a value for 
	//case e turn things on the {x, y} values only, and is such that
	//x=x*cos(theta)
	/*lets say we look at the tile at location (0,1) at start the cameras
	theta value is at (0*someNumber, -cos(-math.pi())+
	*/

public:
	void handleEvent(SDL_Event& e, Tile* tileSet[], SDL_Rect& camera)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				int x, y;
				SDL_GetMouseState(&x, &y);
				x = (x+camera.x) / 64;
				y = (y+camera.y) / 64;
				std::cout << x << std::endl;
				std::cout << y << std::endl;
				//this will effectively change the map. but not tileset
				grid[x][y] = m_selected;

				//nextt we have to go in the tileset and change the tile
				tileSet[(x) + y*16]->setType(m_selected);
				break;
			}
			

		}
		else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a: camera.x += -23; break;
			case SDLK_d: camera.x += 23;  break;
			case SDLK_w: camera.y += -16;  break;
			case SDLK_s: camera.y +=19; break;
			case SDLK_o: m_selected += 1; break;
			case SDLK_p: m_selected += -1; break;
			case SDLK_l: 
				std::ofstream map("maps/levelone.map");
				for (int i = 0; i < TOTAL_TILES; i++)
				{
					map << tileSet[i]->getType() << " ";
				}
				map.close();
				break;	
			}
		}
	}

	Selected()
	{
		for (int i = 0; i < max; i++)
		{
			tileID[i] = i;
		}

		m_selected = 1;
		
		for (int m = 0; m < 10; m++)
		{
			for (int n = 0; n < 10; n++)
			{
				grid[m][n] = 0;
			}
		}

	}

};