#include "OptionsMenu.h"

options_menu::options_menu()
{
	cur_state = state::waiting;
	//init buttons
	back.init(constants::font_inkedout, "Back", 16);
	back.set_position({ constants::setup::WINDOW_WIDTH - back.get_width() - 20, constants::setup::WINDOW_HEIGHT - back.get_height() - 10 });

	apply.init(constants::font_inkedout, "Apply", 16);
	apply.set_position({ constants::setup::WINDOW_WIDTH - back.get_width() - apply.get_width() - 50, constants::setup::WINDOW_HEIGHT - apply.get_height() - 10 });

	//required for sliders and checkboxes
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_optimus);

	//create placeholder textures for master volume slider
	SDL_Texture* bar_temp = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* slider_temp = sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 });

	volume = new slider(sdlframework::sdl_manager::load_font(fontpath, 20, {255,255,255}), bar_temp, slider_temp, SDL_Rect{ constants::VOLUME_SLIDER_POS.x, constants::VOLUME_SLIDER_POS.y, constants::SLIDER_WIDTH,constants::SLIDER_HEIGHT }, 0, "Master volume");

	//create placeholder textures for music slider
	SDL_Texture* music_tex = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* music_tex_sl = sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 });

	music = new slider(sdlframework::sdl_manager::load_font(fontpath, 20, { 255,255,255 }), music_tex, music_tex_sl, SDL_Rect{ constants::MUSIC_SLIDER_POS.x,constants::MUSIC_SLIDER_POS.y,constants::SLIDER_WIDTH,constants::SLIDER_HEIGHT}, 0, "Music volume");

	//create placeholder texture for sounds slider
	SDL_Texture* sounds_tex = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* sounds_tex_sl = sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 });

	sounds = new slider(sdlframework::sdl_manager::load_font(fontpath, 20, { 255,255,255 }), sounds_tex, sounds_tex_sl, SDL_Rect{ constants::SOUNDS_SLIDER_POS.x, constants::SOUNDS_SLIDER_POS.y, constants::SLIDER_WIDTH,constants::SLIDER_HEIGHT }, 0, "Sounds");

	//create placeholder textures for the checkbox
	SDL_Texture* checked_texture = sdlframework::sdl_manager::create_texture(1, 1, { 0, 255, 0 });
	SDL_Texture* unchecked_texture = sdlframework::sdl_manager::create_texture(1, 1, {255, 0, 0});

	fullscreen = new check_box(checked_texture, unchecked_texture, fontpath, 20, constants::FULLSCREEN_CHECKBOX_POS, "Fullscreen", false);

	SDL_Texture* list_bg = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* selected_bg = sdlframework::sdl_manager::create_texture(1, 1, { 150, 0, 150 });
	std::vector<list_item> res_list;
	//res_list.push_back({ "640x480", "640x480" }); //disabled because my screen doesn't properly support it
	res_list.push_back({ "800x600", "800x600" });
	res_list.push_back({ "1024x768", "1024x768" });
	res_list.push_back({ "1600x900", "1600x900" });
	res_list.push_back({ "1920x1080", "1920x1080" });
	res_list.push_back({ "1920x1200", "1920x1200" });
	
	resolutions = new item_list(fontpath, { 255,255,255 }, list_bg, SDL_Rect{ constants::RESOLUTIONS_LIST_POS.x, constants::RESOLUTIONS_LIST_POS.y, constants::RESOLUTION_LIST_WIDTH, constants::RESOLUTION_LIST_HEIGHT}, selected_bg, res_list);

	load_from_file();
}

void options_menu::draw(SDL_Renderer* renderer)
{
	back.draw(renderer);
	apply.draw(renderer);
	volume->draw(renderer);
	music->draw(renderer);
	fullscreen->draw(renderer);
	sounds->draw(renderer);
	resolutions->draw(renderer);
	if (error_window != nullptr)
		error_window->draw(renderer);
}

