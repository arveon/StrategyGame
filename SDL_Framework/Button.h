#pragma once
#include <iostream>

#include <SDL.h>
#include "Mouse.h"
#include "Constants.h"
#include "TextRenderer.h"

///Class serves as a representation of the UI button object
///Contains basic button functionality and works for both, image buttons and text buttons
class Button
{
private:
	friend class main_menu;

	//colors used for changing the color of the text button on hover/click/default
	SDL_Color* c_default;
	SDL_Color* c_hovered;
	SDL_Color* c_clicked;

	TTF_Font* font;
	static const int def_fontsize = 20;

	//determines if the button is text or an image
	bool is_icon;
	enum state
	{
		None,
		Hovered,
		Pressed,
		Clicked
	};
	state cur_state;
	
	std::string caption;
	SDL_Texture* image;
	SDL_Rect draw_rect;

	void set_caption_and_coords(std::string caption="");
	void set_default_colors();
public:
	enum type
	{
		exit,
		start,
		load,
		options,
		ok,
		cancel,
		UI
	};
	void init(TTF_Font* font_name, type type);
	void init(TTF_Font* font, type type, SDL_Point coords);
	void init(std::string font_name, type type, int font_size = def_fontsize);
	void init(std::string font_name, type type, SDL_Point coords, int font_size = def_fontsize);
	void init(std::string font_name, int size, type type);
	void init(std::string font_name, std::string caption, int font_size = def_fontsize);
	void init(std::string font_name, std::string caption, SDL_Point position, int font_size = def_fontsize);
	void init(SDL_Texture* texture, SDL_Rect position);

	void update(Mouse mouse);
	void draw(SDL_Renderer*);

	bool is_clicked() { return (cur_state == state::Clicked); }
	bool is_pressed(){ return (cur_state == state::Pressed); }
	void reset_button();

	int get_height() { return draw_rect.h; }
	int get_width() { return draw_rect.w; }

	void set_position(SDL_Point new_pos) { draw_rect.x = new_pos.x; draw_rect.y = new_pos.y; }
	void set_colors(SDL_Color* none, SDL_Color* active, SDL_Color* hovered) { c_default = none; c_hovered = hovered; c_clicked = active; };

	Button();
	~Button();

	type b_type;
};

