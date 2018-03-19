#include "Engine.h"
#include "InventoryRedux.h"
#include "HyperCube.h"
#include "Equipment_Inventory.h"
#include <math.h>
#include "Weapon.h"
#include "Bow.h"
#include "Sword.h"
#include "RPotion.h"
#include "Level_Creation.h"
#include "Room.h"
#include "EnemyManager.h"
#include "LevelGenerator.h"
#include "Level.h"
#include "Enemy.h"
#include <time.h>
#include "Core.h"

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

	textColor = { 0, 0, 0 };
	gFont = TTF_OpenFont("fonts/lazy.ttf", 90);
	if (!endMessage.loadFromRenderedText("You Lost", textColor, gRenderer, gFont))
	{
		printf("end message failed to load");
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
			gRenderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_PRESENTVSYNC | SDL_SWSURFACE);
		}
	}

	loadItemMedia(gRenderer);
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
	Tile* mutableTile[11];
	int padding = 10;
	int tileS = 128;
	int gOff = 0;
	for (int i = 0; i < 11; i++)
	{
		mutableTile[i] = new Tile{ (SCREEN_WIDTH/2 - 128 + padding * i + tileS * i), 11, i };
	}
	//Tile mutableTile = { 0, 11, selector.m_selected };
	int  tileNumbers = 10;
	//std::string levelname;
	//std::cin >> levelname;
	loadLevelOneMedia(tileSet, gRenderer, "maps/startTown.map");
	int gX, gY;
	
	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	
	SDL_Event e;
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
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_q: 
					gOff += tileS + padding;
					break;
				case SDLK_e:
					gOff -= tileS + padding;
				}
			}
			selector.handleEvent(e, tileSet, camera);
		}
		SDL_GetMouseState(&gX, &gY);
		gX = (gX + camera.x) / 128;
		gY = (gY + camera.y) / 128;
		SDL_Rect tileBox = { (gX * 128) - camera.x , (gY * 128) - camera.y, 128, 128 };
		SDL_Rect tileBox1 = { SCREEN_WIDTH / 2 - 133, 6, 138, 138 };
		SDL_Rect UIBox = { 0, 0, SCREEN_WIDTH, 150 };

		for (int j = 0; j < 11; j++)
		{
			mutableTile[j]->mBox.x = (SCREEN_WIDTH / 2 - 128 + padding * j + tileS * j) + camera.x + gOff;
			mutableTile[j]->mBox.y = 11 + camera.y;
		}
		//mutableTile[i] = {SCREEN_WIDTH / 2 - 128 + camera.x, 11 + camera.y, selector.m_selected };
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		SDL_RenderClear(gRenderer);
		gTileTexture.renderHalf(0, 0, &gLevelOneClips[selector.m_selected], gRenderer);

		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//tileSet[i]->render(camera, gRenderer);
		}
		SDL_RenderDrawRect(gRenderer, &tileBox);
		SDL_SetRenderDrawColor(gRenderer, 0x128, 0x64, 0x156, 255);
		SDL_RenderFillRect(gRenderer, &UIBox);
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

		SDL_RenderFillRect(gRenderer, &tileBox1);
		for (int x = 0; x < 11; x++)
		//mutableTile[x]->render(camera, gRenderer);
		


		//gTileTexture.renderHalf(0, 0, &gLevelOneClips[selector.m_selected], gRenderer);

		
		//system("CLS");
		
		//dialogue.loadFromRenderedText("The quic brown fox jumps over the lazy dog", textColor, gRenderer, gFont);
		//dialogue.render(0, 0, currentClip, gRenderer, NULL, 0, flipType);
		SDL_RenderPresent(gRenderer);
	}
}

