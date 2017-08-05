#include "MessageBox.h"

message_box::message_box(SDL_Texture* bg, SDL_Point window_coords, std::string text, int width, int height):dialog_window(bg, window_coords,true ,text, width, height)
{
	cur_state = state::waiting;
	ok.scaling = false;
	ok.init(constants::font_optimus, Button::type::ok);
	ok.set_position({window_coords.x + constants::CONFIRM_EXIT_DIALOG_WIDTH/2 - ok.get_width()/2, window_coords.y + constants::CONFIRM_EXIT_DIALOG_HEIGHT - ok.get_height() - 10});
}

void message_box::update(Mouse mouse)
{
	ok.update(mouse);

	if (ok.is_clicked())
		cur_state = state::confirmed;
}

void message_box::draw(SDL_Renderer* renderer)
{
	dialog_window::draw(renderer);
	ok.draw(renderer);
}

message_box::~message_box()
{
	
}
