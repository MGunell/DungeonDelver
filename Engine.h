#pragma once
#include "stdafx.h"
#include "BaseNpc.h"


bool init();
bool loadMedia();

void startgame();
void levelOne();
void initSDL();

bool checkCollision(SDL_Rect a, SDL_Rect b);
bool touchesWall(SDL_Rect box, Tile* tiles[]);
bool touchesPlayer(SDL_Rect box, Player player);