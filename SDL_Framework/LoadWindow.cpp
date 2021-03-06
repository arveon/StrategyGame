#include "LoadWindow.h"

/*
	default and only constructor
	will need to be programmed only once and is only used once in the entire game
*/
load_window::load_window()
{
	cur_state = state::waiting;
	
	//init buttons
	back.init(constants::font_inkedout, "Back", 16);
	back.set_position({ constants::setup::WINDOW_WIDTH - back.get_width() - 20, constants::setup::WINDOW_HEIGHT - back.get_height() - 10 });

	load.init(constants::font_inkedout, "Apply", 16);
	load.set_position({ constants::setup::WINDOW_WIDTH - back.get_width() - load.get_width() - 50, constants::setup::WINDOW_HEIGHT - load.get_height() - 10 });

	//initialise the saves list
	//textures
	SDL_Texture* texture = sdlframework::sdl_manager::create_texture(1, 1, {150,150,150});
	SDL_Texture* selected_bg = sdlframework::sdl_manager::create_texture(1, 1, { 200, 150, 110 });

	//a dummy list
	//TODO: replace this with file names in the saves folder
	std::vector<list_item> items;
	items = file_handler::get_saved_files();
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });
	items.push_back({ "asd", "asd" });

	//font
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_optimus);
	//final (textures for the slider are loaded from inside for now)
	//TODO: decide if they should be loaded here and passed on
	saves_list = new item_list(fontpath, { 50, 50, 170 }, texture, { 10, 10, 300, 300 }, selected_bg, items);
}

/*
	updates screen state based on mouse state
*/
void load_window::update(Mouse* mouse)
{
	back.update(mouse);
	load.update(mouse);
	saves_list->update(mouse);

	if (back.is_clicked())
		cur_state = state::back_clicked;
	else if (load.is_clicked())
		cur_state = state::load_clicked;
}

void load_window::draw(SDL_Renderer* renderer)
{
	back.draw(renderer);
	load.draw(renderer);
	saves_list->draw(renderer);
}

load_window::~load_window()
{
	delete saves_list;
}
