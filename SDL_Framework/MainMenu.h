#pragma once
#include <SDL.h>

#include "Mouse.h"
#include "Button.h"
#include "sdl_manager.h"

class main_menu
{
private:
	SDL_Texture* bg;

	Button start;
	Button load;
	Button options;
	Button exit;

public:
	enum state
	{
		waiting,
		start_clicked,
		load_clicked,
		options_clicked,
		exit_clicked
	};
	state cur_state;

	void init();
	void update(Mouse mouse);
	void draw(SDL_Renderer*);
	main_menu();
	~main_menu();
};

