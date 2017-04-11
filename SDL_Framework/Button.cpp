#include "Button.h"


void Button::init(SDL_Texture* img, type t)
{
	std::cout << image << std::endl;
	this->image = img; 
	this->b_type = t; 
	draw_rect.w = constants::BUTTON_WIDTH;
	draw_rect.h = constants::BUTTON_HEIGHT;
	
	switch(b_type)
	{
	case type::start:
			draw_rect.x = constants::START_X;
			draw_rect.y = constants::START_Y;
			break;
	case type::load:
		draw_rect.x = constants::LOAD_X;
		draw_rect.y = constants::LOAD_Y;
		break;
	case type::options:
		draw_rect.x = constants::OPTIONS_X;
		draw_rect.y = constants::OPTIONS_Y;
		break;
	case type::exit:
		draw_rect.x = constants::EXIT_X;
		draw_rect.y = constants::EXIT_Y;
		break;
	}
}

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
	//std::cout << image << " " << renderer << std::endl;
	SDL_RenderCopy(renderer, image, NULL, &draw_rect);
}


Button::Button()
{
}


Button::~Button()
{
}
