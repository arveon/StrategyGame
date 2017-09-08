#pragma once
#include <SDL.h>

#include "TextRenderer.h"
#include "Sprite.h"
#include "Constants.h"


class load_screen
{
private:
	SDL_Texture* background;
	sprite progress_bar_bg;
	sprite progress_bar;

	TextRenderer* text_indicator;

	float percentage = 0;
	bool is_finished = false;
public:
	void set_percentage(float percentage, std::string loaded_item);//should be in range of 0-1

	void update();
	void draw(SDL_Renderer* renderer);
	load_screen();
	~load_screen();
};

