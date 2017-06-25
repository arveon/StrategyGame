#include "Slider.h"

#pragma region Initialisation
slider::slider()
{
}
slider::slider(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture * bar, SDL_Texture* slider, SDL_Rect draw_rect, int value, std::string title)
{
	this->element_draw_rect = draw_rect;
	this->bar_texture = bar;
	this->slider_texture = slider;
	this->slider_draw_rect = draw_rect;
	SDL_QueryTexture(slider, NULL, NULL, &slider_draw_rect.w, &slider_draw_rect.h);
	slider_draw_rect.y = slider_draw_rect.y - slider_draw_rect.h / 2 + element_draw_rect.h / 2;
	cur_value = value;
	init_title(renderer, font, title);
}

slider::slider(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture * bar, SDL_Texture * slider, int w, int h, int x, int y, int value, std::string title)
{
	this->bar_texture = bar;
	this->slider_texture = slider;
	this->element_draw_rect = SDL_Rect{ x,y,w,h };
	slider_draw_rect = SDL_Rect{ x,y,0,0 };
	SDL_QueryTexture(slider, NULL, NULL, &slider_draw_rect.w, &slider_draw_rect.h);
	slider_draw_rect.y = slider_draw_rect.y - slider_draw_rect.h / 2 + element_draw_rect.h / 2;
	cur_value = value;
	init_title(renderer, font, title);
}

slider::slider(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture * bar, SDL_Texture * slider, int w, int h, SDL_Point pos, int value, std::string title)
{
	this->bar_texture = bar;
	this->slider_texture = slider;
	this->element_draw_rect = SDL_Rect{ pos.x, pos.y, w, h };
	SDL_QueryTexture(slider, NULL, NULL, &slider_draw_rect.w, &slider_draw_rect.h);
	slider_draw_rect.y = slider_draw_rect.y - slider_draw_rect.h / 2 + element_draw_rect.h / 2;
	this->cur_value = value;
	init_title(renderer, font, title);
}

void slider::init_title(SDL_Renderer* renderer, TTF_Font* font, std::string title)
{
	this->title_texture = TextRenderer::get_texture_from_text(font, title, renderer, constants::SECONDARY_MENU_SLIDER_COLOR);
	this->title_draw_rect = element_draw_rect;
	title_draw_rect.y -= 50;
	SDL_QueryTexture(title_texture, NULL, NULL, &title_draw_rect.w, &title_draw_rect.h);
}
#pragma endregion


void update(Mouse mouse)
{

}

void slider::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, title_texture, NULL, &title_draw_rect);
	SDL_RenderCopy(renderer, bar_texture, NULL, &element_draw_rect);
	SDL_RenderCopy(renderer, slider_texture, NULL, &slider_draw_rect);
}

slider::~slider()
{
}
