#pragma once
#include "Button.h"
#include "Slider.h"


class options_menu
{
public:
	enum state 
	{
		waiting,
		back_pressed,
		apply_pressed
	};
private:
	Button back;
	Button apply;
	slider volume;
	state cur_state;
public:
	void draw(SDL_Renderer*);
	void update(Mouse);

	options_menu(SDL_Renderer*);
	~options_menu();
};

