#pragma once
#include "Button.h"


class OptionsMenu
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
public:
	void draw(SDL_Renderer*);
	void update(Mouse);

	OptionsMenu(SDL_Renderer*);
	~OptionsMenu();
};

