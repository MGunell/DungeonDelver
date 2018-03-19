#pragma once
#include <iostream>
#include <stdint.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_Image.h"

class LPolygon {
public:
	LPolygon();
	~LPolygon();

private:
	int vertices;
	//int x[vertices];
	//int *y[]
};