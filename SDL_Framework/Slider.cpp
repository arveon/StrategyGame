#include "Slider.h"

#pragma region Initialisation
slider::slider()
{
}
/*
	constructors that accept the size and position in different formats
*/

slider::slider(TTF_Font* font, SDL_Texture * bar, SDL_Texture* slider, SDL_Rect draw_rect, int value, std::string title)
{
	this->element_draw_rect = draw_rect;
	this->bar_texture = bar;
	this->slider_texture = slider;
	this->slider_draw_rect = draw_rect;
	slider_draw_rect.w = slider_width;
	slider_draw_rect.h = slider_height;

	//SDL_QueryTexture(slider, NULL, NULL, &slider_draw_rect.w, &slider_draw_rect.h);
	slider_draw_rect.y = slider_draw_rect.y - slider_draw_rect.h / 2 + element_draw_rect.h / 2;
	cur_value = value;
	init_title(font, title);
}

slider::slider(TTF_Font* font, SDL_Texture * bar, SDL_Texture * slider, int w, int h, int x, int y, int value, std::string title)
{
	this->bar_texture = bar;
	this->slider_texture = slider;
	this->element_draw_rect = SDL_Rect{ x,y,w-50,h };
	slider_draw_rect = SDL_Rect{ x,y,slider_width,slider_height };
	slider_draw_rect.y = slider_draw_rect.y - slider_draw_rect.h / 2 + element_draw_rect.h / 2;
	cur_value = value;
	init_title(font, title);
}

slider::slider(TTF_Font* font, SDL_Texture * bar, SDL_Texture * slider, int w, int h, SDL_Point pos, int value, std::string title)
{
	this->bar_texture = bar;
	this->slider_texture = slider;
	this->element_draw_rect = SDL_Rect{ pos.x, pos.y, w, h };
	slider_draw_rect.w = slider_width;
	slider_draw_rect.h = slider_height;
	slider_draw_rect.y = slider_draw_rect.y - slider_draw_rect.h / 2 + element_draw_rect.h / 2;
	this->cur_value = value;
	init_title(font, title);
}

/*
function that initialises the title, its texture and rectangle
also initialises the value of the slider and the position of it
used to dump the code that would otherwise be duplicated in all of the constructors
*/
void slider::init_title(TTF_Font* font, std::string title)
{
	this->font = font;

	//init title
	this->title_texture = TextRenderer::get_texture_from_text(font, title, constants::SECONDARY_MENU_SLIDER_COLOR);
	this->title_draw_rect = element_draw_rect;
	title_draw_rect.y -= 50;
	SDL_QueryTexture(title_texture, NULL, NULL, &title_draw_rect.w, &title_draw_rect.h);

	//init value
	this->value_texture = TextRenderer::get_texture_from_text(font, std::to_string(cur_value), constants::SECONDARY_MENU_SLIDER_COLOR);
	this->value_draw_rect = SDL_Rect{ element_draw_rect.x + element_draw_rect.w + 15, element_draw_rect.y, 0, 0 };
	SDL_QueryTexture(value_texture, NULL, NULL, &value_draw_rect.w, &value_draw_rect.h);
	value_draw_rect.y -= value_draw_rect.h / 2;

	prev_value = -1;
	is_pressed = false;
}
#pragma endregion


void slider::update(Mouse mouse)
{
	//set state of slider depending on the mouse
	SDL_Point mousepoint = { mouse.x, mouse.y };
	if ((SDL_PointInRect(&mousepoint, &slider_draw_rect) || SDL_PointInRect(&mousepoint, &element_draw_rect)) && mouse.lmb_down && !mouse.prev_lmb_down)
		is_pressed = true;
	else if (!mouse.lmb_down)
		is_pressed = false;

	//if clicked, make it follow the mouse
	if (is_pressed)
	{
		slider_draw_rect.x = mouse.x - slider_draw_rect.w / 2;
		
		//if slider is too far to the right/left, clamp it to size of bar
		if (slider_draw_rect.x + slider_draw_rect.w > element_draw_rect.x + element_draw_rect.w)
			slider_draw_rect.x = element_draw_rect.x + element_draw_rect.w - slider_draw_rect.w;
		if (slider_draw_rect.x < element_draw_rect.x)
			slider_draw_rect.x = element_draw_rect.x;

		//set appropriate value (in %)
		cur_value =(int) ((float)(slider_draw_rect.x - element_draw_rect.x) / (element_draw_rect.w - slider_draw_rect.w) * 100);
		if (prev_value != cur_value)
		{
			//change value indicator
			SDL_DestroyTexture(value_texture);
			value_texture = nullptr;
			value_texture = TextRenderer::get_texture_from_text(font, std::to_string(cur_value), constants::SECONDARY_MENU_SLIDER_COLOR);
			SDL_QueryTexture(value_texture, NULL, NULL, &value_draw_rect.w, nullptr);
		}

		prev_value = cur_value;
	}
}

void slider::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, title_texture, NULL, &title_draw_rect);
	SDL_RenderCopy(renderer, bar_texture, NULL, &element_draw_rect);
	SDL_RenderCopy(renderer, slider_texture, NULL, &slider_draw_rect);
	SDL_RenderCopy(renderer, value_texture, NULL, &value_draw_rect);
}

slider::~slider()
{
	SDL_DestroyTexture(bar_texture);
	SDL_DestroyTexture(title_texture);
	SDL_DestroyTexture(slider_texture);
	SDL_DestroyTexture(value_texture);

	TTF_CloseFont(font);
}
