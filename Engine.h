#ifndef __Engine__
#define __Engine__

class Player;
class Tile;
class BaseNpc;
class BossSlime;



#include "SDL_mixer.h"
#include "BossSlime.h"
#include "Player.h"
#include "Selected.h"
#include "Tile.h"
#include "Inventory.h"
#include "RenderableManager.h"
#include <string>
bool init();
bool loadMedia();

void startgame();
void levelOne();
void initSDL();
void startMapEditor();

bool checkCollision(SDL_Rect a, SDL_Rect b);
bool touchesWall(SDL_Rect box, Tile* tiles[]);
bool touchesPlayer(SDL_Rect box, Player player);

//The music that will be played
//Mix_Music *gMusic = NULL;

//The sound effects that will be used
//Mix_Chunk *gScratch = NULL;
//Mix_Chunk *gHigh = NULL;
//Mix_Chunk *gMedium = NULL;
//Mix_Chunk *gLow = NULL;

static SDL_Renderer* gRenderer = NULL;
static SDL_Window* window = NULL;
static LTexture dialogue;
static LTexture endMessage;
static TTF_Font *gFont = NULL;
static SDL_Color textColor = { 255, 125, 255 };

#endif