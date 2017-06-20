#pragma once
#include "DialogWindow.h"
#include "Button.h"

class message_box:dialog_window
{
public:
	enum state {
		waiting,
		confirmed
	};
private:
	SDL_Color text_color;
	state cur_state;
	Button ok;

public:
	message_box(SDL_Texture* bg, SDL_Point window_center, std::string text, int width, int height);

	void update(Mouse mouse);
	void draw(SDL_Renderer* renderer);

	bool is_confirmed() { return cur_state == state::confirmed; }

	~message_box();
};

