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
	res_list.push_back({ "640x480", "640x480" });
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
	//TODO: logic for saving settings
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

	std::cout << res_w << " " << res_h << std::endl;

	if (sdlframework::sdl_manager::save_window_changes(res_w, res_h, fullscreen->is_checked()))
	{
		save_to_file(res_w, res_h);
		constants::setup::init_settings(file_handler::get_launch_config());
		return true;
	}
	else
	{
		error_window = new message_box(sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 }), { constants::setup::WINDOW_WIDTH / 2 - constants::CONFIRM_EXIT_DIALOG_WIDTH/2, constants::setup::WINDOW_HEIGHT / 2  - constants::CONFIRM_EXIT_DIALOG_HEIGHT /2}, "Resolution not supported!", constants::CONFIRM_EXIT_DIALOG_WIDTH, constants::CONFIRM_EXIT_DIALOG_HEIGHT);
		cur_state = state::error;
		return false;
	}
	
}

void options_menu::save_to_file(int res_w, int res_h)
{
	//TODO: add checks for whether the file exists
	//save settings into a settings file
	std::ofstream filestr("cfg/settings.cfg");
	if (filestr.good())
	{
		filestr.clear();
		filestr << "master_volume " << volume->get_value() << std::endl;
		filestr << "music_volume " << music->get_value() << std::endl;
		filestr << "sounds_volume " << sounds->get_value() << std::endl;
		filestr << "fullscreen " << fullscreen->is_checked() << std::endl;
		filestr << "resolution " << resolutions->get_selected() << std::endl;
		filestr.close();
	}

	//CONFIG FILE CHANGES
	//replace resolution and fullscreen entries in launch.cfg 
	std::ifstream launch_ifilestr("cfg/launch.cfg");
	bool found;
	std::string line;
	std::vector<std::string> lines;
	int i = 0;
	int res_id, fs_id = -1;
	//store lines from file in a temp vector and find line numbers for resolution and fullscreen settings
	while (getline(launch_ifilestr, line))
	{
		std::cout << line << std::endl;
		lines.push_back(line);
		if (line.find("resolution ") != std::string::npos)
			res_id = i;
		else if (line.find("fullscreen ") != std::string::npos)
			fs_id = i;
		i++;
	}
	launch_ifilestr.close();

	//replace resolution line in the vector containing all file lines
	if (res_id == -1)
		return;
	std::stringstream buffer;
	buffer << "resolution " << res_w << " " << res_h << std::endl;
	getline(buffer, lines.at(res_id));

	//replace fullscreen line in the vector containing all file lines
	if (fs_id == -1)
		return;
	std::stringstream buffer2;
	buffer << "fullscreen " << fullscreen->is_checked() << std::endl;
	getline(buffer, lines.at(fs_id));

	//replace contents of file with the edited version
	std::ofstream launch_ofilestr("cfg/launch.cfg");
	for (int i = 0; i < lines.size(); i++)
	{
		launch_ofilestr << lines.at(i) << std::endl;
	}
	launch_ofilestr.close();
}

void options_menu::load_from_file()
{
	int master, music, sound, fullscr, res;

	std::ifstream filestr("cfg/settings.cfg");

	std::string line;
	while (getline(filestr, line))
	{
		std::string temp = "";
		std::stringstream str_buffer;
		str_buffer << line;
		getline(str_buffer, temp, ' ');
		
		if (temp == "master_volume")
		{
			getline(str_buffer, temp);
			master = std::stoi(temp);
		}
		else if (temp == "music_volume")
		{
			getline(str_buffer, temp);
			music = std::stoi(temp);
		}
		else if (temp == "sounds_volume")
		{
			getline(str_buffer, temp);
			sound = std::stoi(temp);
		}
		else if (temp == "fullscreen")
		{
			getline(str_buffer, temp);
			fullscr = std::stoi(temp);
		}
		else if (temp == "resolution")
		{
			getline(str_buffer, temp);
			res = std::stoi(temp);
		}
	}

	volume->set_value(master);
	this->music->set_value(music);
	sounds->set_value(sound);
	fullscreen->set_checked(fullscr);
	resolutions->set_selected(res);

}

options_menu::~options_menu()
{
	delete volume;
	delete music;
	delete fullscreen;
	delete resolutions;
	delete sounds;
}
