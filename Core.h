#pragma once
#include "LTexture.h"



class Core
{
public:
	Core(int x1 = -9999, int y1 = -9999)
	{
		radius = 10;
		angle = 0;
		x = x1;
		y = y1;
		box = NULL;
		coreTexture = NULL;
	}

	void render(SDL_Renderer* gRenderer, SDL_Rect& camera)
	{
		coreTexture->render((x - radius) - camera.x, (y - radius) - camera.y, box, gRenderer);
	}

	void waveMove()
	{
		y += (.5 * sin((angle * 3.14) / 180));
		if (angle <= 360) angle += 6;
		else angle = 0;
	}

	void setTexture(LTexture* src)
	{
		coreTexture = src;
	}

	void setRect(SDL_Rect* src)
	{
		box = src;
	}

	bool checkCollision(Player* player)
	{
		int x1, x2;
		int y1, y2;
		int r1, r2;

		x1 = player->x + player->mCollider.w;
		y1 = player->y + player->mCollider.h * 2;

		x2 = x;
		y2 = y;

		r1 = player->radius;
		r2 = radius;

		if ((x2 - x1) * (x2 - x1) + ((y1 - y2) * (y1 - y2)) < (r1 + r2) * (r1 + r2))
		{
			return true;
		}

		return false;
	}

	int radius;
	int angle;
	double x, y;
	int value;
	SDL_Rect* box;
	LTexture* coreTexture;
};

class greenCore : public Core
{
public:
	greenCore(int x1, int y1) : Core(x1, y1)
	{
		value = 1;
	}
};

class redCore : public Core
{
public:
	redCore(int x1, int y1) : Core(x1, y1)
	{
		value = 20;
	}
};

class blueCore : public Core
{
public:
	blueCore(int x1, int y1) : Core(x1, y1)
	{
		value = 5;
	}
};

class orangeCore : public Core
{
public:
	orangeCore(int x1, int y1) : Core(x1, y1)
	{
		value = 50;
	}
};

class silverCore : public Core
{
public:
	silverCore(int x1, int y1) : Core(x1, y1)
	{
		value = 100;
	}
};

class blackCore : public Core
{
public:
	blackCore(int x1, int y1) : Core(x1, y1)
	{
		value = 200;
	}
};

class CNode
{
public:
	CNode()
	{
		core = NULL;
		next = NULL;
		prev = NULL;
	}

	Core* core;
	CNode* next;
	CNode* prev;
};

class CoreManager
{
public:
	CoreManager()
	{
		capacity = 20;
		head = NULL;
		tail = NULL;
	}

	void addTail(Core* src)
	{
		CNode* temp = new CNode;
		temp->core = src;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}



	void render(SDL_Renderer* gRenderer, SDL_Rect& camera, Player* player)
	{
		CNode* temp = new CNode;
		temp = head;
		while (temp != NULL)
		{
			temp->core->waveMove();
			temp->core->render(gRenderer, camera);

			if (temp->core->checkCollision(player) == true)
			{
				player->coins += temp->core->value;

				if (temp == head)
				{
					CNode* temP = new CNode;
					temP = temp->next;
					delete head;
					head = temP;

					temp = temP;
				}
				else if (temp == tail)
				{
					CNode* temP = new CNode;
					temP = tail->prev;
					temP->next = NULL;
					delete tail;
					tail = temP;
					

					temp = NULL;
				}
				else
				{
					CNode* temP = new CNode;
					temP = temp;
					temp->prev->next = temP->next;
					temP->next->prev = temp->prev;

					temp = temp->next;
					delete temP;
				}
			}
			else
			{
				temp = temp->next;
			}
		}
	}


	CNode* head;
	CNode* tail;
	int capacity;
};

class CoreFactory
{
public:
	CoreFactory()
	{
		for (int i = 0; i < 6; i++)
		{
			coreRects[i].x = i * 10;
			coreRects[i].y = 0;
			coreRects[i].h = 10;
			coreRects[i].w = 10;
		}
	}

	void init(SDL_Renderer* gRenderer)
	{
		coreTextureSheet.loadFromFile("images/CoreCrystals.png", gRenderer);
	}

	Core* makeCore(int type, int x, int y)
	{
		if (type == 0)
		{
			Core* temp1 = new greenCore(x, y);
			temp1->setTexture(&coreTextureSheet);
			temp1->setRect(&coreRects[0]);
			return temp1;
		}
		if (type == 1)
		{
			Core * temp2 = new blueCore(x, y);
			temp2->setTexture(&coreTextureSheet);
			temp2->setRect(&coreRects[1]);
			return temp2;
		}
		if (type == 2)
		{
			Core * temp3 = new redCore(x, y);
			temp3->setTexture(&coreTextureSheet);
			temp3->setRect(&coreRects[2]);
			return temp3;
		}
		if (type == 3)
		{
			Core * temp4 = new orangeCore(x, y);
			temp4->setTexture(&coreTextureSheet);
			temp4->setRect(&coreRects[3]);
			return temp4;
		}
		if (type == 4)
		{
			Core * temp5 = new silverCore(x, y);
			temp5->setTexture(&coreTextureSheet);
			temp5->setRect(&coreRects[4]);
			return temp5;
		}
		if (type == 5)
		{
			Core * temp6 = new blackCore(x, y);
			temp6->setTexture(&coreTextureSheet);
			temp6->setRect(&coreRects[5]);
			return temp6;
		}
		return NULL;
	}

	LTexture coreTextureSheet;
	SDL_Rect coreRects[6];
	//all cores created get assigned this texture pointer
};