/*{
	template <typename T>
	class vec3d<T>
	{
	public:

		vec3d();
		vec3d(T x, T y, T z) : x(x), y(y), z(z) {}
		vec3d(const vec3d& vect)
		{
			x = vect.x;
			y = vect.y;
			z = vect.z;
		}

		T x, y, z;

		vec3d& operator=(const vec3d &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}
		T operator*(const vec3d &rhs)
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}
		T LenSq() const {
			return x * x + y * y + z * z;
		}
		T Len() const { return sqrt(LenSq() }
	};

	template <typename T>
	class Mat3
	{
	public:
		Mat3 & operator*=(T rhs)
		{

		}
		Mat3 & operator*(T rhs) const
		{
			Mat3 result = *this;
			return result *= rhs;
		}
		Mat3 operator*(const Mat3& rhs) const
		{
			Mat3 result;
			for (size_t j = 0; j < 3; j++)
			{
				for (size_t k = 0; k < 3; k++)
				{
					T sum = (T)0.0;
					for (size_t i = 0; i < 3; i++)
					{
						sum += elements[j][i] * rhs.elements[i][k];
					}
					result.elements[j][k] = sum;
				}
			}
			return result;
		}
		static Mat3 Identity()
		{
			return {
				(T)1.0, (T)0.0, (T)0.0,
				(T)0.0, (T)1.0, (T)0.0,
				(T)0.0, (T)0.0, (T)1.0
			};
		}
		static Mat3 scaling(T factor)
		{
			return {
				factor, (T)0.0, (T)0.0,
				(T)0.0, factor, (T)0.0,
				(T)0.0, (T)0.0, factor
			};
		}
	public:
		T elements[3][3];
	};

	template <typename T>
	class _3dSpace
	{
	public:
		_3dSpace()
			:
			xFactor(float(SCREEN_WIDTH) / 2.0f),
			yFactor(float(SCREEN_HEIGHT) / 2.0f)
		{}
		vec3d<T>& Transform(vec3d<T>& v) const
		{
			v.x = (v.x + 1.0f) * xFactor;
			v.y = (v.y + 1.0f) * yFactor;
			return v;
		}
		vec3d<T> getTransformed(const vec3d<T>& v) const
		{
			return Transform(vec3d(v));
		}
	private:
		float xFactor;
		float yFactor;

	};

	template <typename T>
	vec3d operator*(const vec3d<T>& lhs, const mat3d<T>& rhs)
	{
		return {
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0],
		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1],
		lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2]
		};
	}

	void loadLevelMesh()
	{






	};

	void matrixMult(vec3d matrix)
	{

	}
}*/

void polygon3D()
{
	initSDL();

}

void levelOn11e()
{
	initSDL();
	Inventory3 newInv2((SCREEN_WIDTH - (15 * (64 + 5)))/2, SCREEN_HEIGHT - 100, 15, 1);
	Inventory3 newInv( 100, 200, 4, 5);
	LTexture boxSprite;
	boxSprite.loadFromFile("images/boxSprite.png", gRenderer);
	newInv.setBoxTexture(&boxSprite);
	newInv2.setBoxTexture(&boxSprite);
	Player player;
	player.hotbar = new Inventory3((SCREEN_WIDTH - (15 * (64 + 5))) / 2, SCREEN_HEIGHT - 100, 15, 1);
	player.boxSprite.loadFromFile("images.boxSprite.png", gRenderer);
	player.hotbar->setBoxTexture(&boxSprite);
	Bow bow1(100, 100, 1, 0, gRenderer, 0, 10, 16);
	Bow bow2(200, 100, 1, 1, gRenderer, 0, 10, 16);
	Bow bow3(300, 100, 1, 2, gRenderer, 0, 10, 16);
	RPotion smallPotion( 300, 100, 25, 0, gRenderer);
	RenderableManager r;
	r.addRenderable(&bow1);
	r.addRenderable(&bow2);
	r.addRenderable(&smallPotion);
	SDL_Rect camera = { 0, 0, 1200, 900 };
	
	int mx, my;
	int mmy, mmx;
	bool clicking = true;
	SDL_Event e;
	while (true)
	{
		SDL_GetMouseState(&mx, &my);
		SDL_GetRelativeMouseState(&mmx, &mmy);
		mx += mmx*2;
		my += mmy*2;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				//quit == true;
			}
			if (clicking)
			{
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_o:
						newInv.addItem(&bow1);
						break;
					case SDLK_i:
						newInv.addItem(&bow2);
						break;
					case SDLK_k:
						newInv.addItem(&smallPotion);
						break;
					case SDLK_l:
						clicking = false;
						break;
					}
				}

				if (e.wheel.y == 1)
				{
					if (newInv.selectedBox < newInv.capacity - 1)
						newInv.selectedBox += 1;
				}
				if (e.wheel.y == -1)
				{
					if (newInv.selectedBox > 0)
						newInv.selectedBox -= 1;
				}
			}
			else
			{
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_o:
						newInv2.addItem(&bow1);
						break;
					case SDLK_i:
						newInv2.addItem(&bow2);
						break;
					case SDLK_k:
						newInv2.addItem(&smallPotion);
						break;
					case SDLK_l:
						clicking = true;
						break;
					}
				}
				if (e.wheel.y == 1)
				{
					if (newInv2.selectedBox < newInv2.capacity - 1)
						newInv2.selectedBox += 1;
				}
				if (e.wheel.y == -1)
				{
					if (newInv2.selectedBox > 0)
						newInv2.selectedBox -= 1;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
			{
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					newInv.grabIitem(newInv.getBoxCollision());
					std::cout << newInv.getBoxCollision();
					break;
				case SDL_BUTTON_RIGHT:
					break;
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP && e.key.repeat == 0)
			{
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					newInv.releaseItem();

					break;
				case SDL_BUTTON_RIGHT:
					break;
				}
			}
			
		}

		SDL_RenderClear(gRenderer);
		
		//newInv.render(gRenderer, mx, my);
		//newInv2.render(gRenderer, mx, my);
		player.render(camera, 0, gRenderer, 0, 0, SDL_FLIP_NONE, 0);
		r.renderAll(gRenderer, player.hotbar);

		SDL_RenderPresent(gRenderer);
	}
}

