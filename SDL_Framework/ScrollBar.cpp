#include "ScrollBar.h"


scroll_bar::scroll_bar()
{
	up.init(constants::font_inkedout, "up", { 400, 20 }, 12);
	down.init(constants::font_inkedout, "down", { 400, 420 }, 12);
}

void scroll_bar::update(Mouse mouse)
{
	up.update(mouse);
	down.update(mouse);

	if (down.is_clicked())
		cur_state = move_down;
	else if (up.is_clicked())
		cur_state = move_up;
	else
		cur_state = none;
}

void scroll_bar::draw(SDL_Renderer* renderer)
{
	down.draw(renderer);
	up.draw(renderer);
}

scroll_bar::~scroll_bar()
{
}
