#pragma once
#include <list>

#include <SDL.h>

#include "Mouse.h"
#include "ListItem.h"

#include "ScrollBar.h"

class item_list
{
	SDL_Rect box_draw_rect;
	SDL_Texture* bg;
	
	std::list<list_item> items_list;
	int top_item;
	int selected_item;

	int view_size;

	std::list<SDL_Texture*> list_item_textures_text;
	std::list<SDL_Rect> list_item_text_draw_rects;

	SDL_Texture* selected_item_bg_texture;
	SDL_Rect selected_item_bg_draw_rect;

	scroll_bar scroll_bar;
public:
	void draw(SDL_Renderer* renderer);
	void update(Mouse mouse);

	item_list();
	item_list(SDL_Texture* background, SDL_Rect draw_rect, SDL_Texture* selected_bg, std::list<list_item>, int items_in_view);
	~item_list();
};

