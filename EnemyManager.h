#pragma once
#include "BaseNpc.h"
#include "Enemy.h"
#include "Core.h"
class Enemy;
class BaseNpc;
class ProjectileManager;
class RenderableManager;
class Room;
//linked list

struct node
{
	Enemy* enemy;
	node* next;
};

class EnemyManager
{
public:
	EnemyManager()
	{
		head = NULL;
		tail = NULL;
		used = 0;
	}

	void insertEnemy(Enemy* enemy)
	{
		node* temp = new node;
		temp->enemy = enemy;
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
			std::cout << "1";
			node* temp = new node;
			temp = head;
			head = head->next;

			delete temp;
		}
		else if (pos == 0 && used <= 1)
		{
			std::cout << "2";
			delete head;
			head = NULL;
		}
		else if (pos == used-1 && used > 1)
		{
			std::cout << "3";
			node *current = new node;
			node *previous = new node;
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
			
			node* current = new node;
			node* previous = new node;
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
		//renderNodes();
	}

	void renderNodes()
	{	
		//std::cout << head->enemy->name << "------\n";
		node* temp = new node;
		temp = head;
		while (temp != NULL)
		{
			//std::cout << "  [" << temp->enemy->name << "] |||";
			temp = temp->next;
		}
	}

	void moveAll(Player& player, Level* level, ProjectileManager& p, CoreManager& r, SDL_Renderer* gRenderer, CoreFactory& rf)
	{
		node* temp = new node;
		temp = head;
		int i = 0;
		while (temp != NULL)
		{
			temp->enemy->update();

			if (temp->enemy->insideRadius())
			{
				player.dealDamage(temp->enemy->attackDamage);
				player.knockback(level,*this, *temp->enemy);
			}

			if (temp->enemy->hp < 0)
			{
				r.addTail(rf.makeCore(0, temp->enemy->x, temp->enemy->y));
				temp = temp->next;
				deletePos(i);
			}
			else
			{
				temp = temp->next;
			}
			i++;
		}
	}

	void renderAll(SDL_Rect camera, SDL_Renderer* gRenderer, Room* room, Player* player)	
	{
		node* temp = new node;
		temp = head;
		while (temp != NULL)
		{
			temp->enemy->render(gRenderer, camera);
			temp = temp->next;
		}
	}
	node * head;
	int used;
private:
	
	node* tail;

};