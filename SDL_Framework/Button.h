#pragma once
#include <iostream>

#include <SDL.h>
#include "Mouse.h"
#include "Constants.h"
#include "TextRenderer.h"

class Button
{
private:
	friend class main_menu;

	SDL_Color* c_default;
	SDL_Color* c_hovered;
	SDL_Color* c_clicked;

	TTF_Font* font;

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

	
	//void set_image(SDL_Texture* image) { this->image = image; }
public:
	enum type
	{
		exit,
		start,
		load,
		options,
		ok,
		cancel
	};
	void init(TTF_Font* font_name, type type);
	void init(TTF_Font* font_name, type type, SDL_Point coords);
	void init(std::string font_name, type type);
	void init(std::string font_name, type type, SDL_Point coords);
	void update(Mouse mouse);
	void draw(SDL_Renderer*);

	bool is_clicked() { return (cur_state == state::Clicked); }
	bool is_pressed(){ return (cur_state == state::Pressed); }
	void reset_button() { cur_state = state::None; }

	Button();
	~Button();

	type b_type;
};

