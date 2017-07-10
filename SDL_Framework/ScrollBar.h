#pragma once
#include <SDL.h>
#include "Button.h"
class scroll_bar
{
private:
	Button up;
	Button down;

	enum state{
		none,
		move_up,
		move_down
	};
	state cur_state;

public:
	void draw(SDL_Renderer* renderer);
	void update(Mouse mouse);

	bool is_up(){ return cur_state == move_up; }
	bool is_down(){ return cur_state == move_down; }

	void reset(){ cur_state = none; }
	scroll_bar();
	~scroll_bar();
};

