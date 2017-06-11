#include "MainMenu.h"



void main_menu::init()
{
	font = sdlframework::sdl_manager::load_font(constants::font_inkedout, 12, { 255, 255, 255 });
	start.init("Inked_Out.ttf", start.start);
	load.init("Inked_Out.ttf", load.load);
	options.init("Inked_Out.ttf", options.options);
	exit.init("Inked_Out.ttf", exit.exit);
	cur_state = state::waiting;

	display = new TextRenderer(font, { 255, 255, 255 }, "default text");
}

void main_menu::update(Mouse mouse)
{
	start.update(mouse);
	load.update(mouse);
	options.update(mouse);
	exit.update(mouse);

	if (exit.is_clicked())
	{
		display->change_caption("attempting to close the window");
		cur_state = state::exit_clicked;
		exit.reset_button();
	}
	
	if (cur_state != state::exit_clicked)
	{
		if (start.is_clicked())
		{
			display->change_caption("start clicked");
			cur_state = state::start_clicked;
			start.reset_button();
		}
		else if (load.is_clicked())
		{
			display->change_caption("load clicked");
			cur_state = state::load_clicked;
			load.reset_button();
		}
		if (options.is_clicked())
		{
			display->change_caption("options clicked");
			cur_state = state::options_clicked;
			options.reset_button();
		}
	}
	else
	{
		if (exit_confirmation == nullptr)
		{
			SDL_Texture* temp = sdlframework::sdl_manager::create_texture(sdlframework::sdl_manager::get_renderer(), constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
			std::string caption = "Are you sure you want to exit?";
			SDL_Point center = SDL_Point{ constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT / 2 };
			exit_confirmation = new confirm_dialog(temp, center, caption, constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
		}




	}
}

void main_menu::draw(SDL_Renderer* renderer)
{
	start.draw(renderer);
	load.draw(renderer);
	options.draw(renderer);
	exit.draw(renderer);
	display->draw(renderer);

	if (cur_state == state::exit_clicked)
		exit_confirmation->draw(renderer);
}

main_menu::main_menu()
{
}


main_menu::~main_menu()
{
	delete display;
}
