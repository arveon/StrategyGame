#include "SplashScreen.h"


//proper splash screen initialisation (when it's reinitialised)
splash_screen::splash_screen(SDL_Renderer* renderer)
{
	image = sdlframework::sdl_manager::load_png_texture("assets/graphics/splash.png");
	
	draw_rect.w = 300;
	draw_rect.h = 200;
	draw_rect.x = constants::setup::WINDOW_WIDTH/2-(draw_rect.w/2);
	draw_rect.y = constants::setup::WINDOW_HEIGHT/2 - (draw_rect.h/2);
	Uint8 alpha = 255;
	SDL_SetTextureAlphaMod(image, 255);
	state = state::Waiting;
}

//when it's first initialised it uses default constructor
splash_screen::splash_screen()
{
	image = nullptr;
}

//update splash screen
void splash_screen::update(int delta_time)
{
	elapsed_time += delta_time;
	//change between states when time comes
	if (state == state::Waiting)
	{
		transparency = 0;
		if (elapsed_time >= wait_time)
		{
			elapsed_time = 0;
			state = state::FadeIn;
		}
	}
	if (state == state::FadeIn)
	{
		transparency = elapsed_time / (float)animation_time * 255;//transpatency starts at 0 finishes at 255
		if (transparency == 255)
		{
			elapsed_time = 0;
			state = state::Static;
		}	
	}
	else if (state == state::Static)
	{//pause between fading in and out
		transparency = 255;
		if (elapsed_time >= total_screen_time - (2 * animation_time))
		{
			state = state::FadeOut;
			elapsed_time = 0;
		}
	}
	else if (state == state::FadeOut)
	{//fading out
		transparency = (animation_time - elapsed_time) / (float)animation_time * 255;//starts at 255 finishes at 0
		if (transparency == 0)
			state = state::Blank;
	}

	//update texture alpha
	SDL_SetTextureAlphaMod(image, (Uint8)transparency);
}


void splash_screen::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, NULL, &draw_rect);
}

splash_screen::~splash_screen()
{
	SDL_DestroyTexture(image);
}
