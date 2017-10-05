#include "LevelManager.h"

void level_manager::update(Mouse* mouse, const Uint8* keyboard_state,int delta_time)
{
	level1.update(mouse);
	loaded = level1.get_loaded_percent();
	level_loaded = level1.level_loaded();
	loaded_item = 1;

	update_displayed_tile_type(mouse);
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

void level_manager::update_displayed_tile_type(Mouse* mouse)
{
	static constants::tile_type old_type = constants::tile_type::empty;
	constants::tile_type new_type;

	SDL_Point total_size = map_manager::get_map_dimensions_px();
	total_size.x /= constants::tile_scaling;
	total_size.y /= constants::tile_scaling;
	SDL_Point camera_position = drawing_manager.get_camera_ptr()->world_coords;

	SDL_Point mouse_world_pos;
	mouse_world_pos.x = (mouse->x + camera_position.x) / constants::tile_scaling;
	mouse_world_pos.y = (mouse->y + camera_position.y) / constants::tile_scaling;

	int tile_x = 0, tile_y = 0;
	tile_x = (int)std::floor((float)mouse_world_pos.x/(float)map_manager::get_tile_size());
	tile_y = (int)std::floor((float)mouse_world_pos.y/(float)map_manager::get_tile_size());
	new_type = map_manager::get_tile_type_at(tile_x, tile_y);

	if (new_type == old_type)
		return;

	std::string newstring = "";
	switch (new_type)
	{
	case constants::tile_type::empty:
		newstring = "Empty";
		break;
	case constants::tile_type::earth:
		newstring = "Dirt";
		break;
	case constants::tile_type::grass:
		newstring = "Grass";
		break;
	case constants::tile_type::stone:
		newstring = "Stone";		
		break;
	case constants::tile_type::water:
		newstring = "Water";
		break;
	}
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_libertine);
	tile_type_indicator->change_texture(sdlframework::sdl_manager::render_text(newstring, { 255,255,255 }, sdlframework::sdl_manager::load_font(fontpath, 20, { 0,0,0 })));

	old_type = new_type;
}

level_manager::level_manager()
{
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_libertine);

	SDL_Texture* temp = sdlframework::sdl_manager::render_text("Empty", { 255,255,255 }, sdlframework::sdl_manager::load_font(fontpath, 20, { 0,0,0 }));
	int x, y;
	SDL_QueryTexture(temp, NULL, NULL, &x, &y);
	tile_type_indicator = new drawable_object({constants::GPI_TILE_TYPE_POS_MARGIN.x, constants::setup::WINDOW_HEIGHT + constants::GPI_TILE_TYPE_POS_MARGIN.y}, x, y, true, temp, constants::base_object_type::ui);
	drawing_manager.add_object_to_queue(tile_type_indicator);

	camera_frozen = true;
	level_loaded = false;
	level1.init(&drawing_manager);
	camera_frozen = false;
}

level_manager::~level_manager()
{
}
