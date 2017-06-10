#include "TextRenderer.h"


void TextRenderer::draw(SDL_Renderer* renderer)
{
	
	SDL_QueryTexture(text_texture, NULL, NULL, &draw_rect.w, &draw_rect.h);

	SDL_RenderCopy(renderer, text_texture, NULL, &draw_rect);
}

TextRenderer::TextRenderer(TTF_Font* font, SDL_Color color, std::string caption)
{
	this->font = font;
	this->text = caption;
	draw_color = color;
		
	
	draw_rect.x = 0;
	draw_rect.y = 0;
	text_texture = sdlframework::sdl_manager::render_text(sdlframework::sdl_manager::get_renderer(), text, draw_color, font);
}

void TextRenderer::change_caption(std::string new_text)
{
	text = new_text;

	text_texture = sdlframework::sdl_manager::render_text(sdlframework::sdl_manager::get_renderer(), text, draw_color, font);
}

TextRenderer::~TextRenderer()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(text_texture);
}
