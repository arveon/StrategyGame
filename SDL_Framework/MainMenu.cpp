#include "MainMenu.h"



void main_menu::init()
{
	
	start.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, start.start);
	load.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, load.load);
	options.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, options.options);
	exit.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, exit.exit);
	cur_state = state::waiting;

	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_inkedout);

	font = sdlframework::sdl_manager::load_font(fontpath, 15, { 255, 255, 255 });
	display = new TextRenderer(font, { 255, 255, 255 }, "default text");
}

void main_menu::update(Mouse mouse)
{
	//if exit was clicked, change the caption, menu state and reset the button
	if (exit.is_clicked())
	{
		display->change_caption("attempting to close the window");
		cur_state = state::exit_clicked;
		exit.reset_button();
	}
	
	//if exit wasn't clicked update all the buttons and check if they were clicked
	if (cur_state != state::exit_clicked && cur_state != options_clicked)
	{
		start.update(mouse);
		load.update(mouse);
		options.update(mouse);
		exit.update(mouse);

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
	else if (cur_state == exit_clicked)//if exit was clicked 
	{
		//if the confirm box didn't exist before, create it
		if (exit_confirmation == nullptr)
		{
			// temp = sdlframework::sdl_manager::create_texture(sdlframework::sdl_manager::get_renderer(), constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
			SDL_Texture* temp = sdlframework::sdl_manager::load_png_texture(sdlframework::sdl_manager::get_renderer(), "assets/graphics/temp_dialog_bg.png");
			std::string caption = "Are you sure you want to exit?";
			SDL_Point center = SDL_Point{ (constants::WINDOW_WIDTH - constants::CONFIRM_EXIT_DIALOG_WIDTH) / 2 , (constants::WINDOW_HEIGHT - constants::CONFIRM_EXIT_DIALOG_HEIGHT) / 2  };
			exit_confirmation = new confirm_dialog(temp, center, caption, constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
		}
		//update the dialog box
		exit_confirmation->update(mouse);

		if (exit_confirmation->is_confirmed())
			cur_state = state::exit_confirmed;
		if (exit_confirmation->is_cancelled())
		{
			delete exit_confirmation;
			exit_confirmation = nullptr;
			cur_state = state::waiting;
		}
	}
	else if (cur_state == options_clicked)
	{
		if (options_message == nullptr)
		{
			
			SDL_Texture* temp = sdlframework::sdl_manager::load_png_texture(sdlframework::sdl_manager::get_renderer(), "assets/graphics/temp_dialog_bg.png");
			std::string caption = "Options panel is under development...";
			SDL_Point center = SDL_Point{ (constants::WINDOW_WIDTH - constants::CONFIRM_EXIT_DIALOG_WIDTH) / 2 , (constants::WINDOW_HEIGHT - constants::CONFIRM_EXIT_DIALOG_HEIGHT) / 2 };
			options_message = new message_box(temp, center, caption, constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
		}
		options_message->update(mouse);
		if (options_message->is_confirmed())
		{
			delete options_message;
			options_message = nullptr;
			cur_state = state::waiting;
			options.reset_button();
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

	if (cur_state == state::exit_clicked && exit_confirmation != nullptr)
		exit_confirmation->draw(renderer);
	else if (cur_state == state::options_clicked && options_message != nullptr)
		options_message->draw(renderer);
}

main_menu::main_menu()
{
}


main_menu::~main_menu()
{
	delete display;
}
