#include "Painter.h"

void painter::init_anchor(game_object* camera_anchor)
{
	render_camera.camera_anchor = camera_anchor;
	render_camera.world_coords = camera_anchor->get_position();
}

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

void painter::sort_queues()
{
	//TODO: write logic to sort queues so that objects with lowest Y coordinate are at the top of the queue
	//TODO: this function should be called every tick
}

void painter::reset_queue()
{
}

void painter::draw_queue(SDL_Renderer * renderer)
{
	for (std::vector<drawable_object*>::iterator it = rq_terrain.begin(); it != rq_terrain.end(); ++it)
	{
		drawable_object* temp = *it;
		SDL_Rect draw_rect = { temp->world_coords.x, temp->world_coords.y, temp->width, temp->height };
		SDL_RenderCopy(renderer, temp->texture, NULL, &draw_rect);
	}

}


painter::painter()
{
}

painter::~painter()
{
}
