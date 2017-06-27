#include "OptionsMenu.h"

options_menu::options_menu()
{
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_inkedout);
	back.init(constants::font_inkedout, "Back", 16);
	back.set_position({ constants::WINDOW_WIDTH - back.get_width() - 20, constants::WINDOW_HEIGHT - back.get_height() - 10 });

	apply.init(constants::font_inkedout, "Apply", 16);
	apply.set_position({ constants::WINDOW_WIDTH - back.get_width() - apply.get_width() - 50, constants::WINDOW_HEIGHT - apply.get_height() - 10 });

	SDL_Texture* bar_temp = sdlframework::sdl_manager::create_texture(100, 10, { 150,150,150 });
	SDL_Texture* slider_temp = sdlframework::sdl_manager::create_texture(10, 30, { 255,255,255 });
	volume = new slider(sdlframework::sdl_manager::load_font(fontpath, 10, {255,255,255}), bar_temp, slider_temp, SDL_Rect{ 10,100,300,10 }, 0, "Volume");

	SDL_Texture* bar_temp1 = sdlframework::sdl_manager::create_texture(100, 10, { 150,150,150 });
	SDL_Texture* slider_temp1 = sdlframework::sdl_manager::create_texture(10, 30, { 255,255,255 });
	volume2 = new slider(sdlframework::sdl_manager::load_font(fontpath, 10, { 255,255,255 }), bar_temp1, slider_temp1, SDL_Rect{ 10,200,300,10 }, 0, "Volume2");
}

void options_menu::draw(SDL_Renderer* renderer)
{
	back.draw(renderer);
	apply.draw(renderer);
	volume->draw(renderer);
	volume2->draw(renderer);
}

void options_menu::update(Mouse mouse)
{
	back.update(mouse);
	apply.update(mouse);

	if (back.is_clicked())
		cur_state = state::back_pressed;
	if (apply.is_clicked())
		cur_state = state::apply_pressed;

	volume->update(mouse);
	volume2->update(mouse);
}

void options_menu::save()
{
	//TODO: logic for saving settings
}


options_menu::~options_menu()
{
	delete volume;
	delete volume2;
}