/*
	depending on the button clicks updates the screen state and all the elements
*/
void options_menu::update(Mouse mouse)
{
	if (cur_state != state::error)
	{
		back.update(mouse);
		apply.update(mouse);

		if (back.is_clicked())
			cur_state = state::back_pressed;
		if (apply.is_clicked())
		{
			//save_to_file();
			cur_state = state::apply_pressed;
		}

		volume->update(mouse);
		music->update(mouse);
		fullscreen->update(mouse);
		resolutions->update(mouse);
		sounds->update(mouse);
	}
	else
	{
		error_window->update(mouse);
		if (error_window->is_confirmed())
		{
			delete error_window;
			error_window = nullptr;
			cur_state = state::waiting;
		}
	}
}

/*
	Function called from outside of the class if the settings need to be applied and saved
	contains logic for saving the new settings
*/
bool options_menu::apply_settings()
{
	int res_w, res_h = 0;

	std::string res_str = resolutions->get_element_at(resolutions->get_selected()).value;

	//pull resolution values from string
	std::stringstream str;
	str << res_str;

	std::string temp_res;
	getline(str, temp_res, 'x');
	res_w = stoi(temp_res);

	getline(str, temp_res, 'x');
	res_h = stoi(temp_res);

	if (sdlframework::sdl_manager::save_window_changes(res_w, res_h, fullscreen->is_checked()))
	{
		stable_resolution = resolutions->get_selected();
		save_to_file(res_w, res_h);
		constants::setup::init_settings(file_handler::get_launch_config());
		return true;
	}
	else
	{
		error_window = new message_box(sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 }), { constants::setup::WINDOW_WIDTH / 2 - constants::CONFIRM_EXIT_DIALOG_WIDTH/2, constants::setup::WINDOW_HEIGHT / 2  - constants::CONFIRM_EXIT_DIALOG_HEIGHT /2}, "Resolution not supported!", constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
		cur_state = state::error;
		resolutions->set_selected(stable_resolution);
		return false;
	}
	
}

void options_menu::save_to_file(int res_w, int res_h)
{
	//prepare vector for saving settings
	std::vector<std::string> settings;
	std::stringstream buffer;
	buffer << "master_volume " << volume->get_value() << std::endl;
	settings.push_back(buffer.str());
	buffer.str(std::string());

	buffer << "music_volume " << music->get_value() << std::endl;
	settings.push_back(buffer.str());
	buffer.str(std::string());

	buffer << "sounds_volume " << sounds->get_value() << std::endl;
	settings.push_back(buffer.str());
	buffer.str(std::string());

	buffer << "fullscreen " << fullscreen->is_checked() << std::endl;
	settings.push_back(buffer.str());
	buffer.str(std::string());

	buffer << "resolution " << resolutions->get_selected() << std::endl;
	settings.push_back(buffer.str());
	buffer.str(std::string());
	file_handler::save_settings(settings);

	//update launch file as well
	std::stringstream buffer1;
	buffer << res_w << " " << res_h;
	file_handler::save_launch(buffer.str(), fullscreen->is_checked());
}

void options_menu::load_from_file()
{
	//variables that will be saved
	int master, music, sound, fullscr, res = 1;

	std::vector<list_item> settings = file_handler::load_settings();

	for (int i = 0; i < settings.size(); i++)
	{
		if (settings.at(i).display_name == "master_volume")
		{
			master = std::stoi(settings.at(i).value);
		}
		else if (settings.at(i).display_name == "music_volume")
		{
			music = std::stoi(settings.at(i).value);
		}
		else if (settings.at(i).display_name == "sounds_volume")
		{
			sound = std::stoi(settings.at(i).value);
		}
		else if (settings.at(i).display_name == "fullscreen")
		{
			fullscr = std::stoi(settings.at(i).value);
		}
		else if (settings.at(i).display_name == "resolution")
		{
			res = std::stoi(settings.at(i).value);
		}
	}

	volume->set_value(master);
	this->music->set_value(music);
	sounds->set_value(sound);
	fullscreen->set_checked(fullscr);
	resolutions->set_selected(res);

	stable_resolution = res;
}

options_menu::~options_menu()
{
	delete volume;
	delete music;
	delete fullscreen;
	delete resolutions;
	delete sounds;
}