void le567velOne()
{
	initSDL();
	SDL_Rect rooms[4];
	LTexture src;
	src.loadFromFile("images/tiles.png", gRenderer);
	rooms[0].x = 10;
	rooms[0].y = 0;
	rooms[0].w = 20;
	rooms[0].h = 10;

	rooms[1].x = 20;
	rooms[1].y = 10;
	rooms[1].w = 20;
	rooms[1].h = 6;

	rooms[2].x = 30;
	rooms[2].y = 16;
	rooms[2].w = 31;
	rooms[2].h = 30;

	rooms[3].x = 00;
	rooms[3].y = 46;
	rooms[3].w = 32;
	rooms[3].h = 2;
	Room room1(rooms, 4);
	if (!gTileTexture.loadFromFile("images/tiles.png", gRenderer))
		std::cout << "problem";
	
	setTiles_();
	//std::cout << room1.wallsCapacity << std::endl;
	for (int i = 0; i < room1.wallsCapacity; i++)
	{
		std::cout << room1.walls[i].getType() << std::endl;
	}

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Event e;
	
	
	//room1.printLines(gRenderer, camera);
	//std::cin.get();
	while (true)
	{

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_a:
					camera.x -= 150;
					break;
				case SDLK_d:
					camera.x += 150;
					break;
				case SDLK_w:
					camera.y -= 150;
					break;
				case SDLK_s:
					camera.y += 150;
					break;
				}
			}
		}

		SDL_RenderClear(gRenderer);

		//room1.render(gRenderer, camera, src);

	//	gTileTexture.renderHalf(25 - camera.x, 25 - camera.y, &gLevelOneClips[2], gRenderer);
		SDL_RenderPresent(gRenderer);
	}
}
void levelOn1e()
{
	SDL_Rect camera = { 0, 0, 600, 600 };
	SDL_Event e;
	LevelMap map(5, 5);
	LevelMap map1(5, 5);
	Tile* tiles[27 * 27];
	//for (int i = 0; )
	map.randomizeMapGen();
	map = map.build();
	map = map.addBorders();
	map.print();
    map1 = map.makeWallMap(map);
	//map1 = map1.getGround(map1);
	//map1.cull(map1);
	map1.print();

	initSDL();

	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_a:
					camera.x -= 150;
					break;
				case SDLK_d:
					camera.x += 150;
					break;
				case SDLK_w:
					camera.y -= 150;
					break;
				case SDLK_s:
					camera.y += 150;
					break;
				}
			}
		}


		




		map.render(gRenderer, camera);
		
	}

}

