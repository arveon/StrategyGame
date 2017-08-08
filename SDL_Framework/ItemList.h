#pragma once
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "TextRenderer.h"

#include "Mouse.h"
#include "ListItem.h"

#include "ScrollBar.h"

///Class represents the list view UI element
///has a scrollbar attached to it (so total width += scrollbar width)
class item_list
{
	scroll_bar scroll_bar_i;

	TTF_Font* font;
	SDL_Color font_color;

	//items in the list
	std::vector<list_item> items_list;
	int top_item;//top visible item
	int selected_item;
	//number of items that can be in the view simultaneously
	int view_size;
	bool empty = false;//required to block certain features in case list is empty

	//required for drawing
	//whole element
	SDL_Rect box_draw_rect;
	SDL_Texture* bg;
	//individual elements
	std::vector<SDL_Texture*> list_item_textures_text;
	std::vector<SDL_Rect> list_item_text_draw_rects;//only has enough rects to fit in the view

	SDL_Texture* selected_item_bg_texture;
	SDL_Rect selected_item_bg_draw_rect;

	void init_lists(int selected = 0);

public:
	int item_margin = 10;//vertical margin between items
	int left_margin = 10;//margin of items from the left border of element

	void draw(SDL_Renderer* renderer);
	void update(Mouse mouse);

	int get_selected() { return selected_item; }
	void set_selected(int new_select);

	list_item get_element_at(int id) { return items_list.at(id); }

	item_list();
	item_list(std::string font_path, SDL_Color font_color, SDL_Texture* background, SDL_Rect draw_rect, SDL_Texture* selected_bg, std::vector<list_item>);
	~item_list();
};

