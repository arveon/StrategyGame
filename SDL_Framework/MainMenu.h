#pragma once
#include <SDL.h>

#include "Mouse.h"
#include "Button.h"
#include "sdl_manager.h"
#include "TextRenderer.h"
#include "ConfirmDialog.h"
#include "MessageBox.h"
#include "OptionsMenu.h"
#include "LoadWindow.h"

class main_menu
{
private:
	SDL_Texture* bg;

	TTF_Font* font;
	TextRenderer* display;

	Button start;
	Button load;
	Button options;
	Button exit;

	confirm_dialog* exit_confirmation = nullptr;
	message_box* msg_box = nullptr;
	options_menu* options_window = nullptr;
	load_window* load_game_window = nullptr;

public:
	enum state
	{
		waiting,
		start_clicked,
		load_clicked,
		options_clicked,
		exit_clicked,
		exit_confirmed
	};
	state cur_state;

	void init();
	void update(Mouse mouse);
	void draw(SDL_Renderer*);
	main_menu();
	~main_menu();
};