void levelOne()
{

	int cLevel(0);
	time_t timer;
	double seconds;
	time_t timer2;
	Inventory inventory;
	initSDL();
	loadPotionMedia(gRenderer);
	if (!gCubeTexture1.loadFromFile("images/hypercube.png", gRenderer))
	{
		printf("couldnt load slime stuff");
		
	}
	else
	{
		cubeSprites[0].x = 0;
		cubeSprites[0].y = 0;
		cubeSprites[0].h = 32;
		cubeSprites[0].w = 32;

		cubeSprites[1].x = 32;
		cubeSprites[1].y = 0;
		cubeSprites[1].h = 32;
		cubeSprites[1].w = 32;

		cubeSprites[2].x = 64;
		cubeSprites[2].y = 0;
		cubeSprites[2].h = 32;
		cubeSprites[2].w = 32;

		cubeSprites[3].x = 96;
		cubeSprites[3].y = 0;
		cubeSprites[3].h = 32;
		cubeSprites[3].w = 32;

		cubeSprites[4].x = 128;
		cubeSprites[4].y = 0;
		cubeSprites[4].h = 32;
		cubeSprites[4].w = 32;

		cubeSprites[5].x = 160;
		cubeSprites[5].y = 0;
		cubeSprites[5].h = 32;
		cubeSprites[5].w = 32;

		cubeSprites[6].x = 192;
		cubeSprites[6].y = 0;
		cubeSprites[6].h = 32;
		cubeSprites[6].w = 32;

		cubeSprites[7].x = 224;
		cubeSprites[7].y = 0;
		cubeSprites[7].h = 32;
		cubeSprites[7].w = 32;

		cubeSprites[8].x = 256;
		cubeSprites[8].y = 0;
		cubeSprites[8].h = 32;
		cubeSprites[8].w = 32;

		cubeSprites[9].x = 0;
		cubeSprites[9].y = 32;
		cubeSprites[9].h = 32;
		cubeSprites[9].w = 32;

		cubeSprites[10].x = 32;
		cubeSprites[10].y = 32;
		cubeSprites[10].h = 32;
		cubeSprites[10].w = 32;

		cubeSprites[11].x = 64;
		cubeSprites[11].y = 32;
		cubeSprites[11].h = 32;
		cubeSprites[11].w = 32;

		cubeSprites[12].x = 96;
		cubeSprites[12].y = 32;
		cubeSprites[12].h = 32;
		cubeSprites[12].w = 32;

		cubeSprites[13].x = 128;
		cubeSprites[13].y = 32;
		cubeSprites[13].h = 32;
		cubeSprites[13].w = 32;

		cubeSprites[14].x = 160;
		cubeSprites[14].y = 32;
		cubeSprites[14].h = 32;
		cubeSprites[14].w = 32;

		cubeSprites[15].x = 192;
		cubeSprites[15].y = 32;
		cubeSprites[15].h = 32;
		cubeSprites[15].w = 32;

		cubeSprites[16].x = 224;
		cubeSprites[16].y = 32;
		cubeSprites[16].h = 32;
		cubeSprites[16].w = 32;

		cubeSprites[17].x = 256;
		cubeSprites[17].y = 32;
		cubeSprites[17].h = 32;
		cubeSprites[17].w = 32;

		cubeSprites[18].x = 0;
		cubeSprites[18].y = 64;
		cubeSprites[18].h = 32;
		cubeSprites[18].w = 32;

		cubeSprites[19].x = 32;
		cubeSprites[19].y = 64;
		cubeSprites[19].h = 32;
		cubeSprites[19].w = 32;

		cubeSprites[20].x = 64;
		cubeSprites[20].y = 64;
		cubeSprites[20].h = 32;
		cubeSprites[20].w = 32;

		cubeSprites[21].x = 96;
		cubeSprites[21].y = 64;
		cubeSprites[21].h = 32;
		cubeSprites[21].w = 32;

		cubeSprites[22].x = 128;
		cubeSprites[22].y = 64;
		cubeSprites[22].h = 32;
		cubeSprites[22].w = 32;

		cubeSprites[23].x = 160;
		cubeSprites[23].y = 64;
		cubeSprites[23].h = 32;
		cubeSprites[23].w = 32;

		cubeSprites[24].x = 192;
		cubeSprites[24].y = 64;
		cubeSprites[24].h = 32;
		cubeSprites[24].w = 32;

		cubeSprites[25].x = 224;
		cubeSprites[25].y = 64;
		cubeSprites[25].h = 32;
		cubeSprites[25].w = 32;

		cubeSprites[26].x = 256;
		cubeSprites[26].y = 64;
		cubeSprites[26].h = 32;
		cubeSprites[26].w = 32;

	}
	
	LTexture CubeTexture;
	CubeTexture.loadFromFile("images/hypercube.png", gRenderer);

	loadTextBoxMedia(gRenderer);
	LTexture boxsprite;
	SDL_Rect something = { 100, 100, 25, 25 };
		LTexture ogre;
		SDL_Color textColor1 = { 255, 255, 255 };
		TTF_Font* gFont2 = TTF_OpenFont("fonts/lazy.ttf", 15);
		ogre.loadFromRenderedText("Ogre", textColor1, gRenderer, gFont2);
		ogre.render(100, 100, &something, gRenderer);

	const int Slimes = 5;
	BaseNpc* basenpc[Slimes];
	//basenpc[0] = new BaseNpc(400, 400);
	//basenpc[1] = new BaseNpc(200, 200);
	basenpc[0] = new BaseNpc(1900, 700);
	basenpc[1] = new BaseNpc(1700, 800);
	basenpc[2] = new BaseNpc(1800, 700);
	basenpc[3] = new BaseNpc(1900, 1400);
	basenpc[4] = new BaseNpc(2300, 1400);

	//BossSlime Boss(500, 100);
	//BaseNpc slime1(400, 400);
	//BaseNpc slime2(200, 200);
	Player player;
	boxsprite.loadFromFile("images/boxSprite.png", gRenderer);
	player.hotbar = new Inventory3(SCREEN_WIDTH+25, 100, 5, 6);
	player.hotbar->setBoxTexture(&boxsprite);
	EnemyManager eM;
	LevelGenerator LG;
	//eM.insertEnemy(basenpc[0]);
	//eM.insertEnemy(basenpc[1]);
	//eM.insertEnemy(basenpc[2]);
	//eM.insertEnemy(basenpc[3]);
	//eM.insertEnemy(basenpc[4]);
	RenderableManager r;
	// Inventory2 inventory2(gRenderer);
	//r.addRenderablePotion(200, 300, 25, gRenderer);
	//r.addRenderablePotion(300, 450, 25, gRenderer);
	//r.addRenderableManaPotion(400, 250, 25, gRenderer);
	//inventory2.placePotion(gRenderer);
	//inventory2.placeWeapon(gRenderer, 1, 19, 0, 20, 10);
	/*inventory2.placeWeapon(gRenderer, 1, 18, 1, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 2, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 3, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 4, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 5, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 6, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 7, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 8, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 9, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 10, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 11, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 12, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 13, 35, 10);
	inventory2.placeWeapon(gRenderer, 1, 19, 14, 20, 10);
	inventory2.placeWeapon(gRenderer, 1, 18, 15, 35, 10);*/ 



	SDL_Rect rooms[4];
	//SDL_Rect rooms[2];
	LTexture src;
	src.loadFromFile("images/tiles.png", gRenderer);
	rooms[0].x = 10;
	rooms[0].y = 0;
	rooms[0].w = 20;
	rooms[0].h = 10;

	rooms[1].x = 20;
	rooms[1].y = 10;
	rooms[1].w = 20;
	rooms[1].h = 6;

	rooms[2].x = 30;
	rooms[2].y = 16;
	rooms[2].w = 31;
	rooms[2].h = 30;

	rooms[3].x = 0;
	rooms[3].y = 46;
	rooms[3].w = 32;
	rooms[3].h = 2;
	//Room room1(rooms, 4);

	setTiles_();

	Room* temp = NULL;
	temp = LG.rooms[0];

	CoreManager cM;


	CoreFactory coref;
	coref.init(gRenderer);

	Core* coretemp = coref.makeCore(1, 800, 800);
	Core* coretemp1 = coref.makeCore(2, 700, 800);
	Core* coretemp2 = coref.makeCore(3, 600, 800);
	Core* coretemp3 = coref.makeCore(4, 500, 800);
	Core* coretemp4 = coref.makeCore(0, 400, 800);
	cM.addTail(coretemp);
	cM.addTail(coretemp1);
	cM.addTail(coretemp2);
	cM.addTail(coretemp3);
	cM.addTail(coretemp4);
	cM.addTail(coref.makeCore(5, 600, 600));

	Enemy firstEnemy(700, 700, 32);
	hyperCubeBoss Boss(1600, 1600, 64);
	HCBpawn pawn_0(-999, -999, 32);
	HCBpawn pawn_1(-999, -999, 32);
	HCBpawn pawn_2(-999, -999, 32);
	HCBpawn pawn_3(-999, -999, 32);
//	eM.insertEnemy(&firstEnemy);
//	firstEnemy.setTexture(&ogre);
//	firstEnemy.setAgro(&player);

	pawn_0.setNameTexture(&ogre);
	pawn_0.setAgro(&player);

	pawn_1.setNameTexture(&ogre);
	pawn_1.setAgro(&player);

	pawn_2.setNameTexture(&ogre);
	pawn_2.setAgro(&player);

	pawn_3.setNameTexture(&ogre);
	pawn_3.setAgro(&player);

	eM.insertEnemy(&Boss);
	Boss.setNameTexture(&ogre);
	Boss.setAgro(&player);
	Boss.setPawn(&pawn_0, 0);
	Boss.setPawn(&pawn_1, 1);
	Boss.setPawn(&pawn_2, 2);
	Boss.setPawn(&pawn_3, 3);
	Boss.setEM(&eM);

	////it goes in x, y, slot, sprite, projectilesprite, damage, range projectiles spd
	Bow bow1(100, 100, 1, 0, gRenderer, 0, 30, 6, 1, 6);
	Bow bow2(100, 100, 1, 1, gRenderer, 1, 10, 6, 2, 6);
	Bow bow3(100, 100, 1, 2, gRenderer, 2, 10, 6, 3, 6);
	Bow bow4(100, 100, 1, 3, gRenderer, 3, 40, 6, 1, 6);
	Sword sword(100, 100, 1, 3, gRenderer, 5, 60, 1, 3, 2);
	//r.addRenderable(&bow4);
	//bow1.placeInBag(&inventory2, gRenderer);
	//bow2.placeInBag(&inventory2, gRenderer);
	//bow3.placeInBag(&inventory2, gRenderer);
	//bow4.placeInBag(&inventory2, gRenderer);

	//inventory.placePotion(1);
	//inventory.placePotion(2);
	//r.addRenderable(&bow1);
	//Tile* tileSet[TOTAL_TILES+18];
//	loadLevelOneMedia(tileSet, gRenderer, "maps/levelone.map");
	loadPlayerMedia(gRenderer);
	loadSlimeMedia(gRenderer);
	loadProjectileMedia(gRenderer);
	
	SDL_Rect camera = {0,0,   SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_Rect largeChat = { 20, 152, 12, 8 };
	SDL_Event e;

	EquipInv equipInv(SCREEN_WIDTH, 50);
	//equipInv.equips[1] = new Bow(100, 100, 1, 0, gRenderer, 0, 10, 6);
	equipInv.loadSprite("images/equipinv.png", gRenderer);

	ProjectileManager p;
	ProjectileManager enemyP;

	Boss.setPM(&enemyP);
	pawn_0.setPM(&enemyP);
	pawn_1.setPM(&enemyP);
	pawn_2.setPM(&enemyP);
	pawn_3.setPM(&enemyP);

	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	int frame = 0;
	SDL_Rect* currentClip; 
	player.hotbar->addItem(&bow4);
	player.hotbar->addItem(&sword);
	player.setWeapon(&sword);
	eM.renderNodes();

	Level level_1(&eM, &player);



	while (true)
	{
		time(&timer);


		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_p:
					temp = LG.rooms[1];
					break;
				case SDLK_o:
					temp = LG.rooms[2];
					break;
				}
			}
			player.handleEvent(e);
			equipInv.handleEvent(e);
			//inventory2.handleEvent(e);
		}
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		//equipInv.handleMovement(player, inventory2, gRenderer);
		//inventory2.handleMovement(player, equipInv, gRenderer);

		SDL_RenderClear(gRenderer);
		
		eM.moveAll(player, &level_1, enemyP, cM, gRenderer, coref);
		player.update(&level_1, &p, &camera, &equipInv, gRenderer, eM);

		player.setCamera(camera);
		//temp->render(gRenderer, camera, src, &player);
		level_1.renderNodes(camera, gRenderer, src);
		
		//firstEnemy.render(gRenderer, camera);
		//firstEnemy.renderInfo(gRenderer, camera);
		eM.renderAll(camera, gRenderer, temp, &player);

		p.renderAll(camera, gRenderer, &eM, temp, &player);
		enemyP.renderAllEnemy(camera, gRenderer, player, level_1._Level->rooms[0]);
		currentClip = player.getClip();

		//inventory2.renderAll(camera, gRenderer);
		//equipInv.render(camera, gRenderer);
		//equipInv.renderModularItems(player, gRenderer, camera);
		//player.render(camera, currentClip, gRenderer, 0, 0, flipType, 0);

		//temp->renderWalls(gRenderer, camera, src, &player);

		//room1.renderWalls(gRenderer, camera, src, &player );
		player.renderBars(gRenderer);
		player.renderBow(gRenderer, camera);
		//temp->renderMiniMap(gRenderer, &player);
		//room1.renderMiniMap(gRenderer, &player);
		r.renderAll(gRenderer, camera, &player, player.hotbar);
		//player.render(camera, currentClip, gRenderer, NULL, 0, flipType, &largeChat);

		
		//SDL_RenderDrawLine(gRenderer, firstEnemy.x - camera.x, firstEnemy.y - camera.y, player.x - camera.x, player.y - camera.y);
		if (false)// && basenpc[1]->getAlive() && basenpc[2]->getAlive())
		{
			//this means a level was cleared. we should call this after all render loops
			//now the player can level up and we can add more enemies
			//player.LevelUp();
			cLevel++;
			dialogue.loadFromRenderedText("Level: " + std::to_string(player.getLevel()), textColor, gRenderer, gFont);
			/*for (int w = 0; w < Slimes; w++)
			{
				delete basenpc[w];
			}*/
			//delete basenpc;
			if (cLevel > 0 && cLevel % 3 == 0)
			{
				
				basenpc[0] = new BaseNpc(1800, 700);
				basenpc[1] = new HyperCube(1700, 800);
				basenpc[2] = new BossSlime(1900, 700);
				//eM.insertEnemy(basenpc[0]);
				//eM.insertEnemy(basenpc[1]);
				//eM.insertEnemy(basenpc[2]);
			}
			else
			{

				basenpc[0] = new BaseNpc(1800, 700);
				basenpc[1] = new HyperCube(1700, 800);
				basenpc[2] = new BossSlime(1900, 700);
				//eM.insertEnemy(basenpc[0]);
				//eM.insertEnemy(basenpc[1]);
				//eM.insertEnemy(basenpc[2]);
			}
		}
	//	coretemp->render(gRenderer, camera);
		cM.render(gRenderer, camera, &player);
		player.incrementFrames();
		//system("CLS");
		//std::cout << player.getLevel();
		//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//dialogue.loadFromRenderedText("Coins x " + std::to_string(player.coins), textColor, gRenderer, gFont);
		//dialogue.render((SCREEN_WIDTH - dialogue.getWidth())/2, 30, NULL, gRenderer, NULL, 0, flipType);

		//gCubeTexture1.render(5, 5, &cubeSprites[1], gRenderer);
		//CubeTexture.render(5, 5, &cubeSprites[1], gRenderer);
		time(&timer2);
		seconds = difftime(timer, timer2);
		//std::cout << seconds << '\n';
		//endMessage.loadFromRenderedText(std::to_string(60.0 / seconds), textColor, gRenderer, gFont);
		//endMessage.render((SCREEN_WIDTH - endMessage.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL, gRenderer, NULL, 0, flipType);

		SDL_RenderPresent(gRenderer);

		if (player.getHealth() <= 0)
			break;
	}
	
	SDL_RenderPresent(gRenderer);
	std::cin.get();
}

