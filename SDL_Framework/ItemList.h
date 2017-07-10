#pragma once
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "TextRenderer.h"

#include "Mouse.h"
#include "ListItem.h"

#include "ScrollBar.h"

class item_list
{
	TTF_Font* font;
	SDL_Color font_color;

	SDL_Rect box_draw_rect;
	SDL_Texture* bg;
	
	std::vector<list_item> items_list;
	int top_item;
	int selected_item;

	int view_size;

	std::vector<SDL_Texture*> list_item_textures_text;
	std::vector<SDL_Rect> list_item_text_draw_rects;

	SDL_Texture* selected_item_bg_texture;
	SDL_Rect selected_item_bg_draw_rect;

	scroll_bar scroll_bar_i;

	void init_lists();

public:
	int item_margin = 10;
	int left_margin = 10;

	void draw(SDL_Renderer* renderer);
	void update(Mouse mouse);

	item_list();
	item_list(std::string font_path, SDL_Color font_color, SDL_Texture* background, SDL_Rect draw_rect, SDL_Texture* selected_bg, std::vector<list_item>, int items_in_view);
	~item_list();
};

