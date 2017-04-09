#include "System.h"

using namespace sdlframework;
void system::init_system()
{
	
}

void system::game_loop()
{
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