bool checkCollision(SDL_Rect a, SDL_Rect b, int offsety = 0)
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
	topB = b.y+offsety;
	bottomB = b.y + b.h+offsety;

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

bool touchesWall(SDL_Rect box, Room* room, int offsety)
{
	//go through the tiles
	for (int i = 0; i < room->wallsCapacity; i++)
	{
		if (((room->walls[i].getType() > 0) && (room->walls[i].getType() < 14)))
		{
			//check collision box
			if (checkCollision(box, room->walls[i].getBox(), offsety))
			{
				return true;
			}
		}
	}
	return false;
}

bool touchesPlayer(SDL_Rect box, Player player)
{
	if (checkCollision(box, player.getBox(), 0))
	{
		return true;
	}
	return false;
}















///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//////////    ///////                   ///////
      ///     ///   ///                 ///
   ///        ///    //                 /// ///   
//    ///     ///   ///                 ///  
 //////       ///////                   ///////
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LPolygon.h"

struct Vertice {
	int x, y, z;
};

class polygon
{
public:

	polygon()
	{
		for (int i = 0; i < 10; i++)
		{
			listStart[i]->x = NULL;
			listStart[i]->y = NULL;
			listEnd[i]->x = NULL;
			listEnd[i]->y = NULL;
		}
	}

