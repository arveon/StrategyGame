#include "ScrollBar.h"

using namespace constants;
/*
	default constructor that just initialises up and down buttons
*/
void scroll_bar::init()
{
	up.init(constants::font_inkedout, "up", { 400, 20 }, 12);
	down.init(constants::font_inkedout, "down", { 400, 420 }, 12);
}

/*
	proper scroll bar initialisation
	@up & down button textures
	@draw_rect element rectangle
	@num_of_elements number of elements in the list, required to calculate percentages properly
	@bg_texture texture under slider, not drawn if not specified
*/
void scroll_bar::init(SDL_Texture* slider_texture, SDL_Texture* up, SDL_Texture* down, SDL_Rect draw_rect, int num_of_elements, int view_size, SDL_Texture* bg_texture)
{
	//set draw rect to exclude are with buttons
	draw_rect.y += draw_rect.w;
	draw_rect.h -= draw_rect.w * 2;

	//rectangle that is used to initialise button positions
	SDL_Rect buttons;
	buttons.x = draw_rect.x;
	buttons.y = draw_rect.y - draw_rect.w;
	buttons.w = draw_rect.w;
	buttons.h = draw_rect.w;

	this->up.init(up, buttons);

	buttons.y = draw_rect.y + draw_rect.h;
	this->down.init(down, buttons);

	slider_draw_rect.w = draw_rect.w;
	slider_draw_rect.x = draw_rect.x;
	slider_draw_rect.y = draw_rect.y;

	this->draw_rect = draw_rect;
	this->num_of_elements = num_of_elements;
	this->bg_texture = bg_texture;
	this->slider_texture = slider_texture;

	if (view_size >= num_of_elements)
		cur_state = state::disabled;

	if (cur_state != state::disabled)
		slider_draw_rect.h = (int)(draw_rect.h * ((float)view_size / num_of_elements));
	else
	{
		this->up.disable();
		this->down.disable();
		slider_draw_rect.h = draw_rect.h;
	}

	//set_bar_percent(1.0f);
}

void scroll_bar::update(Mouse mouse, int percentage)
{
	up.update(mouse);
	down.update(mouse);

	//if disabled, don't update
	if (cur_state == state::disabled)
		return;

	//update state depending on button clicks
	if (down.is_clicked())
		cur_state = move_down;
	else if (up.is_clicked())
		cur_state = move_up;
	else
		cur_state = none;

	//check if slider was clicked
	SDL_Point mouse_point = { mouse.x, mouse.y };
	if (SDL_PointInRect(&mouse_point, &draw_rect) && mouse.lmb_down && !mouse.prev_lmb_down)
		is_clicked = true;
	else if (!mouse.lmb_down)
		is_clicked = false;

	//update slider position and state to percentage_changed so that objects outside can pick it up
	if (is_clicked)
	{
		slider_draw_rect.y = mouse.y - slider_draw_rect.h / 2;
		cur_state = state::percentage_changed;
	}

	//clamp slider to area between up and down buttons
	if (slider_draw_rect.y + slider_draw_rect.h > draw_rect.y + draw_rect.h)
		slider_draw_rect.y = draw_rect.y + draw_rect.h - slider_draw_rect.h;
	else if (slider_draw_rect.y < draw_rect.y)
		slider_draw_rect.y = draw_rect.y;

	//update current percentage if it was changed
	if (cur_state == state::percentage_changed)
		bar_cur_percentage = (float)(slider_draw_rect.y - draw_rect.y) / (draw_rect.h - slider_draw_rect.h); //slider position / maximum slider position wwith point of origin translated to minimum slider position

}

void scroll_bar::draw(SDL_Renderer* renderer)
{
	if (bg_texture != nullptr) { SDL_RenderCopy(renderer, bg_texture, NULL, &draw_rect); }//draw bg_texture if it was set
	SDL_RenderCopy(renderer, slider_texture, NULL, &slider_draw_rect);
	down.draw(renderer);
	up.draw(renderer);
}

/*
	function used to set the new percentage if it's updated from outside
*/
void scroll_bar::set_bar_percent(float percentage)
{
	bar_cur_percentage = percentage;
	slider_draw_rect.y =(int) (percentage * ((float)draw_rect.h - slider_draw_rect.h)) + draw_rect.y; //(percentage * max slider pos) with origin translated to min slider position
}

scroll_bar::~scroll_bar()
{
}
