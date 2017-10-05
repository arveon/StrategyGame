#include "LevelManager.h"

void level_manager::update(Mouse* mouse, const Uint8* keyboard_state,int delta_time)
{
	level1.update(mouse);
	loaded = level1.get_loaded_percent();
	level_loaded = level1.level_loaded();
	loaded_item = 1;

	update_camera(mouse, keyboard_state, delta_time);
}

void level_manager::draw(SDL_Renderer* renderer)
{
	drawing_manager.draw_queue(renderer);
}

void level_manager::update_camera(Mouse* mouse, const Uint8* keyboard_state, int dt)
{
	camera* cam = drawing_manager.get_camera_ptr();
	int dx = 0, dy = 0;

	if (mouse->x <= 40)
		dx = -1;
	else if (mouse->x >= cam->width - 40)
		dx = 1;

	if (mouse->y <= 40)
		dy = -1;
	else if (mouse->y >= cam->height - 40)
		dy = 1;
	
	SDL_Point mapsize = map_manager::get_map_dimensions_px();
	if(cam->world_coords.x + dx >= 0 && cam->world_coords.x + cam->width + dx <= mapsize.x)
		cam->world_coords.x += dx;

	if (cam->world_coords.y + dy >= 0 && cam->world_coords.y + cam->height + dy <= mapsize.y)
		cam->world_coords.y += dy;
}

level_manager::level_manager()
{
	camera_frozen = true;
	level_loaded = false;
	level1.init(&drawing_manager);
	camera_frozen = false;
}

level_manager::~level_manager()
{
}
