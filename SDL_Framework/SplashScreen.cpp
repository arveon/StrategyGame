#include "SplashScreen.h"



splash_screen::splash_screen(SDL_Renderer* renderer)
{
	image = sdlframework::sdl_manager::load_png_texture(renderer, "assets/graphics/splash.png");
	
	draw_rect.w = 20;
	draw_rect.h = 10;
	draw_rect.x = 0;
	draw_rect.y = 0;
	Uint8 alpha = 255;
	SDL_SetTextureAlphaMod(image, 255);
	state = state::Waiting;
}

splash_screen::splash_screen()
{
	image = nullptr;
}

void splash_screen::update(int delta_time)
{
	elapsed_time += delta_time;
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
		transparency = elapsed_time / (float)animation_time * 255;
		if (transparency == 255)
		{
			elapsed_time = 0;
			state = state::Static;
		}	
	}
	else if (state == state::Static)
	{
		transparency = 255;
		if (elapsed_time >= total_screen_time - (2 * animation_time))
		{
			state = state::FadeOut;
			elapsed_time = 0;
		}
	}
	else if (state == state::FadeOut)
	{
		transparency = (animation_time - elapsed_time) / (float)animation_time * 255;
		if (transparency == 0)
			state = state::Blank;
	}


	SDL_SetTextureAlphaMod(image, transparency);
}


void splash_screen::draw(SDL_Renderer* renderer)
{
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, image, NULL, NULL);
	

	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

splash_screen::~splash_screen()
{
}
