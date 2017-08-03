#include "ItemList.h"
using namespace constants;
/*
	constructor
	@draw_rect - rectangle where the whole element (excluding the scrollbar) will be drawn
	@items_in_view - number of items that would fit in a view without scrolling
*/
item_list::item_list(std::string font_path, SDL_Color font_color, SDL_Texture* background, SDL_Rect draw_rect, SDL_Texture* selected_bg, std::vector<list_item> items)
{
#pragma warning(disable:4244)
	draw_rect.x *= scaling_horizontal;
	draw_rect.y *= scaling_vertical;

	this->font = sdlframework::sdl_manager::load_font(font_path, 20, font_color);
	this->font_color = font_color;
	this->bg = background;
	this->box_draw_rect = draw_rect;
	this->selected_item_bg_texture = selected_bg;
	this->items_list = items;
	this->top_item = 0;
	
	if (items_list.size() > 0)
		init_lists();
	else
	{
		scroll_bar_i.disable();
	}
	scroll_bar_i.init(sdlframework::sdl_manager::create_texture(1, 1, { 255, 0, 0 }), sdlframework::sdl_manager::create_texture(1, 1, { 255, 255, 255 }), sdlframework::sdl_manager::create_texture(20, 20, { 255, 255, 255 }), { box_draw_rect.x + box_draw_rect.w, box_draw_rect.y, 20, box_draw_rect.h }, items_list.size(), view_size, sdlframework::sdl_manager::create_texture(20, box_draw_rect.h, { 100, 100, 100 }));
}

/*
	function used to initialise and fill the list of text textures and draw rectangles also initialises the selected item rectangle
*/
void item_list::init_lists()
{
	selected_item = 0;

	for (int i = 0; i < (int) items_list.size(); i++)
	{
		int width, height;

		list_item_textures_text.push_back(TextRenderer::get_texture_from_text(font, items_list.at(i).display_name, font_color));
		SDL_QueryTexture(list_item_textures_text.at(i), NULL, NULL, &width, &height);

		if (i == 0)
			view_size = box_draw_rect.h / (height + item_margin);
		//only initialise draw_rectangles for elements that are inside the view
		if (i < view_size)
		{
			list_item_text_draw_rects.push_back(SDL_Rect{box_draw_rect.x + left_margin, box_draw_rect.y + i * (height + item_margin), width, height});
		}
	}

	selected_item_bg_draw_rect = list_item_text_draw_rects.at(0);
	selected_item_bg_draw_rect.w = box_draw_rect.w;
	selected_item_bg_draw_rect.x -= left_margin;
	selected_item_bg_draw_rect.h += item_margin;
}

void item_list::update(Mouse mouse)
{
	//if its empty, don't need to update it
	if (empty)
		return;

	SDL_Point mousepoint{ mouse.x, mouse.y };
	if (SDL_PointInRect(&mousepoint, &box_draw_rect))
	{//if mouse inside the box area
		//loop through all the draw rectangles
		for (int i = 0; i < view_size; i++)
		{
			//if reached size of list (happens if there is less elements than the view size), break out
			if (i >= (int) items_list.size())
				break;
			
			//compose a collision rectangle 
			//(need to be composed because it's slightly bigger than draw rect for texture, since margins are clickable and covers full width of box)
			SDL_Rect collision_rect = list_item_text_draw_rects.at(i);
			collision_rect.w = box_draw_rect.w;
			collision_rect.h += item_margin;
			collision_rect.x -= left_margin;

			//if clicked on the collision rectangle of the item (and it wasnt selected before), 
			//update selected item index and set selected bg draw rect to collision rect
			if (SDL_PointInRect(&mousepoint, &collision_rect) && mouse.lmb_down && !mouse.prev_lmb_down && i+top_item != selected_item)
			{
				selected_item_bg_draw_rect = collision_rect;
				selected_item = i + top_item;
			}
		}
	}

	scroll_bar_i.update(mouse);

	//block checks for scroll bar updates
	if (scroll_bar_i.is_down() && top_item + view_size < (int)items_list.size())
	{//if down button pressed and bottom of list not reached yet, shift selected_item_draw_rect one item up and change top item id
		selected_item_bg_draw_rect.y -= selected_item_bg_draw_rect.h;
		scroll_bar_i.reset();
		top_item++;
		//calculate the percentage of the list scrolled and update scroll bar slider position
		float percentage = (top_item > 0) ? (float)top_item / (float)(items_list.size()-view_size) : 0;
		scroll_bar_i.set_bar_percent(percentage);
	}
	else if (scroll_bar_i.is_up() && top_item != 0)
	{//same as above except shift selected_item_draw_rect one item up
		selected_item_bg_draw_rect.y += selected_item_bg_draw_rect.h;
		scroll_bar_i.reset();
		top_item--;

		float percentage = (top_item > 0) ? (float)top_item / (float)(items_list.size() - view_size) : 0;
		scroll_bar_i.set_bar_percent(percentage);
	}
	else if (scroll_bar_i.is_percentage_changed())
	{//if scroll bar slider moved manually, update the top item
		int old_top_item = top_item;//store, so can calculate by how much to shift the selected_item_draw_rect
		top_item = (int) (((float)items_list.size() - view_size) * scroll_bar_i.get_bar_percent());//calculate the id of the item that needs to be at the top by scrollbar percentage
		scroll_bar_i.reset();

		//by how many items to move selected_item_draw_rect, move it
		int delta = top_item - old_top_item;
		selected_item_bg_draw_rect.y -= selected_item_bg_draw_rect.h * delta;
	}
	
}

void item_list::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, bg, NULL, &box_draw_rect);
	scroll_bar_i.draw(renderer);

	//dont draw individual entries if list is empty
	if (empty)
		return;
	//loop through the list until view size reached
	for (int i = 0; (int) i < view_size; i++)
	{
		//if end of list reached, stop looping
		if (i >= (int) items_list.size())
			break;

		//if item currently drawn is selected, draw a selected item texture under it
		if (selected_item == i + top_item )
			SDL_RenderCopy(renderer, selected_item_bg_texture, NULL, &selected_item_bg_draw_rect);

		//update the width of the draw rectangle so the texture fits in it (rectangles are not be updated when scrolled down/up in the list)
		SDL_QueryTexture(list_item_textures_text.at(i + top_item), NULL, NULL, &list_item_text_draw_rects.at(i).w, nullptr);
		//draw item
		SDL_RenderCopy(renderer, list_item_textures_text.at(i + top_item), NULL, &list_item_text_draw_rects.at(i));
	}

	
}

item_list::~item_list()
{

}


item_list::item_list()
{

}