#ifndef __LTexture__
#define __LTexture__

#include <iostream>
#include <stdint.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_Image.h"


class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont);

	void free();

	void render(int x, int y, SDL_Rect* clip = NULL, SDL_Renderer* gRenderer = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void renderHalf(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void LTexture::renderInventory(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

};

#endif