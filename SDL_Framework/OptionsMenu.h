#pragma once
#include <fstream>
#include <string>
#include <sstream>

#include <vector>

#include "FileHandler.h"

#include "Button.h"
#include "Slider.h"
#include "CheckBox.h"
#include "ItemList.h"
#include "ListItem.h"

#include "MessageBox.h"

///Class that represents the settings menu of the game
///Will allow player to change game settings
class options_menu
{
public:
	enum state 
	{
		waiting,
		back_pressed,
		apply_pressed,
		error
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

	message_box* error_window = nullptr;

	state cur_state;

	void save_to_file(int res_w, int res_h);
	void load_from_file();
public:
	void draw(SDL_Renderer*);
	void update(Mouse);

	bool is_applied() { return cur_state == apply_pressed; }
	bool is_back_clicked() { return cur_state == back_pressed; }

	bool apply_settings();

	options_menu();
	~options_menu();
};

