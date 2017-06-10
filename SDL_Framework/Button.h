#pragma once
#include <iostream>

#include <SDL.h>
#include "Mouse.h"
#include "Constants.h"

class Button
{
private:
	friend class main_menu;
	enum type
	{
		exit,
		start,
		load,
		options
	};
	type b_type;

	enum state
	{
		None,
		Hovered,
		Pressed,
		Clicked
	};
	state cur_state;
	
	SDL_Texture* image;
	SDL_Rect draw_rect;

	void init(SDL_Texture* img, type type);
	//void set_image(SDL_Texture* image) { this->image = image; }
public:
	void update(Mouse mouse);
	void draw(SDL_Renderer*);

	bool is_clicked() { return (cur_state == state::Clicked); }
	bool is_pressed(){ return (cur_state == state::Pressed); }
	void reset_button() { cur_state = state::None; }
	Button();
	~Button();
};

