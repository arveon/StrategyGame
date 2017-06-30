#include "ItemList.h"


item_list::item_list()
{

}

item_list::item_list(SDL_Texture* background, SDL_Rect draw_rect, SDL_Texture* selected_bg, std::list<list_item> items, int items_in_view)
{
	this->bg = background;
	this->box_draw_rect = draw_rect;
	this->selected_item_bg_texture = selected_bg;
	this->items_list = items;
	this->view_size = items_in_view;
}

item_list::~item_list()
{

}
