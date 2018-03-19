#include "RenderableManager.h"
#include "RPotion.h"
#include "InventoryRedux.h"

RenderableManager::RenderableManager()
{
	maxCapacity = 30;
	used = 0;
}

RenderableManager::~RenderableManager()
{
}

void RenderableManager::renderAll(SDL_Renderer* gRenderer, SDL_Rect& camera, Player* p, Inventory3* inv)
{
	for (int i = 0; i < used; i++)
	{
		if (renderQueue[i]->getAlive())
		{
			renderQueue[i]->waveMove();
			renderQueue[i]->render(gRenderer, camera);

			if (PickUp(*renderQueue[i], *p))
			{

				renderQueue[i]->lifetime = 0;
				renderQueue[i]->placeItem(inv);
			}
		}
		else
		{
			if (used > 1 && i < used-1)
			{
				delete renderQueue[i];
				renderQueue[i] = renderQueue[used - 1];
			}
			used--;
		}
	}
}

void RenderableManager::renderAll(SDL_Renderer* gRenderer, Inventory3* inv)
{
	SDL_Rect camera = { 0, 0, 1200, 900 };
	for (int i = 0; i < used; i++)
	{
		if (renderQueue[i]->getAlive())
		{
			renderQueue[i]->waveMove();
			renderQueue[i]->render(gRenderer, camera);
		}
		else
		{
			renderQueue[i]->placeItem(inv);
			if (used > 1 && i < used - 1)
			{
				renderQueue[i] = renderQueue[used - 1];
			}
			used--;
		}
	}
}

void RenderableManager::addRenderable(Renderable* target)
{
	renderQueue[used] = target;
	used++;
}

void RenderableManager::addRenderableManaPotion(int x, int y, int resolution, SDL_Renderer* gRenderer)
{
	renderQueue[used] = new RPotion(x, y, resolution, 1, gRenderer);
	used++;
}