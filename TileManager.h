#pragma once
class Tile;
class Player;
#include "Tile.h"
#include "Player.h"

class TNode
{
public:
	Tile* tile;
	TNode* next;
};

class TileManager
{
	public:
		TileManager()
		{
			head = NULL;
			tail = NULL;
			used = 0;
		}

		void insertEnemy(Tile* enemy)
		{
			TNode* temp = new TNode;
			temp->tile = enemy;
			temp->next = NULL;

			if (head == NULL)
			{
				head = temp;
				tail = temp;
				temp = NULL;
			}
			else
			{
				tail->next = temp;
				tail = temp;
			}
			used++;
		}

		void deletePos(int pos)
		{
			if (pos == 0 && used > 1)
			{

				TNode* temp = new TNode;
				temp = head;
				head = head->next;

				delete temp;
			}
			else if (pos == 0 && used < 1)
			{
				delete head;
				head = NULL;
			}
			else if (pos == used - 1)
			{
				TNode *current = new TNode;
				TNode *previous = new TNode;
				current = head;
				while (current->next != NULL)
				{
					previous = current;
					current = current->next;
				}
				tail = previous;
				previous->next = NULL;
				delete current;
			}
			else
			{

				TNode* current = new TNode;
				TNode* previous = new TNode;
				current = head;
				for (int i = 0; i < pos; i++)
				{
					previous = current;
					current = current->next;
				}
				previous->next = current->next;
				delete current;
			}
			used--;
			renderTNodes();
		}

		void renderTNodes()
		{
			//std::cout << head->enemy->name << "------\n";
			TNode* temp = new TNode;
			temp = head;
			while (temp != NULL)
			{
				//std::cout << "  [" << temp->enemy->name << "] |||";
				temp = temp->next;
			}
		}

		/*void moveAll(Player& player, Room* room, ProjectileManager& p, RenderableManager& r, SDL_Renderer* gRenderer)
		{
			TNode* temp = new TNode;
			temp = head;
			int i = 0;
			while (temp != NULL)
			{
				if (temp->enemy->move(player, room, p, r, gRenderer) == false)
				{
					temp = temp->next;
					deletePos(i);
				}
				else
				{
					temp = temp->next;
				}
				i++;
			}
		}*/

		void renderWallsTop(SDL_Rect camera, SDL_Renderer* gRenderer, Player* player, LTexture& target, double rotation)
		{
			TNode* temp = new TNode;
			temp = head;
			while (temp != NULL)
			{
				double x1, y1;
				//y1 = (temp->tile->mBox.x - (player->mCollider.x + player->mCollider.w))*sin(rotation) + ((temp->tile->mBox.y) - (player->mCollider.y + player->mCollider.h*2 ))*cos(rotation);
				y1 = temp->tile->mBox.y;
				if (player->mCollider.y > y1)
					{ 
					
					//x1 = (temp->tile->mBox.x - (player->mCollider.x + player->mCollider.w))*cos(rotation) - ((temp->tile->mBox.y) - (player->mCollider.y + player->mCollider.h*2))*sin(rotation);
					x1 = temp->tile->mBox.x;

					//x1 += player->mCollider.x + player->mCollider.w;
					//y1 += player->mCollider.y + player->mCollider.h * 2;

					temp->tile->renderRotation(x1, y1, camera, gRenderer, target, (rotation * 180 / 3.14159));
					}
				temp = temp->next;
			}
		}

		void renderWallsBottom(SDL_Rect camera, SDL_Renderer* gRenderer, Player* player, LTexture& target, double rotation)
		{
			TNode* temp = new TNode;
			temp = head;
			while (temp != NULL)
			{
				double x1, y1;
				//y1 = (temp->tile->mBox.x - (player->mCollider.x + player->mCollider.w))*sin(rotation) + ((temp->tile->mBox.y ) - (player->mCollider.y + player->mCollider.h*2))*cos(rotation);
				y1 = temp->tile->mBox.y;
				if (player->mCollider.y <= y1 + 64)
				{
					//x1 = (temp->tile->mBox.x - (player->mCollider.x + player->mCollider.w))*cos(rotation) - ((temp->tile->mBox.y ) - (player->mCollider.y + player->mCollider.h*2))*sin(rotation);
					x1 = temp->tile->mBox.x;

					//x1 += player->mCollider.x + player->mCollider.w;
					//y1 += player->mCollider.y + player->mCollider.h * 2;

					temp->tile->renderRotation(x1, y1, camera, gRenderer, target, (rotation * 180 / 3.14159));
				}
				temp = temp->next;
			}
		}

		void renderAll(SDL_Rect camera, SDL_Renderer* gRenderer, Player* player, LTexture& target, double rotation)
		{
			TNode* temp = new TNode;
			temp = head;
			while (temp != NULL)
			{
				double x1, y1;

				x1 = (temp->tile->mBox.x - player->x)*cos(rotation) - (temp->tile->mBox.y - player->y)*sin(rotation);
				y1 = (temp->tile->mBox.x - player->x)*sin(rotation) + (temp->tile->mBox.y - player->y)*cos(rotation);

				x1 += player->x;
				y1 += player->y;

				temp->tile->renderRotation(x1, y1, camera, gRenderer, target, (rotation * 180 / 3.14159));

				temp = temp->next;
			}
		}

		TNode* head;
	private:

		TNode * tail;
		int used;
};