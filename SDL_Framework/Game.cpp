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
	menu.init();
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
		
		//storing mouse clicks and mouse releases in mouse class
		if (event.type == SDL_MOUSEBUTTONDOWN)//reading mouse events to determine when the click occurs
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				mouse.lmb_down = true;
			else
				mouse.rmb_down = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				mouse.lmb_down = false;
			else
				mouse.rmb_down = false;
		}
	}

	SDL_GetMouseState(&mouse.x, &mouse.y);
	
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
		menu.update(mouse);

		switch (menu.cur_state)
		{
		case main_menu::state::exit_clicked:
			game_running = false;
			break;
		case main_menu::state::start_clicked:
			std::cout << "Start clicked" << std::endl;
			menu.cur_state = main_menu::state::waiting;
			break;
		case main_menu::state::options_clicked:
			std::cout << "Options clicked" << std::endl;
			menu.cur_state = main_menu::state::waiting;
			break;
		case main_menu::state::load_clicked:
			std::cout << "Load clicked" << std::endl;
			menu.cur_state = main_menu::state::waiting;
			break;
		}
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
		menu.draw(renderer);
		break;
	case constants::game_state::pause_menu:
		break;
	case constants::game_state::game_flow:
		break;
	}
}
