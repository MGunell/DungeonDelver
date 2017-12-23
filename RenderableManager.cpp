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

void RenderableManager::renderAll(SDL_Renderer* gRenderer, SDL_Rect& camera, Player& p, Inventory2& inv)
{
	for (int i = 0; i < used; i++)
	{
		if (renderQueue[i]->getAlive())
		{
			renderQueue[i]->waveMove();
			renderQueue[i]->render(gRenderer, camera);

			if (PickUp(*renderQueue[i], p))
			{
				renderQueue[i]->placeItem(inv, gRenderer);
				renderQueue[i]->lifetime = 0;
			}
		}

		else
		{
			if (used > 1 && i < used-1)
			{
				renderQueue[i] = renderQueue[used - 1];
			}
			used--;
		}
	}
}

void RenderableManager::addRenderablePotion(int x, int y, int resolution, SDL_Renderer* gRenderer)
{
	renderQueue[used] = new RPotion(x, y, resolution, 0, gRenderer);
	used++;
}

void RenderableManager::addRenderableManaPotion(int x, int y, int resolution, SDL_Renderer* gRenderer)
{
	renderQueue[used] = new RPotion(x, y, resolution, 1, gRenderer);
	used++;
}