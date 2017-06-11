#pragma once
#ifndef SDLMANAGER_T
#define SDLMANAGER_T
#include <assert.h>
#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Constants.h"

namespace sdlframework
{
	class sdl_manager
	{
	private:
		static bool initialised;

		static SDL_Window* game_window;
		static SDL_Renderer* renderer;
	public:
		static void init();

		static SDL_Texture* load_png_texture(SDL_Renderer* renderer, std::string path);
		static Mix_Chunk* load_sound(std::string path);
		static Mix_Music* load_music(std::string path);
		static TTF_Font* load_font(std::string path, float size, SDL_Color color);

		static SDL_Renderer* get_renderer() { return renderer; }

		static SDL_Texture* render_text(SDL_Renderer*, std::string, SDL_Color, TTF_Font*);
		static SDL_Texture* create_texture(SDL_Renderer*, int w, int h);

		sdl_manager();
		~sdl_manager();
	};
	
}
#endif

