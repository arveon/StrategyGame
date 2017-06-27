#pragma once
#include "Button.h"
#include "Slider.h"
#include "CheckBox.h"


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
	slider* volume;
	slider* volume2;
	check_box* fullscreen;
	state cur_state;
	SDL_Texture* checked_texture;
public:
	void draw(SDL_Renderer*);
	void update(Mouse);

	bool is_applied() { return cur_state == apply_pressed; }
	bool is_back_clicked() { return cur_state == back_pressed; }

	void save();

	options_menu();
	~options_menu();
};
