#include "Button.h"


void Button::update(Mouse mouse)
{
	if (mouse.x > draw_rect.x && mouse.x < draw_rect.x + draw_rect.w
		&& mouse.y > draw_rect.y && mouse.y < draw_rect.y + draw_rect.h)
	{
		if (mouse.lmb_down)
			cur_state = state::Pressed;
		else if (!mouse.lmb_down && cur_state == state::Pressed)
			cur_state = state::Clicked;
		else
			cur_state = state::Hovered;
	}
	else
		cur_state = state::None;

}

void Button::draw(SDL_Renderer* renderer)
{
}


Button::Button()
{
	draw_rect.w = constants::WINDOW_WIDTH - 100;
	draw_rect.h = constants::WINDOW_HEIGHT;
	draw_rect.x = 0;
	draw_rect.y = 0;
}


Button::~Button()
{
}
