#include "Button.h"

#pragma region Initialisation
void Button::init(TTF_Font* font, type type)
{
	set_default_colors();

	this->font = font;
	this->b_type = type; 
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(this->font, caption, *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void Button::init(TTF_Font * font, type type, SDL_Point coords)
{
	set_default_colors();

	this->font = font;
	this->b_type = type;
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
	draw_rect.x = coords.x;
	draw_rect.y = coords.y;
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void Button::init(std::string font_name, type type, int font_size)
{
	set_default_colors();

	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, font_size, *c_default);
	
	this->b_type = type;

	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}


void Button::init(std::string font_name, type type, SDL_Point init_coords, int font_size)
{
	set_default_colors();
	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, font_size, *c_default);
	this->b_type = type;
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
	draw_rect.x = init_coords.x;
	draw_rect.y = init_coords.y;
}

void Button::init(std::string font_name,int font_size, type type)
{
	set_default_colors();

	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, font_size, *c_default);
	this->b_type = type;
	set_caption_and_coords();
	this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void Button::init(std::string font_name, std::string caption, int font_size)
{
	set_default_colors();
	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, font_size, *c_default);
	this->b_type = type::UI;
	set_caption_and_coords(caption);
	this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);
	draw_rect.x = 0;
	draw_rect.y = 0;
}

void Button::init(std::string font_name, std::string caption, SDL_Point position, int font_size)
{
	set_default_colors();
	this->font = sdlframework::sdl_manager::load_font("assets/fonts/" + font_name, def_fontsize, *c_default);
	this->b_type = type::UI;
	set_caption_and_coords(caption);
	this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
	SDL_QueryTexture(image, NULL, NULL, &draw_rect.w, &draw_rect.h);

	draw_rect.x = position.x;
	draw_rect.y = position.y;
}

void Button::init(SDL_Texture* texture, SDL_Rect position)
{
	image = texture;
	draw_rect = position;
}

void Button::set_default_colors()
{
	c_default = new SDL_Color{ 255, 0, 0 };
	c_hovered = new SDL_Color{ 0, 255, 0 };
	c_clicked = new SDL_Color{ 0, 0, 255 };
}

void Button::set_caption_and_coords(std::string caption)
{
	is_icon = false;
	switch (b_type)
	{
	case type::start:
		this->caption = "New game";
		draw_rect.x = constants::START_X;
		draw_rect.y = constants::START_Y;
		break;
	case type::load:
		this->caption = "Load game";
		draw_rect.x = constants::LOAD_X;
		draw_rect.y = constants::LOAD_Y;
		break;
	case type::options:
		this->caption = "Settings";
		draw_rect.x = constants::OPTIONS_X;
		draw_rect.y = constants::OPTIONS_Y;
		break;
	case type::exit:
		this->caption = "Exit";
		draw_rect.x = constants::EXIT_X;
		draw_rect.y = constants::EXIT_Y;
		break;
	case type::cancel:
		this->caption = "Cancel";
		break;
	case type::ok:
		this->caption = "Ok";
		break;
	case type::UI:
		this->caption = caption;
		draw_rect.x = 0;
		draw_rect.y = 0;
	default:
		this->caption = caption;
		draw_rect.x = 0;
		draw_rect.y = 0;
	}
}
#pragma endregion

void Button::update(Mouse mouse)
{
	if (mouse.x > draw_rect.x && mouse.x < draw_rect.x + draw_rect.w
		&& mouse.y > draw_rect.y && mouse.y < draw_rect.y + draw_rect.h)
	{
		if (mouse.lmb_down && !mouse.prev_lmb_down)
		{
			if (cur_state != Pressed)
			{
				if (!is_icon)
				{
					SDL_DestroyTexture(this->image);
					this->image = TextRenderer::get_texture_from_text(font, caption, *c_clicked);
				}
			}
			cur_state = state::Pressed;
		}
		else if (!mouse.lmb_down && cur_state == state::Pressed)
		{
			cur_state = state::Clicked;
		}
		else if(!mouse.lmb_down)
		{
			if (cur_state != Hovered)
			{
				if (!is_icon)
				{
					SDL_DestroyTexture(this->image);
					this->image = TextRenderer::get_texture_from_text(font, caption, *c_hovered);
				}
			}
			cur_state = state::Hovered;
		}
	}
	else
	{
		if (cur_state != None)
		{
			if (!is_icon)
			{
				SDL_DestroyTexture(this->image);
				this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
			}
		}
		cur_state = state::None;
	}
}

void Button::reset_button()
{
	cur_state = state::None;
	if (!is_icon)
	{
		SDL_DestroyTexture(this->image);
		this->image = TextRenderer::get_texture_from_text(font, caption, *c_default);
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
	/*SDL_DestroyTexture(image);
	TTF_CloseFont(font);*/
}
