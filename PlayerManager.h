#pragma once
class Player;

class PNode
{
public:
	PNode() { 
		player = nullptr;
		next = nullptr;
		}

	PNode * next;
	Player* player;

};

class PlayerManager
{
public:
	PlayerManager();

	void update();

private:

	PNode* playerlist;
	int pCount;


};