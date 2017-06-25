#include "OptionsMenu.h"



options_menu::options_menu(SDL_Renderer* renderer)
{
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_inkedout);
	back.init(constants::font_inkedout, "Back", SDL_Point{200,0});
	apply.init(constants::font_inkedout, "Apply");

	SDL_Texture* bar_temp = sdlframework::sdl_manager::create_texture(100, 10, { 150,150,150 });
	SDL_Texture* slider_temp = sdlframework::sdl_manager::create_texture(20, 30, { 255,255,255 });
	volume = slider(renderer, sdlframework::sdl_manager::load_font(fontpath, 10, {255,255,255}), bar_temp, slider_temp, SDL_Rect{ 10,100,100,10 });
}

void options_menu::draw(SDL_Renderer* renderer)
{
	back.draw(renderer);
	apply.draw(renderer);
	volume.draw(renderer);
}

void options_menu::update(Mouse mouse)
{
	back.update(mouse);
	apply.update(mouse);

	if (back.is_clicked())
		cur_state = state::back_pressed;
	if (apply.is_clicked())
		cur_state = state::apply_pressed;
}


options_menu::~options_menu()
{
}
