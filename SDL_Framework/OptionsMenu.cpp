#include "OptionsMenu.h"

options_menu::options_menu()
{
	//init buttons
	back.init(constants::font_inkedout, "Back", 16);
	back.set_position({ constants::WINDOW_WIDTH - back.get_width() - 20, constants::WINDOW_HEIGHT - back.get_height() - 10 });

	apply.init(constants::font_inkedout, "Apply", 16);
	apply.set_position({ constants::WINDOW_WIDTH - back.get_width() - apply.get_width() - 50, constants::WINDOW_HEIGHT - apply.get_height() - 10 });

	//required for sliders and checkboxes
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_optimus);

	//create placeholder textures for master volume slider
	SDL_Texture* bar_temp = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* slider_temp = sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 });

	volume = new slider(sdlframework::sdl_manager::load_font(fontpath, 20, {255,255,255}), bar_temp, slider_temp, SDL_Rect{ 10,100,300,10 }, 0, "Master volume");

	//create placeholder textures for music slider
	SDL_Texture* music_tex = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* music_tex_sl = sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 });

	music = new slider(sdlframework::sdl_manager::load_font(fontpath, 20, { 255,255,255 }), music_tex, music_tex_sl, SDL_Rect{ 10,150,300,10 }, 0, "Music volume");

	//create placeholder texture for sounds slider
	SDL_Texture* sounds_tex = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* sounds_tex_sl = sdlframework::sdl_manager::create_texture(1, 1, { 255,255,255 });

	sounds = new slider(sdlframework::sdl_manager::load_font(fontpath, 20, { 255,255,255 }), sounds_tex, sounds_tex_sl, SDL_Rect{ 10,200,300,10 }, 0, "Sounds");

	//create placeholder textures for the checkbox
	SDL_Texture* checked_texture = sdlframework::sdl_manager::create_texture(1, 1, { 0, 255, 0 });
	SDL_Texture* unchecked_texture = sdlframework::sdl_manager::create_texture(1, 1, {255, 0, 0});

	fullscreen = new check_box(checked_texture, unchecked_texture, fontpath, 20, {10, 250}, "Fullscreen", false);

	SDL_Texture* list_bg = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	SDL_Texture* selected_bg = sdlframework::sdl_manager::create_texture(1, 1, { 150, 0, 150 });
	std::vector<list_item> res_list;
	res_list.push_back({ "640x480", "640x480" });
	res_list.push_back({ "800x600", "800x600" });
	res_list.push_back({ "1024x768", "1024x768" });
	res_list.push_back({ "1600x900", "1600x900" });
	res_list.push_back({ "1920x1080", "1920x1080" });
	res_list.push_back({ "1920x1200", "1920x1200" });
	
	resolutions = new item_list(fontpath, { 255,255,255 }, list_bg, SDL_Rect{ 10, 350, 150, 100 }, selected_bg, res_list);

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
}

/*
	depending on the button clicks updates the screen state and all the elements
*/
void options_menu::update(Mouse mouse)
{
	back.update(mouse);
	apply.update(mouse);

	if (back.is_clicked())
		cur_state = state::back_pressed;
	if (apply.is_clicked())
	{
		save_to_file();
		cur_state = state::apply_pressed;
	}

	volume->update(mouse);
	music->update(mouse);
	fullscreen->update(mouse);
	resolutions->update(mouse);
	sounds->update(mouse);
}

/*
	Function called from outside of the class if the settings need to be applied and saved
	contains logic for saving the new settings
*/
void options_menu::save()
{
	//TODO: logic for saving settings
}

void options_menu::save_to_file()
{
	int vol_v = volume->get_value();
	int mus_v = music->get_value();
	int sounds_v = sounds->get_value();

	bool fullscr_v = fullscreen->is_checked();
	int res_v = resolutions->get_selected();

	std::ofstream filestr("cfg/settings.cfg");
	if (filestr.good())
	{
		filestr.clear();
		filestr << "master_volume " << vol_v << std::endl;
		filestr << "music_volume " << mus_v << std::endl;
		filestr << "sounds_volume " << sounds_v << std::endl;
		filestr << "fullscreen " << fullscr_v << std::endl;
		filestr << "resolution " << res_v << std::endl;
		filestr.close();
	}
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
