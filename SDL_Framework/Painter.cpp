#include "Painter.h"

///function used to initialise camera anchor and update cameras position to that anchor
void painter::init_anchor(game_object* camera_anchor)
{
	render_camera.camera_anchor = camera_anchor;
	render_camera.world_coords = camera_anchor->get_position();
}

///Adds a given object to an appropriate draw queue depending on its type
void painter::add_object_to_queue(drawable_object* obj)
{
	game_object* t_obj = (game_object*)obj;
	switch (t_obj->get_type())
	{
	case constants::base_object_type::terrain:
		rq_terrain.push_back(obj);
		break;
	case constants::base_object_type::item:
	case constants::base_object_type::character:
		rq_characters_items.push_back(obj);
		break;
	case constants::base_object_type::ui:
		rq_ui.push_back(obj);
		break;
	}
}

///DEPRECATED
void painter::add_text_ui_to_queue(TextRenderer* text)
{
	tq_ui.push_back(text);
}

///Function will sort the render queues
void painter::sort_queues()
{
	//TODO: write logic to sort queues so that objects with lowest Y coordinate are at the top of the queue (drawn first)
	//TODO: this function should be called every tick
}

///Function will be responsible to flush the queue
void painter::reset_queue()
{
}

///Function is called every tick and draws all of the objects in queues
///ORDER: terrain -> characters&items -> ui
void painter::draw_queue(SDL_Renderer* renderer)
{
	//draw terrain
	if (rq_terrain.size() != 0)
	{
		for (std::vector<drawable_object*>::iterator it = rq_terrain.begin(); it != rq_terrain.end(); ++it)
		{
			drawable_object* temp = *it;

			if ((temp->world_coords.x + temp->width < render_camera.world_coords.x) || (temp->world_coords.x > render_camera.world_coords.x + render_camera.width))
				continue;
			if (temp->world_coords.y + temp->width < render_camera.world_coords.y || temp->world_coords.y > render_camera.world_coords.y + render_camera.height)
				continue;

			SDL_Rect draw_rect = { temp->world_coords.x - render_camera.world_coords.x, temp->world_coords.y - render_camera.world_coords.y, temp->width, temp->height };
			SDL_RenderCopy(renderer, temp->texture, NULL, &draw_rect);
		}
	}

	//draw chars and items
	if (rq_characters_items.size() != 0)
	{
		for (std::vector<drawable_object*>::iterator it = rq_characters_items.begin(); it != rq_characters_items.end(); ++it)
		{
			drawable_object* temp = *it;

			if ((temp->world_coords.x + temp->width < render_camera.world_coords.x) || (temp->world_coords.x > render_camera.world_coords.x + render_camera.width))
				continue;
			if (temp->world_coords.y + temp->width < render_camera.world_coords.y || temp->world_coords.y > render_camera.world_coords.y + render_camera.height)
				continue;

			SDL_Rect draw_rect = { temp->world_coords.x - render_camera.world_coords.x, temp->world_coords.y - render_camera.world_coords.y, temp->width, temp->height };
			SDL_RenderCopy(renderer, temp->texture, NULL, &draw_rect);
		}
	}

	//draw ui
	if (rq_ui.size() != 0)
	{
		for (std::vector<drawable_object*>::iterator it = rq_ui.begin(); it != rq_ui.end(); ++it)
		{
			drawable_object* temp = *it;
			SDL_Rect draw_rect = { temp->world_coords.x, temp->world_coords.y, temp->width, temp->height };
			SDL_RenderCopy(renderer, temp->texture, NULL, &draw_rect);
		}
	}

}


painter::painter()
{
}

painter::~painter()
{
}
