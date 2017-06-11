#include "sdl_manager.h"


using namespace sdlframework;

SDL_Window* sdl_manager::game_window = nullptr;
SDL_Renderer* sdl_manager::renderer = nullptr;
bool sdl_manager::initialised = false;

void sdlframework::sdl_manager::init()
{
	assert(SDL_Init(SDL_INIT_EVERYTHING)==0);
	sdl_manager::game_window = SDL_CreateWindow(constants::WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	assert(sdl_manager::game_window);
	sdl_manager::renderer = SDL_CreateRenderer(sdl_manager::game_window, -1, SDL_RENDERER_ACCELERATED);
	assert(sdl_manager::renderer);
	SDL_SetRenderDrawColor(sdl_manager::renderer, 0, 0, 0, 0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	SDL_RenderSetScale(renderer, constants::scaling_horizontal, constants::scaling_vertical);
	SDL_ShowCursor(constants::SHOW_CURSOR);
	SDL_ShowCursor(true);
	std::cout << "sdl initialised" << std::endl;
	int img_flags = IMG_INIT_PNG;

	assert(IMG_Init(img_flags) & img_flags);
	assert(TTF_Init() != -1);
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) >= 0);
	initialised = true;
}


SDL_Texture* sdlframework::sdl_manager::load_png_texture(SDL_Renderer* renderer1, std::string path)
{
	if (initialised)
	{
		SDL_Texture* temp = IMG_LoadTexture(renderer, path.c_str());
		std::cout << IMG_GetError() << " for image " << path;
		assert(temp);
		return temp;
	}
	else
		return nullptr;
	
}

TTF_Font* sdlframework::sdl_manager::load_font(std::string path, float size, SDL_Color color)
{
	if (initialised)
	{
		TTF_Font* temp = TTF_OpenFont(path.c_str(), size);
		assert(temp);
		return temp;
	}
	else
		return nullptr;
}

Mix_Chunk* sdlframework::sdl_manager::load_sound(std::string path)
{
	if (initialised)
	{
		Mix_Chunk* temp = Mix_LoadWAV(path.c_str());
		assert(temp);
		return temp;
	}
	else
		return nullptr;
}

Mix_Music* sdlframework::sdl_manager::load_music(std::string path)
{
	if (initialised)
	{
		Mix_Music* temp = Mix_LoadMUS(path.c_str());
		assert(temp);
		return temp;
	}
	else
		return nullptr;
}

SDL_Texture* sdlframework::sdl_manager::render_text(SDL_Renderer* renderer, std::string text, SDL_Color color, TTF_Font* font)
{
	SDL_Surface* temp_s = TTF_RenderText_Solid(font, text.c_str(), color);
	assert(temp_s);
	return SDL_CreateTextureFromSurface(renderer, temp_s);
}

SDL_Texture* sdlframework::sdl_manager::create_texture(SDL_Renderer* renderer, int w, int h)
{
	return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
}


sdl_manager::sdl_manager()
{
}


sdl_manager::~sdl_manager()
{
	SDL_DestroyWindow(game_window);
	SDL_DestroyRenderer(renderer);
}
