#include "ConfirmDialog.h"


confirm_dialog::confirm_dialog(SDL_Texture* bg, SDL_Point window_coords, std::string text, int width, int height) : dialog_window(bg, window_coords, true, text, width, height)
{
	cur_state = dialog_state::Waiting;
	yes.init(constants::font_optimus, Button::ok, {0 , 0});
	no.init(constants::font_optimus, Button::cancel, {0 , 0});

	yes.set_position({ window_coords.x + width - no.get_width() - yes.get_width() - 30, window_coords.y + height - yes.get_height() - 10 });
	no.set_position({ window_coords.x + width - no.get_width() - 10, window_coords.y + height - no.get_height() - 10 });
}

void confirm_dialog::draw(SDL_Renderer* renderer)
{
	dialog_window::draw(renderer);
	yes.draw(renderer);
	no.draw(renderer);
}

void confirm_dialog::update(Mouse mouse)
{
	yes.update(mouse);
	no.update(mouse);

	if (yes.is_clicked())
		cur_state = dialog_state::Confirmed;
	else if (no.is_clicked())
		cur_state = dialog_state::Cancelled;
}

confirm_dialog::~confirm_dialog()
{
}
