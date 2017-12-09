//this is the main file for the game that imports and runs all loops
#include "Main.h"
#include "Engine.h"

int main(int argc, char* args[])
{
	//loadsomeFiles();
	//loadMenu();
	gameStates states = New_game;
	switch (states)
	{
	case start_game:
		startgame();
	case New_game:
		levelOne();
		//startMapEditor();
		//while (notPaused == true) {};
		//New_game();//run the new game stuff that you need to get user input and calibrate everything
		break;
	case Pause_menu:
		//while (paused == true) {};
			break;
	};
	return 0;
}