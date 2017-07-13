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
	srand((unsigned int)time(NULL));

	splash.~splash_screen();
	new (&splash) splash_screen(sdl_manager::get_renderer());

	menu.init();
	game_state = constants::game_state::main_menu;
	mouse.init();

	state_before_exit = constants::game_state::game_flow;
}

//called every frame
void sdlframework::game::input()
{
	mouse.prev_lmb_down = mouse.lmb_down;
	mouse.prev_rmb_down = mouse.rmb_down;

	//reading events such as windows X button pressed
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			state_before_exit = game_state;
			game_state = constants::game_state::confirming_exit;
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

	//exit splash screen on press of escape
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		if (game_state == constants::game_state::splash)
			game_state = constants::game_state::main_menu;
	}

	SDL_GetMouseState(&mouse.x, &mouse.y);	
	mouse.update();
}

//updates every frame until false is returned
bool game::update(Uint32 delta_time)
{
	bool game_running = true;

	switch (game_state)
	{
	case constants::game_state::splash:
		splash.update(delta_time);
		if (splash.is_splash_elapsed())
			game_state = constants::game_state::main_menu;
		break;
	case constants::game_state::main_menu:
		menu.update(mouse);

		if (menu.cur_state == main_menu::state::exit_clicked)
		{
			state_before_exit = game_state;
			game_state = constants::game_state::confirming_exit;
		}

		break;
	case constants::game_state::pause_menu:
		break;
	case constants::game_state::game_flow:
		break;
	case constants::game_state::confirming_exit:
		if (exit_confirm == nullptr)
		{
			SDL_Point center = SDL_Point{ (constants::WINDOW_WIDTH - constants::CONFIRM_EXIT_DIALOG_WIDTH) / 2, (constants::WINDOW_HEIGHT - constants::CONFIRM_EXIT_DIALOG_HEIGHT) / 2 };
			exit_confirm = new confirm_dialog(sdlframework::sdl_manager::create_texture(1, 1, { 255, 255, 255 }), center, "Are you sure you want to exit?", constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
		}
		exit_confirm->update(mouse);

		if (exit_confirm->is_confirmed())
		{
			delete exit_confirm;
			exit_confirm = nullptr;
			game_running = false;
		}
		else if (exit_confirm->is_cancelled())
		{
			delete exit_confirm;
			exit_confirm = nullptr;
			game_state = state_before_exit;

			if (state_before_exit == constants::main_menu)
				menu.reset_state();
		}

		break;
	}
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
	case constants::game_state::confirming_exit:
		if (state_before_exit == constants::main_menu)
			menu.draw(renderer);
		
		if (exit_confirm != nullptr)
			exit_confirm->draw(renderer);
		break;
	}

	mouse.draw(renderer);
}
