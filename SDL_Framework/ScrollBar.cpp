#include "ScrollBar.h"


void scroll_bar::init()
{
	up.init(constants::font_inkedout, "up", { 400, 20 }, 12);
	down.init(constants::font_inkedout, "down", { 400, 420 }, 12);
}

void scroll_bar::init(SDL_Texture* slider_texture, SDL_Texture* up, SDL_Texture* down, SDL_Rect draw_rect, int num_of_elements, SDL_Texture* bg_texture)
{
	draw_rect.y += draw_rect.w;
	draw_rect.h -= draw_rect.w * 2;

	this->draw_rect = draw_rect;
	this->num_of_elements = num_of_elements;
	this->bg_texture = bg_texture;
	this->slider_texture = slider_texture;
	slider_draw_rect.w = draw_rect.w;
	slider_draw_rect.h = 60;
	slider_draw_rect.x = draw_rect.x;
	slider_draw_rect.y = draw_rect.y;
	
	SDL_Rect buttons;
	buttons.x = draw_rect.x;
	buttons.y = draw_rect.y - draw_rect.w;
	buttons.w = draw_rect.w;
	buttons.h = draw_rect.w;

	this->up.init(up, buttons);

	buttons.y = draw_rect.y + draw_rect.h;
	this->down.init(down, buttons);

	//set_bar_percent(1.0f);
}

void scroll_bar::update(Mouse mouse, int percentage)
{
	up.update(mouse);
	down.update(mouse);

	if (down.is_clicked())
		cur_state = move_down;
	else if (up.is_clicked())
		cur_state = move_up;
	else
		cur_state = none;

	SDL_Point mouse_point = { mouse.x, mouse.y };
	if (SDL_PointInRect(&mouse_point, &draw_rect) && mouse.lmb_down && !mouse.prev_lmb_down)
		is_clicked = true;
	else if (!mouse.lmb_down)
		is_clicked = false;


	if (is_clicked)
	{
		slider_draw_rect.y = mouse.y - slider_draw_rect.h / 2;
		cur_state = state::percentage_changed;
	}

	if (slider_draw_rect.y + slider_draw_rect.h > draw_rect.y + draw_rect.h)
		slider_draw_rect.y = draw_rect.y + draw_rect.h - slider_draw_rect.h;
	else if (slider_draw_rect.y < draw_rect.y)
		slider_draw_rect.y = draw_rect.y;

	if (cur_state == state::percentage_changed)
	{
		bar_cur_percentage = (float)(slider_draw_rect.y - draw_rect.y) / (draw_rect.h - slider_draw_rect.h);
		//std::cout << bar_cur_percentage << std::endl;
	}

}

void scroll_bar::draw(SDL_Renderer* renderer)
{
	if (bg_texture != nullptr) { SDL_RenderCopy(renderer, bg_texture, NULL, &draw_rect); }
	SDL_RenderCopy(renderer, slider_texture, NULL, &slider_draw_rect);
	down.draw(renderer);
	up.draw(renderer);
}

void scroll_bar::set_bar_percent(float percentage)
{
	bar_cur_percentage = percentage;
	slider_draw_rect.y =(int) (percentage * ((float)draw_rect.h - slider_draw_rect.h)) + draw_rect.y;
}

scroll_bar::~scroll_bar()
{
}
