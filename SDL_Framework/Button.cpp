#include "Button.h"


void Button::init(TTF_Font* font, type type)
{
	set_default_colors();

	this->font = font;
	this->b_type = type; 
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(this->font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void Button::init(TTF_Font * font, type type, SDL_Point coords)
{
	set_default_colors();

	this->font = font;
	this->b_type = type;
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
	draw_rect.x = coords.x;
	draw_rect.y = coords.y;
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void Button::init(std::string font_name, type type)
{
	set_default_colors();

	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, fontsize, *c_default);
	
	this->b_type = type;

	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}


void Button::init(std::string font_name, type type, SDL_Point init_coords)
{
	set_default_colors();
	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, fontsize, *c_default);
	this->b_type = type;
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
	draw_rect.x = init_coords.x;
	draw_rect.y = init_coords.y;
}

void Button::init(std::string font_name,int size, type type)
{
	set_default_colors();

	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, size, *c_default);
	this->b_type = type;
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void Button::set_default_colors()
{
	c_default = new SDL_Color{ 255, 0, 0 };
	c_hovered = new SDL_Color{ 0, 255, 0 };
	c_clicked = new SDL_Color{ 0, 0, 255 };
}

void Button::set_caption_and_coords()
{
	switch (b_type)
	{
	case type::start:
		caption = "New game";
		draw_rect.x = constants::START_X;
		draw_rect.y = constants::START_Y;
		break;
	case type::load:
		caption = "Load game";
		draw_rect.x = constants::LOAD_X;
		draw_rect.y = constants::LOAD_Y;
		break;
	case type::options:
		caption = "Settings";
		draw_rect.x = constants::OPTIONS_X;
		draw_rect.y = constants::OPTIONS_Y;
		break;
	case type::exit:
		caption = "Exit";
		draw_rect.x = constants::EXIT_X;
		draw_rect.y = constants::EXIT_Y;
		break;
	case type::cancel:
		caption = "Cancel";
		break;
	case type::ok:
		caption = "Ok";
		break;
	default:
		draw_rect.x = 0;
		draw_rect.y = 0;
	}
}

void Button::update(Mouse mouse)
{
	if (mouse.x > draw_rect.x && mouse.x < draw_rect.x + draw_rect.w
		&& mouse.y > draw_rect.y && mouse.y < draw_rect.y + draw_rect.h)
	{
		if (mouse.lmb_down)
		{
			if (cur_state != Pressed)
			{
				SDL_DestroyTexture(this->image);
				this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_clicked);
			}
			cur_state = state::Pressed;
		}
		else if (!mouse.lmb_down && cur_state == state::Pressed)
			cur_state = state::Clicked;
		else
		{
			if (cur_state != Hovered)
			{
				SDL_DestroyTexture(this->image);
				this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(),	*c_hovered);
			}
			cur_state = state::Hovered;
		}
	}
	else
	{
		if (cur_state != None)
		{
			SDL_DestroyTexture(this->image);
			this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
		}
		cur_state = state::None;
	}

}

void Button::reset_button()
{
	cur_state = state::None;
	SDL_DestroyTexture(this->image);
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), *c_default);
}

void Button::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, NULL, &draw_rect);

	
}


Button::Button()
{
}


Button::~Button()
{
	TTF_CloseFont(font);
}
