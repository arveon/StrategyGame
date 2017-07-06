#pragma once
#include <SDL.h>

#include <vector>

#include "Mouse.h"

#include "Button.h"
#include "ItemList.h"
#include "ListItem.h"

class load_window
{
private:
	Button load;
	Button back;

	item_list saves_list;

	enum state
	{
		loading,
		waiting,
		back_clicked,
		load_clicked
	};
	state cur_state;
public:
	void update(Mouse mouse);
	void draw(SDL_Renderer* renderer);

	bool is_back(){ return cur_state == back_clicked; }
	bool is_load(){ return cur_state == load_clicked; }

	load_window();
	~load_window();
};
