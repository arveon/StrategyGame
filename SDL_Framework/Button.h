#pragma once
#include <iostream>

#include <SDL.h>
#include "Mouse.h"
#include "Constants.h"

class Button
{
private:
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

public:
	void update(Mouse mouse);
	void draw(SDL_Renderer*);

	bool is_clicked() { return cur_state == state::Clicked; }
	bool reset_button() { cur_state == state::None; }
	Button();
	~Button();
};

