#include "LevelGenerator.h"
#include "Room.h"

LevelGenerator::LevelGenerator()
{
	capacity = 1;

	roomVertexes = NULL;

	roomVertexes = new SDL_Rect*[1];

	for (int i = 0; i < capacity; i++)
	{
		roomVertexes[i] = new SDL_Rect[1];
	}

	for (int i = 0; i < capacity; i++)
	{
		for (int j = 0; j < capacity; j++)
		{
			roomVertexes[i][j].x = 0;
			roomVertexes[i][j].y = 0;
			roomVertexes[i][j].w = 50;
			roomVertexes[i][j].h = 50;
		}
	}
	rooms[0] = new Room(roomVertexes[0], 1); 
	//rooms[1] = new Room(roomVertexes[1], 4);
//	rooms[2] = new Room(roomVertexes[2], 4);
	//rooms[3] = new Room(roomVertexes[3], 4);

}