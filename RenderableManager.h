#ifndef __RenderableManager__
#define __RenderableManager__

class Renderable;
class RPotion;
class Inventory;
#include "SDL.h"
#include "Renderable.h"

class RenderableManager
{
public:
	RenderableManager();
	~RenderableManager();
	
	void renderAll(SDL_Renderer* gRenderer, SDL_Rect& camera, Player& p, Inventory2& inv);

	void addRenderablePotion(int x, int y, int resolution, SDL_Renderer* gRenderer);

	void addRenderableManaPotion(int x, int y, int resolution, SDL_Renderer* gRenderer);


private:

	Renderable* renderQueue[30];
	int maxCapacity;
	int used;

};



#endif