	void draw(SDL_Renderer* gRenderer)
	{
		SDL_SetRenderDrawColor(gRenderer, 100, 0, 0, 255);

		for (int i = 0; i < vertices; i++)
		{
			if (!(listStart[i]->x == NULL || listStart[i]->y == NULL || listEnd[i]->x == NULL || listEnd[i]->y == NULL ) )    SDL_RenderDrawLine(gRenderer, listStart[i]->x, listStart[i]->y, listEnd[i]->x, listEnd[i]->y);
		}	
	}
	int vertices;

	Vertice* listStart[10];
	Vertice* listEnd[10];
};

void drawRect(polygon *a)
{
	for (int i = 0; i < 10; i++)
	{
		
	}
}
void _3D_Engine_Init()
{
	initSDL();
	class polygon square;

	//SDL_Rect square = { 500, 500, 50, 50 };
	int* listx[10];
	int* listy[10];
	

	square.listStart[0]->x = 50;
	square.listStart[0]->y = 50;
	square.listEnd[0]->x = 100;
	square.listEnd[0]->y = 50;

	square.listStart[1]->x = 100;
	square.listStart[1]->y = 50;
	square.listEnd[1]->x = 100;
	square.listEnd[1]->y = 100;

	square.listStart[2]->x = 100;
	square.listStart[2]->y = 100;
	square.listEnd[2]->x = 50;
	square.listEnd[2]->y = 100;

	square.listStart[0]->x = 50;
	square.listStart[0]->y = 100;
	square.listEnd[0]->x = 50;
	square.listEnd[0]->y = 50;


	square.listStart[0]->x = 50;
	square.listStart[0]->y = 50;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;



	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	square.listStart[0]->x = NULL;
	square.listStart[0]->y = NULL;
	square.listEnd[0]->x = NULL;
	square.listEnd[0]->y = NULL;

	while (true)
	{
		SDL_RenderClear(gRenderer);
	
		

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderPresent(gRenderer);
		//Lpolygon.render;
	}
}































