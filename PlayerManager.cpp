#include "PlayerManager.h"
#include "Player.h"

PlayerManager::PlayerManager()
{
	pCount = 4;
	playerlist = new PNode[4];
}

void PlayerManager::update()
{
	for (int i = 0; i < pCount; i++)
	{
		//playerlist[i].player->move();
	}
}