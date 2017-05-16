#include "Slime.h"



LTexture gSpriteSheetTexture2;

bool loadSlimeMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	if (!gSpriteSheetTexture2.loadFromFile("images/characters.png", gRenderer))
	{
		printf("couldnt load slime stuff");
	}
	else
	{
		currentSprite.x = 126;
		currentSprite.y = 167;
		currentSprite.h = 25;
		currentSprite.w = 32;
	}

	return success;
}

