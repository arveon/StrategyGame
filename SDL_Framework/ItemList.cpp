#include "ItemList.h"


item_list::item_list()
{

}

item_list::item_list(std::string font_path, SDL_Color font_color, SDL_Texture* background, SDL_Rect draw_rect, SDL_Texture* selected_bg, std::vector<list_item> items, int items_in_view)
{
	this->font = sdlframework::sdl_manager::load_font(font_path, 20, font_color);
	this->font_color = font_color;
	this->bg = background;
	this->box_draw_rect = draw_rect;
	this->selected_item_bg_texture = selected_bg;
	this->items_list = items;
	this->top_item = 0;
	//this->view_size = items_in_view;
	
	init_lists();
}

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

		if (i < view_size)
		{
			list_item_text_draw_rects.push_back(SDL_Rect{box_draw_rect.x + left_margin, box_draw_rect.y + i * (height + item_margin), width, height});
		}
	}
}

void item_list::update(Mouse mouse)
{
	SDL_Point mousepoint{ mouse.x, mouse.y };
	if (SDL_PointInRect(&mousepoint, &box_draw_rect))
	{
		for (int i = 0; i < view_size; i++)
		{
			if (i >= (int) items_list.size())
				break;
			
			SDL_Rect collision_rect = list_item_text_draw_rects.at(i);
			collision_rect.w = box_draw_rect.w;
			collision_rect.h += item_margin;
			collision_rect.x -= left_margin;

			if (SDL_PointInRect(&mousepoint, &collision_rect) && mouse.lmb_down && !mouse.prev_lmb_down && i+top_item != selected_item)
			{
				selected_item_bg_draw_rect = collision_rect;
				selected_item = i + top_item;
			}
		}
	}
	scroll_bar_i.update(mouse);

	if (scroll_bar_i.is_down() && top_item + view_size < (int)items_list.size())
	{
		selected_item_bg_draw_rect.y -= selected_item_bg_draw_rect.h;
		top_item++;
	}
	else if (scroll_bar_i.is_up() && top_item != 0)
	{
		selected_item_bg_draw_rect.y += selected_item_bg_draw_rect.h;
		top_item--;
	}
	//std::cout << top_item << std::endl;
}

void item_list::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, bg, NULL, &box_draw_rect);
	
	for (int i = 0; (int) i < view_size; i++)
	{
		if (i >= (int) items_list.size())
			break;

		if (selected_item == i + top_item )
		{
			SDL_RenderCopy(renderer, selected_item_bg_texture, NULL, &selected_item_bg_draw_rect);
		}
		SDL_QueryTexture(list_item_textures_text.at(i + top_item), NULL, NULL, &list_item_text_draw_rects.at(i).w, nullptr);
		SDL_RenderCopy(renderer, list_item_textures_text.at(i + top_item), NULL, &list_item_text_draw_rects.at(i));
	}

	scroll_bar_i.draw(renderer);
}

item_list::~item_list()
{

}
