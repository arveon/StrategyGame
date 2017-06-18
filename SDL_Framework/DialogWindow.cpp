#include "DialogWindow.h"


dialog_window::dialog_window(SDL_Texture* bg, SDL_Point window_center, bool is_modal, std::string text, int width, int height)
{
	this->background = bg;

	window.w = width;
	window.h = height;

	window.x = window_center.x;
	window.y = window_center.y;

	this->caption = text;
	TTF_Font* asd = sdlframework::sdl_manager::load_font("assets/fonts/Optimus_Princeps.ttf", 15, { 255, 255, 255 });
	//this->caption_text = TextRenderer::get_texture_from_text(asd, caption, sdlframework::sdl_manager::get_renderer(), { 255, 255, 255 });
}


dialog_window::~dialog_window()
{
}
