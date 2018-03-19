#include "Renderable.h"
#include <math.h>
#include "Player.h"
#include "InventoryRedux.h"
#include "Equipment_Inventory.h"


#define PI 3.14

Renderable::Renderable(int x1, int y1) {
	x = x1;
	y = y1;
	angle = 0;
	lifetime = 300;
	slot = -1;
	renderable = false;
	textColor = { 0, 0, 0 };
	gFont1 = TTF_OpenFont("fonts/lazy.ttf", 30);
};

void Renderable::setClips() {
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			clips[i*10 + j].x = i * width;
			clips[i*10 + j].x = j * height;
			clips[i*10 + j].w = width;
			clips[i*10 + j].h = height;
		}
	}
}

void Renderable::setSpriteFile(std::string filename, SDL_Renderer* gRenderer) {
	sprite.loadFromFile(filename, gRenderer);
}

void Renderable::render(int x, int y, SDL_Renderer* gRenderer, double angle)
{
	sprite.renderHalf(x, y, &clips[spriteNum], gRenderer, angle);
}

void Renderable::render(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
	sprite.renderHalf(x - camera.x, y - camera.y, &clips[spriteNum], gRenderer);
}

void Renderable::renderInv(SDL_Renderer* gRenderer, SDL_Rect& camera)
{
	sprite.renderHalf(x + 4, y + 2, &clips[spriteNum], gRenderer);
}

void Renderable::waveMove() {
	y += .35 * sin(angle * PI/ 180);
	if (angle <= 360) angle += 6;
	else angle = 0;

	lifetime -= 3;
}

void Renderable::placeItem(Inventory3* inv)
{
	inv->addItem(this);
}

//Item* Renderable::placeSelf(int x, int y)
//{
	//return new Potion(x, y, 1);
//}

bool PickUp(Renderable& a, Player& p)
{
	int LeftA, LeftP;
	int RightA, RightP;
	int TopA, TopP;
	int BottomA, BottomP;

	LeftA = a.x;
	RightA = a.x + a.width*2;
	TopA = a.y;
	BottomA = a.y + a.height*2;

	LeftP = p.mCollider.x;
	RightP = p.mCollider.x + p.mCollider.w * 2;
	TopP = p.mCollider.y;
	BottomP = p.mCollider.y + p.mCollider.h * 2;

	if (BottomA <= TopP || TopA >= BottomP || RightA <= LeftP || LeftA >= RightP) return false;

	return true;
}

Renderable::~Renderable() {
	std::cout << "deleted a renderable\n";
}