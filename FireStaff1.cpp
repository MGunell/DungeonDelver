#include "FireStaff1.h"

LTexture WeaponSpriteSheet;
SDL_Rect sprites[2];

bool loadWeaponMedia(SDL_Renderer* gRenderer)
{
	bool success = true;

	if (!WeaponSpriteSheet.loadFromFile("images/characters.png", gRenderer))
	{
		printf("failed with weapon sprites");
		success = false;
	}
	else
	{
		sprites[0].x = 28;
		sprites[0].y = 260;
		sprites[0].w = 5;
		sprites[0].h = 19;

		sprites[1].x = 18;
		sprites[1].y = 261;
		sprites[1].w = 5;
		sprites[1].h = 6;
	}

	return success;
}