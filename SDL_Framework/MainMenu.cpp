#include "MainMenu.h"



void main_menu::init()
{
	start.init(sdlframework::sdl_manager::load_png_texture(sdlframework::sdl_manager::get_renderer(), "assets/graphics/start.png"), start.start);
	load.init(sdlframework::sdl_manager::load_png_texture(sdlframework::sdl_manager::get_renderer(), "assets/graphics/start.png"), load.load);
	options.init(sdlframework::sdl_manager::load_png_texture(sdlframework::sdl_manager::get_renderer(), "assets/graphics/start.png"), options.options);
	exit.init(sdlframework::sdl_manager::load_png_texture(sdlframework::sdl_manager::get_renderer(), "assets/graphics/start.png"), exit.exit);
	cur_state = state::waiting;
}

void main_menu::update(Mouse mouse)
{
	start.update(mouse);
	load.update(mouse);
	options.update(mouse);
	exit.update(mouse);


	if (exit.is_clicked())
	{
		cur_state = state::exit_clicked;
		exit.reset_button();
	}
	else if (start.is_clicked())
	{
		cur_state = state::start_clicked;
		start.reset_button();
	}
	else if (load.is_clicked())
	{
		cur_state = state::load_clicked;
		load.reset_button();
	}
	if (options.is_clicked())
	{
		cur_state = state::options_clicked;
		options.reset_button();
	}
}

void main_menu::draw(SDL_Renderer* renderer)
{
	start.draw(renderer);
	load.draw(renderer);
	options.draw(renderer);
	exit.draw(renderer);
}

main_menu::main_menu()
{
}


main_menu::~main_menu()
{
}
