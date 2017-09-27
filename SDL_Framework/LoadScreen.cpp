#include "LoadScreen.h"



load_screen::load_screen()
{
	background = sdlframework::sdl_manager::create_texture(1, 1, { 0,0,0 });
	progress_bar_bg.texture = sdlframework::sdl_manager::create_texture(1, 1, { 150,150,150 });
	progress_bar_bg.draw_rect = { (int)(((float)constants::LOAD_BAR_POS.x) * constants::setup::scaling_horizontal), (int)(((float)constants::LOAD_BAR_POS.y) * constants::setup::scaling_vertical), (int)(((float)constants::LOAD_BAR_SIZE.x) * constants::setup::scaling_horizontal), constants::LOAD_BAR_SIZE.y };

	progress_bar.texture = sdlframework::sdl_manager::create_texture(1, 1, { 20,150,20 });
	progress_bar.draw_rect = progress_bar_bg.draw_rect;
	progress_bar.draw_rect.w = 0;
	text_indicator = new TextRenderer(sdlframework::sdl_manager::load_font(constants::FONTS_PATH + constants::font_optimus, 24, { 255,255,255 }), { 255,255,255 }, "Loading...", constants::LOAD_TEXT_POS.x, constants::LOAD_TEXT_POS.y);
}

void load_screen::update()
{

}

void load_screen::set_percentage(float new_percentage, std::string loaded_item)
{
	text_indicator->change_caption("Loading: " + loaded_item);
	this->percentage = new_percentage;
	progress_bar.draw_rect.w = (int)(((float)progress_bar_bg.draw_rect.w * percentage) + 1);
}

void load_screen::draw(SDL_Renderer* renderer)
{
	SDL_Rect bg = { 0,0,constants::setup::WINDOW_WIDTH, constants::setup::WINDOW_HEIGHT};
	SDL_RenderCopy(renderer, background, NULL, &bg);

	SDL_RenderCopy(renderer, progress_bar_bg.texture, NULL, &progress_bar_bg.draw_rect);
	SDL_RenderCopy(renderer, progress_bar.texture, NULL, &progress_bar.draw_rect);
	text_indicator->draw(renderer);
}

load_screen::~load_screen()
{
	SDL_DestroyTexture(background);
	delete text_indicator;

}
