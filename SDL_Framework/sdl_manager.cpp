#include "sdl_manager.h"


using namespace sdlframework;

SDL_Window* sdl_manager::game_window = nullptr;
SDL_Renderer* sdl_manager::renderer = nullptr;
bool sdl_manager::initialised = false;

/*
	Initialise the SDL library
*/
void sdlframework::sdl_manager::init()
{
	assert(SDL_Init(SDL_INIT_EVERYTHING)==0);
	sdl_manager::game_window = SDL_CreateWindow(constants::WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN/* || SDL_WINDOW_FULLSCREEN*/);

	//initialise window and renderer
	assert(sdl_manager::game_window);
	sdl_manager::renderer = SDL_CreateRenderer(sdl_manager::game_window, -1, SDL_RENDERER_ACCELERATED);
	assert(sdl_manager::renderer);
	SDL_SetRenderDrawColor(sdl_manager::renderer, 0, 0, 0, 0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	SDL_SetRenderDrawBlendMode(sdl_manager::renderer, SDL_BlendMode::SDL_BLENDMODE_ADD);
	SDL_RenderSetScale(renderer, constants::scaling_horizontal, constants::scaling_vertical);

	//initialise img and mix libraries
	int img_flags = IMG_INIT_PNG;

	assert(IMG_Init(img_flags) & img_flags);
	assert(TTF_Init() != -1);
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) >= 0);
	initialised = true;

	//hide mouse cursor so the custom one can be drawn instead
	SDL_ShowCursor(0);
}

/*
	function loads a png texture
*/
SDL_Texture* sdlframework::sdl_manager::load_png_texture(std::string path)
{
	//need that if statement because the method is run before sdl is initialised, because it's a static method
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

/*
	function loads the font into a TTF_Font
	@path - full path to the font
	@size - size of font
	@color - font color
*/

TTF_Font* sdlframework::sdl_manager::load_font(std::string path, int size, SDL_Color color)
{
	//need that if statement because the method is run before sdl is initialised, because it's a static method
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
	//need that if statement because the method is run before sdl is initialised, because it's a static method
	if (initialised)
	{
		Mix_Chunk* temp = Mix_LoadWAV(path.c_str());
		assert(temp);
		return temp;
	}
	else
		return nullptr;
}

/*
	function loads sound file into Mix_Music* object 
	@path - path to the sound file
*/
Mix_Music* sdlframework::sdl_manager::load_music(std::string path)
{
	//need that if statement because the method is run before sdl is initialised, because it's a static method
	if (initialised)
	{
		Mix_Music* temp = Mix_LoadMUS(path.c_str());
		assert(temp);
		return temp;
	}
	else
		return nullptr;
}

/*
	function returns a texture representation of text
	@text - text to render
	@color - color to render text in
	@font - font to use
*/
SDL_Texture* sdlframework::sdl_manager::render_text(std::string text, SDL_Color color, TTF_Font* font)
{
	SDL_Surface* temp_s = TTF_RenderText_Solid(font, text.c_str(), color);
	assert(temp_s);
	SDL_Texture* temp_t = SDL_CreateTextureFromSurface(renderer, temp_s);
	SDL_FreeSurface(temp_s);
	return temp_t;
}

/*
	function that creates a plain texture of given width, height and color
*/
SDL_Texture* sdlframework::sdl_manager::create_texture(int w, int h, SDL_Color color)
{
	SDL_Texture* temp = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);//create a texture
	Uint32* pixels = new Uint32[w * h];// array that holds all the pixel values for the texture
	memset(pixels, 255, w * h * sizeof(Uint32));//set all the pixels to max value
	SDL_UpdateTexture(temp, NULL, pixels, w * sizeof(Uint32)); //apply pixels to texture
	delete[] pixels;//remove the array from memory to avoid memory leak
	SDL_SetTextureColorMod(temp, color.r, color.g, color.b);//set color of the texture
	return temp;
}


sdl_manager::sdl_manager()
{
}


sdl_manager::~sdl_manager()
{
	SDL_DestroyWindow(game_window);
	SDL_DestroyRenderer(renderer);
}
