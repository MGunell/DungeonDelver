#ifndef __BossSlime__
#define __BossSlime__

class Tile;
class Player;
#include "ProjectileManager.h"


class BossSlime : public BaseNpc
{
public:
	BossSlime(int x, int y);
	void targetedMove(Player& player, Tile* tiles[], ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer);
	void shoot(Player& player, ProjectileManager& p);
	void setMoveDirections(Player& player);

	
	
	~BossSlime();

	int damage;
	int shootingFrames;
};

#endif