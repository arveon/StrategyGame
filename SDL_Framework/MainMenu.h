#pragma once
#include <SDL.h>

#include "Mouse.h"
#include "Button.h"

class main_menu
{
private:
	SDL_Texture* bg;

	Button start;
	Button load;
	Button options;
	Button exit;

public:
	void init();
	void update(Mouse mouse);
	main_menu();
	~main_menu();
};

