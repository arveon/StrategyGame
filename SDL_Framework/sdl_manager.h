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
	///Class that contains static function that give access to basic SDL functions
	class sdl_manager
	{
	private:
		static bool initialised;

		static SDL_Window* game_window;
		static SDL_Renderer* renderer;
	public:
		static void init();

		static SDL_Texture* load_png_texture(std::string path);
		static Mix_Chunk* load_sound(std::string path);
		static Mix_Music* load_music(std::string path);
		static TTF_Font* load_font(std::string path, int size, SDL_Color color);
		//function cuts the source rectangle from tilesheet and returns a pointer to it
		static SDL_Texture* get_texture_from_tilesheet(SDL_Texture* tilesheet, SDL_Rect source);

		static SDL_Renderer* get_renderer() { return renderer; }

		static SDL_Texture* render_text(std::string, SDL_Color, TTF_Font*);
		static SDL_Texture* create_texture(int w, int h, SDL_Color);

		static bool save_window_changes(int w_res, int h_res, bool fullscr);

		sdl_manager();
		~sdl_manager();
	};
	
}
#endif

