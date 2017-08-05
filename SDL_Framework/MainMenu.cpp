#include "MainMenu.h"

/*
	Default initialiser is used as main menu is only used for one purpose in one state of the program
*/
void main_menu::init()
{
	//init all the buttons
	start.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, start.start);
	load.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, load.load);
	options.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, options.options);
	exit.init(constants::font_inkedout, constants::MAIN_MENU_BUTTON_FONT_SIZE, exit.exit);

	cur_state = state::waiting;

}

void main_menu::update(Mouse mouse)
{
	//if exit was clicked change menu state and reset the button
	if (exit.is_clicked())
	{
		cur_state = state::exit_clicked;
		exit.reset_button();
	}
	
	//if in waiting state (eg nothing changed the state before) update all the buttons and check if they were clicked
	if (cur_state == state::waiting)
	{
		start.update(mouse);
		load.update(mouse);
		options.update(mouse);
		exit.update(mouse);

		//check if any of the buttons were clicked and update the screen state appropriately
		if (start.is_clicked())
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
	
	//depending on the state of the menu, show/create appropriate windows/do appropriate actions
	if (cur_state == options_clicked)
	{//if options were clicked, if the options menu wasn't open before, create it and update
		if (options_window == nullptr)
		{
			options_window = new options_menu();
		}
		options_window->update(mouse);
		
		//if settings were applied/cancelled either save menu and close it, or close without saving
		if (options_window->is_applied() || options_window->is_back_clicked())
		{
			if(options_window->is_applied())
				options_window->save();

			delete options_window;
			options_window = nullptr;
			cur_state = state::waiting;
		}
	}
	else if (cur_state == start_clicked)
	{//if start got clicked, create a msgbox saying that this feature isn't avaiblable yet
		//TODO: replace the placeholder window with actual game flow screen and add start adding game logic
		if (msg_box == nullptr)
		{
			SDL_Texture* temp = sdlframework::sdl_manager::create_texture(1, 1, { 255, 255, 255 });
			msg_box = new message_box(temp, { constants::WINDOW_WIDTH / 2 - 200, constants::WINDOW_HEIGHT / 2 - 50}, "This feature is not available yet!", 400, 100);
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
	{//if load game is clicked, go into load screen and create it if it doesn't exist
		if (load_game_window == nullptr)
		{
			load_game_window = new load_window();
		}
		load_game_window->update(mouse);

		//if screen is closed, destroy it
		if (load_game_window->is_back())
		{
			delete load_game_window;
			load_game_window = nullptr;
			cur_state = state::waiting;
		}
		//TODO: Add logic to load the game and apply it to Load button of load screen
	}
}

void main_menu::draw(SDL_Renderer* renderer)
{
	//depending on the state draw appropriate elements
	if (cur_state == state::options_clicked && options_window != nullptr)
		options_window->draw(renderer);//only draw options window if user is in options and the screen has been created
	else if (cur_state == state::load_clicked && load_game_window != nullptr)
		load_game_window->draw(renderer);//same with load game window
	else
	{//if user isn't in the menu that takes up the entire screen, draw buttons and the msgbox if it exists
		start.draw(renderer);
		load.draw(renderer);
		options.draw(renderer);
		exit.draw(renderer);

		if (msg_box != nullptr)
			msg_box->draw(renderer);
	}
}

main_menu::main_menu()
{
}


main_menu::~main_menu()
{
}