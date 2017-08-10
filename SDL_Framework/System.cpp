#include "System.h"

//TODO: remove all debug messages

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
	init_constants();

	sdl_manager::init();
}

bool system::init_constants()
{
	bool successful = false;
	std::vector<list_item> settings = file_handler::get_launch_config();
	if (settings.size() == 0)
		return successful;
	else
		successful = true;
	constants::setup::init_settings(settings);

	return successful;
}

/*currently not used for anything*/
system::~system()
{
}

//utterly useless, put initialisation logic at the top of the game loop function
void system::init_system()
{
}

