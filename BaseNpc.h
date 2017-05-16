#pragma once
#include "stdafx.h"
class Player;
#include "LTexture.h"

class BaseNpc
{
public:
	explicit BaseNpc(int x, int y);
	
	void move(Player player, Tile* tiles[]);
	void targetedMove(Player& player, Tile* tiles[]);
	void setMoveDirections(Player& player);
	void dealDamage(int pdamage);

	void render(SDL_Rect& camera, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip);
	bool getAlive();
	int nPosX, nPosY;
	double nVelX, nVelY;
	int frame, clock, v1;

	SDL_Rect mCollider;
	SDL_Rect healthbox;

	double width;


	double getxDirection(Player& player );
	double getyDirection(Player& player );

private:
	int snum = 0;
	double health;
	double maxHealth;
	bool damaged;
	bool dead;
};

void loadLevelOneMobs();
bool loadSlimeMedia(SDL_Renderer* gRenderer);