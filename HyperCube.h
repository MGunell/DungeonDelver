#ifndef __hypercube__
#define __hypercube__

class Tile;
class Player;
#include "ProjectileManager.h"

class HyperCube : public BaseNpc
{
public:
	HyperCube(int x, int y);
	void targetedMove(Player& player, Room* room, ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer);
	void shoot(Player& player, ProjectileManager& p);
	void setMoveDirections(Player& player);
	void render(SDL_Rect& camera, SDL_Renderer* gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip);
private:
	int damage;
	int shootingFrames;
};

//static SDL_Rect cubeSprites[27];
//static LTexture gCubeTexture;
//bool loadCubeMedia(SDL_Renderer* gRenderer);
#endif
