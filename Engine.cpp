#include "Engine.h"


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
	if ( TTF_Init() == -1 )
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		//success = false;
	}

	gFont = TTF_OpenFont("fonts/lazy.ttf", 45);
	textColor = { 255, 255, 255 };
	if (gFont == NULL) {
		printf("Failed to load the font, SDL_TTF error: %s", TTF_GetError());
	}

	if (!dialogue.loadFromRenderedText("Level: 1", textColor, gRenderer, gFont))
	{
		printf("fucked up with word texture");
		//success = false;
	}

	return success;
}

bool loadMusicMedia(SDL_Renderer* gRenderer)
{
	bool success = true;

	//gMusic = Mix_LoadMUS("fonts/jupiter.wav");

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
	//Mix_PlayMusic(gMusic, -1);
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

void startMapEditor()
{
	loadTextBoxMedia(gRenderer);
	
	Selected selector;
	initSDL();
	Tile* tileSet[TOTAL_TILES + 18];
	int  tileNumbers = 10;
	int cameraX1, cameraY1;
	cameraX1 = (SCREEN_WIDTH / tileNumbers);
	setTiles(tileSet);
	BaseNpc* basenpc[3];
	basenpc[0] = new BaseNpc(400, 400);
	basenpc[1] = new BaseNpc(200, 200);
	basenpc[2] = new BaseNpc(200, 300);
	loadLevelOneMedia(tileSet, gRenderer);
	loadPlayerMedia(gRenderer);
	loadSlimeMedia(gRenderer);
	loadProjectileMedia(gRenderer);

	//loadMapLevelMedia(tileSet, gRenderer);
	
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect largeChat = { 20, 152, 12, 8 };
	SDL_Event e;
	ProjectileManager p;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	int frame = 0;
	SDL_Rect* currentClip; SDL_Color textColor = { 0, 0, 255 };
	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				//quit == true;
			}
			selector.handleEvent(e, tileSet, camera);
		}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		SDL_RenderClear(gRenderer);

		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			tileSet[i]->render(camera, gRenderer);
		}
		p.renderAll(camera, gRenderer, basenpc);

		
		//system("CLS");
		
		//dialogue.loadFromRenderedText("The quic brown fox jumps over the lazy dog", textColor, gRenderer, gFont);
		//dialogue.render(0, 0, currentClip, gRenderer, NULL, 0, flipType);
		SDL_RenderPresent(gRenderer);
	}
}

void levelOne()
{

	initSDL();

	loadTextBoxMedia(gRenderer);

	const int Slimes = 1;
	BaseNpc* basenpc[Slimes];
	//basenpc[0] = new BaseNpc(400, 400);
	//basenpc[1] = new BaseNpc(200, 200);
	//basenpc[2] = new BaseNpc(200, 300);
	basenpc[0] = new BossSlime(500, 100);
	//BossSlime Boss(500, 100);
	//BaseNpc slime1(400, 400);
	//BaseNpc slime2(200, 200);

	Player player;

	Inventory inventory;
	Potion smallPotion(-100, -100, 1);
	Potion largePotion(-100, -100, 2);
	inventory.placeItem(smallPotion);
	inventory.placeItem(largePotion);
	
	Tile* tileSet[TOTAL_TILES+18];
	loadLevelOneMedia(tileSet, gRenderer);
	loadPlayerMedia(gRenderer);
	loadSlimeMedia(gRenderer);
	loadProjectileMedia(gRenderer);
	loadItemMedia(gRenderer);
	SDL_Rect camera = {50,100,   SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_Rect largeChat = { 20, 152, 12, 8 };
	SDL_Event e;

	ProjectileManager p;
	ProjectileManager enemyP;
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
			inventory.handleEvent(e);
		}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		inventory.handleMovement(player);

		SDL_RenderClear(gRenderer);

		for (int w = 0; w < Slimes; w++)
		{
			//basenpc[w]->targetedMove(player, tileSet);
			basenpc[0]->targetedMove(player, tileSet, enemyP);
		}
		//Boss.targetedMove(player, tileSet, enemyP);
		//slime1.targetedMove(player, tileSet);
		//slime2.targetedMove(player, tileSet);

		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			tileSet[i]->render(camera, gRenderer);
		}

		p.renderAll(camera, gRenderer, basenpc);
		//enemyP.renderAllEnemy(camera, gRenderer, player);

		for (int x = 0; x < Slimes; x++)
		{
			basenpc[x]->render(camera, currentClip, gRenderer, NULL, 0, flipType);
			//Boss.render(camera, currentClip, gRenderer, NULL, 0, flipType);
		}
		//slime1.render(camera, currentClip, gRenderer, NULL, 0, flipType);
		//slime2.render(camera, currentClip, gRenderer, NULL, 0, flipType);


		player.move(tileSet, p, camera);
		player.setCamera(camera);
		currentClip = player.getClip();
		inventory.renderItems(camera, gRenderer);
		player.render(camera, currentClip, gRenderer, NULL, 0, flipType, &largeChat);

		if (basenpc[0]->getAlive())// && basenpc[1]->getAlive() && basenpc[2]->getAlive())
		{
			//this means a level was cleared. we should call this after all render loops
			//now the player can level up and we can add more enemies
			player.LevelUp();

			dialogue.loadFromRenderedText("Level: " + std::to_string(player.getLevel()), textColor, gRenderer, gFont);
			for (int w = 0; w < Slimes; w++)
			{
				//delete basenpc[w];
			}

			if (player.getLevel() % 5 == 0 && player.getLevel() > 4)
			{
				//basenpc[0] = new BaseNpc(500, 100);
			}
			else
			{

				basenpc[0] = new BossSlime(500, 100);
				//basenpc[1] = new BaseNpc(200, 200);
				//basenpc[2] = new BaseNpc(200, 300);
			}
		}
		
		//inventory.debugItem(gRenderer);
		
		player.incrementFrames();
		//system("CLS");
		//std::cout << player.getLevel();
		//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//dialogue.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, gRenderer, gFont);
		dialogue.render((SCREEN_WIDTH - dialogue.getWidth())/2, 30, NULL, gRenderer, NULL, 0, flipType);
		SDL_RenderPresent(gRenderer);
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