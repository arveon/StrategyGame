#pragma once
#include <SDL.h>
#include "Mouse.h"
#include "TextRenderer.h"

///Class represets a classic UI checkbox
class check_box
{
private:
	enum state 
	{
		None,
		Pressed,
		Hovered,
		Clicked
	};
	state cur_state;
	bool is_box_checked;

	SDL_Texture* box_unchecked;
	SDL_Texture* box_checked;
	SDL_Texture* caption;
	
	SDL_Rect draw_rect;
	SDL_Rect title_draw_rect;

	//is also used as box height
	int box_width = 20;

	void init_draw_rects();
public:
	void draw(SDL_Renderer*);
	void update(Mouse);

	bool is_checked() { return is_box_checked; }
	void set_checked(bool value) { is_box_checked = value; }

	check_box(SDL_Texture* checked_t, SDL_Texture* unchecked_t, TTF_Font* font, SDL_Point position, std::string caption = "default checkbox", bool checked = false);
	check_box(SDL_Texture* checked_t, SDL_Texture* unchecked_t, std::string font_name, int font_size, SDL_Point position, std::string caption = "default checkbox", bool checked = false);

	~check_box();
};

