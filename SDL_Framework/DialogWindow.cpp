#include "DialogWindow.h"


dialog_window::dialog_window(SDL_Texture* bg, SDL_Point window_center, bool is_modal, std::string text, int width, int height)
{
	this->background = bg;

	window.w = width;
	window.h = height;

	window.x = window_center.x;
	window.y = window_center.y;

	this->caption = text;

	text_color = SDL_Color{ 0,0,0 };
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_optimus);
	TTF_Font* temp_font = sdlframework::sdl_manager::load_font(fontpath, 20, { 255, 255, 255 });
	caption_text = TextRenderer::get_texture_from_text(temp_font, caption, text_color);
	TTF_CloseFont(temp_font);
}

void dialog_window::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, background, NULL, &window);
	SDL_Rect temp;
	SDL_QueryTexture(caption_text, NULL, NULL, &temp.w, &temp.h);
	temp.x = window.x;
	temp.y = window.y + temp.h / 2;

	SDL_RenderCopy(renderer, caption_text, NULL, &temp);
}


dialog_window::~dialog_window()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(caption_text);
}
