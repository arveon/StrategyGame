#include "ConfirmDialog.h"


confirm_dialog::confirm_dialog(SDL_Texture* bg, SDL_Point window_center, std::string text, int width, int height) : dialog_window(bg, window_center, true, text, width, height)
{
	yes.init("Optimus_Princeps.ttf", Button::ok, { window.x + 300, window.y + 170});
	no.init("Optimus_Princeps.ttf", Button::cancel, { window.x + 350, window.y + 170 });
}

void confirm_dialog::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, background, NULL, &window);
	SDL_Rect temp;
	/*temp.w = 200;
	temp.h = 100;
	temp.x = 0;
	temp.y = 0;*/
	SDL_QueryTexture(caption_text, NULL, NULL, &temp.w, &temp.h);
	temp.x = window.x;
	temp.y = window.y;

	SDL_RenderCopy(renderer, caption_text, NULL, &temp);
	yes.draw(renderer);
	no.draw(renderer);
}

void confirm_dialog::update(Mouse mouse)
{
	yes.update(mouse);
	no.update(mouse);
}

confirm_dialog::~confirm_dialog()
{
}
