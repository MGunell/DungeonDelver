#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

SDL_Renderer* gRenderer = NULL;
SDL_Window* window = NULL;
LTexture dialogue;
TTF_Font *gFont;

bool loadTextBoxMedia(SDL_Renderer* gRenderer)
{
	bool success = true;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("sdlimag failure");
		success = false;
	}

	//initialize sdl ttf
	if (TTF_Init() == -1)
	{
		printf("failed with sdl init dude");
		success = false;
	}

	gFont = TTF_OpenFont("fonts/lazy.ttf", 28);
	SDL_Color textColor = { 0, 0, 255 };
	if (!dialogue.loadFromRenderedText("The quic brown fox jumps over the lazy dog", textColor, gRenderer, gFont))
	{
		printf("fucked up");
		success = false;
	}

	return success;
}

bool loadMusicMedia(SDL_Renderer* gRenderer)
{
	bool success = true;

	gMusic = Mix_LoadMUS("fonts/jupiter.wav");

	return success;
}

void initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
	{
		printf("SDL could not initialize");
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else
	{
		window = SDL_CreateWindow("My first sdl window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window failed to load");
		}
		else
		{
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		}
	}
}
bool firstscript = true;
void startgame()
{
	
	
	initSDL();
	printf("we looped");
	loadTextBoxMedia(gRenderer);
	loadMusicMedia(gRenderer);
	printf("we looped");
	int frame = 0;
	SDL_Rect RECT;
	RECT.x = 0;
	RECT.y = 0;
	RECT.w = 50;
	RECT.h = 50;
	printf("we looped");
	SDL_Rect camera = { 0,0,   SCREEN_WIDTH,SCREEN_HEIGHT };
	Mix_PlayMusic(gMusic, -1);
	while (firstscript == true)
	{
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		{
			
			SDL_RenderClear(gRenderer);
			 
			dialogue.render(0, 0, NULL, gRenderer);
			
			SDL_RenderPresent(gRenderer);
			
		}
	}
}

void levelOne()
{ 
	BaseNpc slime1(400, 400);
	Player player;
	initSDL();
	Tile* tileSet[TOTAL_TILES+18];
	loadLevelOneMedia(tileSet, gRenderer);
	loadPlayerMedia(gRenderer);
	loadSlimeMedia(gRenderer);
	loadProjectileMedia(gRenderer);
	SDL_Rect camera = {50,100,   SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_Rect largeChat = { 20, 152, 12, 8 };
	SDL_Event e;
	ProjectileManager p;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	int frame = 0;
	SDL_Rect* currentClip;
	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				//quit == true;
			}
			player.handleEvent(e);
		}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		player.move(tileSet, p, camera);
		player.setCamera(camera);

		slime1.targetedMove(player, tileSet);

		SDL_RenderClear(gRenderer);

		currentClip = player.getClip();


		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			tileSet[i]->render(camera, gRenderer);
		}
		p.renderAll(camera, gRenderer, slime1);
		slime1.render(camera, currentClip, gRenderer, NULL, 0, flipType);
		player.render(camera, currentClip, gRenderer, NULL, 0, flipType, &largeChat);
		

		SDL_RenderPresent(gRenderer);
		player.incrementFrames();
	}
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
	//go through the tiles
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		if ((tiles[i]->getType() >= 3) && (tiles[i]->getType() <= 11))
		{
			//check collision box
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}
	return false;
}

bool touchesPlayer(SDL_Rect box, Player player)
{
	if (checkCollision(box, player.getBox()))
	{
		return true;
	}
	return false;
}