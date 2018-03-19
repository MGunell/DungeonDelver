#ifndef __RenderableManager__
#define __RenderableManager__

class Renderable;
class RPotion;
class Inventory;
class Inventory3;
#include "SDL.h"
#include "Renderable.h"

class RenderableManager
{
public:
	RenderableManager();
	~RenderableManager();
	
	void renderAll(SDL_Renderer* gRenderer, SDL_Rect& camera, Player* p, Inventory3* inv);

	void renderAll(SDL_Renderer* gRenderer, Inventory3* inv);
	void addRenderable(Renderable* target);

	void addRenderableManaPotion(int x, int y, int resolution, SDL_Renderer* gRenderer);


private:

	Renderable* renderQueue[30];
	int maxCapacity;
	int used;

};



#endif
