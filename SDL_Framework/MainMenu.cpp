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
		//display->change_caption("attempting to close the window");
		cur_state = state::exit_clicked;
		exit.reset_button();
	}
	
	//if exit wasn't clicked update all the buttons and check if they were clicked
	if (cur_state == state::waiting)
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
	
	/*if (cur_state == exit_clicked)//if exit was clicked 
	{
		//if the confirm box didn't exist before, create it
		if (exit_confirmation == nullptr)
		{
			SDL_Texture* temp = sdlframework::sdl_manager::create_texture(constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT, { 255,255,255 });
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
	else */if (cur_state == options_clicked)
	{
		if (options_window == nullptr)
		{
			options_window = new options_menu();
		}
		options_window->update(mouse);
		
		if (options_window->is_applied())
		{
			options_window->save();
			delete options_window;
			options_window = nullptr;
			cur_state = state::waiting;
		}
		else if (options_window->is_back_clicked())
		{			
			delete options_window;
			options_window = nullptr;
			cur_state = state::waiting;
		}
	}
	else if (cur_state == start_clicked)
	{
		if (msg_box == nullptr)
		{
			SDL_Texture* temp = sdlframework::sdl_manager::create_texture(200, 100, { 255, 255, 255 });
			msg_box = new message_box(temp, { constants::WINDOW_WIDTH / 2 - 200, constants::WINDOW_HEIGHT / 2 - 50 }, "This feature is not available yet!", 400, 100);
		}
		msg_box->update(mouse);

		if (msg_box->is_confirmed())
		{
			delete msg_box;
			msg_box = nullptr;
			cur_state = state::waiting;
		}
	}
	else if (cur_state == load_clicked)
	{
		if (load_game_window == nullptr)
		{
			load_game_window = new load_window();
		}
		load_game_window->update(mouse);

		if (load_game_window->is_back())
		{
			delete load_game_window;
			load_game_window = nullptr;
			cur_state = state::waiting;
		}
	}
}

void main_menu::draw(SDL_Renderer* renderer)
{
	if (cur_state == state::options_clicked && options_window != nullptr)
		options_window->draw(renderer);
	else if (cur_state == state::load_clicked && load_game_window != nullptr)
		load_game_window->draw(renderer);
	else
	{
		start.draw(renderer);
		load.draw(renderer);
		options.draw(renderer);
		exit.draw(renderer);
		display->draw(renderer);

		if (cur_state == state::exit_clicked && exit_confirmation != nullptr)
			exit_confirmation->draw(renderer);
		if (msg_box != nullptr)
			msg_box->draw(renderer);

	}
}

main_menu::main_menu()
{
}


main_menu::~main_menu()
{
	delete display;
}
