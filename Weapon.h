#pragma once
#include "LTexture.h"

class Weapon
{
public:
	Weapon(int damage1, int range1, int speed1);

	int damage;
	int range;
	int speed;
	void renderProjectile(int x, int y);
	void renderProjectileStep2(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip);
private:
};