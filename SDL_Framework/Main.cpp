#include "System.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	sdlframework::system system;
	//system.init_system();
	system.game_loop();
	system.cleanup();

	return 0;
}
