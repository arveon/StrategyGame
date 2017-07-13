#include "System.h"

using namespace sdlframework;

/*
	function represents the game loop
*/
void system::game_loop()
{
	//need to call these functions here as they don't get called in init_system for some reason
	time.init();
	game.init();

	bool gameGoing = true;
	while (gameGoing)
	{
		time.update();
		game.input();
		gameGoing = game.update(time.get_delta_time());

		SDL_RenderClear(sdl_manager::get_renderer());
		game.draw(sdl_manager::get_renderer());
		SDL_RenderPresent(sdl_manager::get_renderer());
	}
}

//called before the program exits
void system::cleanup()
{
}


system::system()
{
	sdl_manager::init();
}

/*currently not used for anything*/
system::~system()
{
}

//utterly useless, put initialisation logic at the top of the game loop function
void system::init_system()
{
}

