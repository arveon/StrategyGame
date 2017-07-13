#include "CheckBox.h"




check_box::check_box(SDL_Texture* checked_texture, SDL_Texture* unchecked_texture, TTF_Font* font, SDL_Point position, std::string caption,  bool checked)
{
	this->box_checked = checked_texture;
	this->box_unchecked = unchecked_texture;
	this->title_draw_rect.x = position.x;
	this->title_draw_rect.y = position.y;
	this->caption = TextRenderer::get_texture_from_text(font, caption, constants::SECONDARY_MENU_SLIDER_COLOR);
	TTF_CloseFont(font);
	this->is_box_checked = checked;
	init_draw_rects();
}

check_box::check_box(SDL_Texture* checked_texture, SDL_Texture* unchecked_texture, std::string font_name, int font_size, SDL_Point position, std::string caption, bool checked)
{
	this->box_checked = checked_texture;
	this->box_unchecked = unchecked_texture;
	this->title_draw_rect.x = position.x;
	this->title_draw_rect.y = position.y;

	TTF_Font* temp = sdlframework::sdl_manager::load_font(font_name, font_size, { 255,255,255 });
	this->caption = TextRenderer::get_texture_from_text(temp, caption, constants::SECONDARY_MENU_SLIDER_COLOR);
	TTF_CloseFont(temp);
	this->is_box_checked = checked;
	init_draw_rects();
}

void check_box::init_draw_rects()
{
	SDL_QueryTexture(caption, NULL, NULL, &title_draw_rect.w, &title_draw_rect.h);

	draw_rect.x = title_draw_rect.x + title_draw_rect.w + 20;
	draw_rect.y = title_draw_rect.y;

	draw_rect.w = draw_rect.h = box_width;
	//SDL_QueryTexture(box_checked, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void check_box::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, caption, NULL, &title_draw_rect);
	
	SDL_Texture* to_draw;
	if (is_box_checked)
		to_draw = box_checked;
	else
		to_draw = box_unchecked;

	SDL_RenderCopy(renderer, to_draw, NULL, &draw_rect);
}

void check_box::update(Mouse mouse)
{
	SDL_Point temp = SDL_Point{ mouse.x, mouse.y };
	if (SDL_PointInRect(&temp, &draw_rect))
	{
		if (mouse.lmb_down && mouse.prev_lmb_down == false)
		{
			cur_state = state::Pressed;
		}
		else if (!mouse.lmb_down && cur_state == state::Pressed)
		{
			cur_state = state::Clicked;
		}
		else if (!mouse.lmb_down)
		{
			cur_state = state::Hovered;
		}
	}
	else
		cur_state = state::None;

	if (cur_state == state::Clicked)
	{
		is_box_checked = !is_box_checked;
		cur_state = state::None;
	}
}

check_box::~check_box()
{
	SDL_DestroyTexture(box_checked);
	SDL_DestroyTexture(box_unchecked);
	SDL_DestroyTexture(caption);
}
