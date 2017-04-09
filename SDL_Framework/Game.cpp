#include "Game.h"

using namespace sdlframework;

game::game()
{
	//can put not sdl-related stuff here, sdl only get initialised after this constructor, but before init()
}

//your game destructor
game::~game()
{

}

//game initialisation
void sdlframework::game::init()
{
	left_click = false;
	splash.~splash_screen();

	srand(time(NULL));
	new (&splash) splash_screen(sdl_manager::get_renderer());
	//change_color();
	//cur_color = RGB{ 0, 0, 0 };
	game_state = constants::game_state::splash;
}

//called every frame
void sdlframework::game::input()
{
	static bool left_down = false;
	
	//reading events such as windows X button pressed
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			quit_game = true;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)//reading mouse events to determine when the click occurs
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				left_down = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (left_down)
					std::cout << "Clicked" << std::endl;
				left_down = false;
			}
		}
	}

}

//updates every frame until false is returned
bool game::update(Uint32 delta_time)
{
	bool game_running = true;

	splash.update(delta_time);
	switch (game_state)
	{
	case constants::game_state::splash:
		//splash.update(delta_time);
		//std::cout << splash.is_splash_elapsed() << std::endl;
		if (splash.is_splash_elapsed())
			game_state = constants::game_state::main_menu;
		break;
	case constants::game_state::main_menu:
		break;
	case constants::game_state::pause_menu:
		break;
	case constants::game_state::game_flow:
		break;
	}

	if (quit_game == true)
		game_running = false;
	return game_running;
}

//draws every frame
void game::draw(SDL_Renderer* renderer)
{
	switch (game_state)
	{
	case constants::game_state::splash:
		splash.draw(renderer);
		break;
	case constants::game_state::main_menu:
		break;
	case constants::game_state::pause_menu:
		break;
	case constants::game_state::game_flow:
		break;
	}
}

//customly created method
void game::change_color()
{
	dest_color = RGB{ rand()%255, rand()%255, rand()%255 };
	std::cout << "color changed" << std::endl;
	std::cout << "DR:" << dest_color.R << " DG:" << dest_color.G << " DB:" << dest_color.B << std::endl;
}
