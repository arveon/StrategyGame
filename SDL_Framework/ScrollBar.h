#pragma once
#include <SDL.h>
#include "Button.h"
class scroll_bar
{
private:
	int button_width = 20;

	Button up;
	Button down;

	enum state{
		none,
		move_up,
		move_down,
		percentage_changed
	};
	state cur_state;

	SDL_Texture* bg_texture;
	SDL_Rect draw_rect;
	SDL_Texture* slider_texture;
	SDL_Rect slider_draw_rect;
	
	int num_of_elements;
	float bar_cur_percentage;//current position of bar

	bool is_clicked = true;
public:
	void draw(SDL_Renderer* renderer);
	void update(Mouse mouse, int percentage = 0);

	bool is_up(){ return cur_state == move_up; }
	bool is_down(){ return cur_state == move_down; }
	bool is_percentage_changed(){ return cur_state == percentage_changed; }

	void set_bar_percent(float percentage);
	float get_bar_percent(){ return bar_cur_percentage; }

	void reset(){ cur_state = none; }
	void init();
	void init(SDL_Texture* slider_texture, SDL_Texture* up, SDL_Texture* down, SDL_Rect draw_rect, int num_of_elements, SDL_Texture* bg_texture = nullptr);
	//TODO: add total number of items to init ^
	scroll_bar(){}
	~scroll_bar();
};

