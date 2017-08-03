#include "CheckBox.h"

using namespace constants;

#pragma region Constructors
/*
	constructor for when you have font object
	@position - position of the text of the checkbox, checkbox itself will be on the right of it
	@checked - default value
*/
check_box::check_box(SDL_Texture* checked_texture, SDL_Texture* unchecked_texture, TTF_Font* font, SDL_Point position, std::string caption,  bool checked)
{
	this->box_checked = checked_texture;
	this->box_unchecked = unchecked_texture;
	this->title_draw_rect.x = position.x;
	this->title_draw_rect.y = position.y;
	this->caption = TextRenderer::get_texture_from_text(font, caption, SECONDARY_MENU_SLIDER_COLOR);
	TTF_CloseFont(font);
	this->is_box_checked = checked;
	init_draw_rects();
}

/*
	constructor when you have font name and size
	@position - position of the text of the checkbox, checkbox itself will be on the right of it
	@checked - default value
*/
check_box::check_box(SDL_Texture* checked_texture, SDL_Texture* unchecked_texture, std::string font_name, int font_size, SDL_Point position, std::string caption, bool checked)
{
	this->box_checked = checked_texture;
	this->box_unchecked = unchecked_texture;
	this->title_draw_rect.x = position.x;
	this->title_draw_rect.y = position.y;

	TTF_Font* temp = sdlframework::sdl_manager::load_font(font_name, font_size, { 255,255,255 });
	this->caption = TextRenderer::get_texture_from_text(temp, caption, SECONDARY_MENU_SLIDER_COLOR);
	TTF_CloseFont(temp);
	this->is_box_checked = checked;
	init_draw_rects();
}
#pragma endregion

/*
	function used to initialise title rectangle width and height and checkbox draw rectangle
*/
void check_box::init_draw_rects()
{
	SDL_QueryTexture(caption, NULL, NULL, &title_draw_rect.w, &title_draw_rect.h);

#pragma warning(disable:4244)
	title_draw_rect.x *= scaling_horizontal;
	title_draw_rect.y *= scaling_vertical;

	draw_rect.x = (title_draw_rect.x + title_draw_rect.w + 20);
	draw_rect.y = title_draw_rect.y;

	draw_rect.w = draw_rect.h = box_width;
	//SDL_QueryTexture(box_checked, NULL, NULL, &draw_rect.w, &draw_rect.h);
}

void check_box::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, caption, NULL, &title_draw_rect);
	
	//depending on the state draw appropriate texture
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
	{//if mouse over the box, switch the state appropriately to mouse state
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
	else//otherwise, state is none
		cur_state = state::None;

	//if was clicked, reset the state and change the checked/unchecked
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
