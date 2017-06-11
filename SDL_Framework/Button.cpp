#include "Button.h"


void Button::init(TTF_Font* fontname, type type)
{
	c_default = new SDL_Color{ 255, 155, 155 };
	c_hovered = new SDL_Color{ 255, 255, 155 };
	c_clicked = new SDL_Color{ 255, 100, 100 };


	std::cout << image << std::endl;
	this->font = fontname;

	switch (type)
	{
	case type::start:
		caption = "New game";
		break;
	case type::load:
		caption = "Load game";
		break;
	case type::options:
		caption = "Settings";
		break;
	case type::exit:
		caption = "Exit";
		break;
	case type::cancel:
		caption = "Cancel";
		break;
	case type::ok:
		caption = "Ok";
		break;
	}
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), {255,155,155});

	this->b_type = type; 
	//draw_rect.w = constants::BUTTON_WIDTH;
	//draw_rect.h = constants::BUTTON_HEIGHT;

	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
	
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
	default:
		draw_rect.x = 0;
		draw_rect.y = 0;
	}
}

void Button::init(std::string fontname, type type)
{
	c_default = new SDL_Color{ 255, 155, 155 };
	c_hovered = new SDL_Color{ 255, 255, 155 };
	c_clicked = new SDL_Color{ 255, 100, 100 };


	std::cout << image << std::endl;
	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + fontname, 16, { 255, 255, 255 });
	switch (type)
	{
	case type::start:
		caption = "New game";
		break;
	case type::load:
		caption = "Load game";
		break;
	case type::options:
		caption = "Settings";
		break;
	case type::exit:
		caption = "Exit";
		break;
	case type::cancel:
		caption = "Cancel";
		break;
	case type::ok:
		caption = "Ok";
		break;
	}
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), { 255, 155, 155 });

	this->b_type = type;
	//draw_rect.w = constants::BUTTON_WIDTH;
	//draw_rect.h = constants::BUTTON_HEIGHT;

	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);

	switch (b_type)
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
	default:
		draw_rect.x = 0;
		draw_rect.y = 0;
	}
}


void Button::init(std::string font_name, type type, SDL_Point coords)
{
	c_default = new SDL_Color{ 255, 155, 155 };
	c_hovered = new SDL_Color{ 255, 255, 155 };
	c_clicked = new SDL_Color{ 255, 100, 100 };

	std::cout << image << std::endl;
	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, 16, { 255, 255, 255 });
	switch (type)
	{
	case type::start:
		caption = "New game";
		break;
	case type::load:
		caption = "Load game";
		break;
	case type::options:
		caption = "Settings";
		break;
	case type::exit:
		caption = "Exit";
		break;
	case type::cancel:
		caption = "Cancel";
		break;
	case type::ok:
		caption = "Ok";
		break;
	}
	this->image = TextRenderer::get_texture_from_text(font, caption, sdlframework::sdl_manager::get_renderer(), { 255, 155, 155 });

	this->b_type = type;

	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);

	draw_rect.x = coords.x;
	draw_rect.y = coords.y;
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
