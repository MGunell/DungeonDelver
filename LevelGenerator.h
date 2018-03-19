#pragma once

class Room;
class SDL_Rect;


class LevelGenerator
{
public:
	LevelGenerator();

	Room* rooms[4];
private:
	int capacity;
	SDL_Rect** roomVertexes;
};