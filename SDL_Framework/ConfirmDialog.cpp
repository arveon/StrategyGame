#include "ConfirmDialog.h"


confirm_dialog::confirm_dialog(SDL_Texture* bg, SDL_Point window_coords, std::string text, int width, int height) : dialog_window(bg, window_coords, true, text, width, height)
{
	text_color = SDL_Color{ 0,0,0 };

	TTF_Font* temp_font = sdlframework::sdl_manager::load_font("assets/fonts/Optimus_Princeps_Semi_Bold.ttf", 20, { 255, 255, 255 });
	caption_text = TextRenderer::get_texture_from_text(temp_font, caption, sdlframework::sdl_manager::get_renderer(), text_color);
	TTF_CloseFont(temp_font);

	cur_state = dialog_state::Waiting;
	yes.init("Optimus_Princeps_Semi_Bold.ttf", Button::ok, {0 , 0});
	no.init("Optimus_Princeps_Semi_Bold.ttf", Button::cancel, {0 , 0});

	yes.set_position({ window_coords.x + width - no.get_width() - yes.get_width() - 30, window_coords.y + height - yes.get_height() - 10 });
	no.set_position({ window_coords.x + width - no.get_width() - 10, window_coords.y + height - no.get_height() - 10 });
}

void confirm_dialog::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderCopy(renderer, background, NULL, &window);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Rect temp;
	SDL_QueryTexture(caption_text, NULL, NULL, &temp.w, &temp.h);
	temp.x = window.x;
	temp.y = window.y + temp.h/2;

	SDL_RenderCopy(renderer, caption_text, NULL, &temp);
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
