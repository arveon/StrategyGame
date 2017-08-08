#pragma once
#include <fstream>
#include <string>
#include <sstream>

#include <vector>

#include "Button.h"
#include "Slider.h"
#include "CheckBox.h"
#include "ItemList.h"
#include "ListItem.h"

///Class that represents the settings menu of the game
///Will allow player to change game settings
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

	//TODO: replace options elements with stuff that is actually required
	slider* volume;
	slider* music;
	slider* sounds;
	check_box* fullscreen;
	item_list* resolutions;

	state cur_state;

	void save_to_file();
	void load_from_file();
public:
	void draw(SDL_Renderer*);
	void update(Mouse);

	bool is_applied() { return cur_state == apply_pressed; }
	bool is_back_clicked() { return cur_state == back_pressed; }

	void apply_settings();

	options_menu();
	~options_menu();
};

