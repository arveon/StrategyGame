#include "LevelManager.h"

//main level update method (level logic and sequences should happen here)
void level_manager::update(Mouse* mouse, const Uint8* keyboard_state,int delta_time)
{
	level1.update(mouse, delta_time);
	loaded = level1.get_loaded_percent();
	level_loaded = level1.level_loaded();
	loaded_item = 1;

	if (level_loaded)
	{
		update_camera(mouse, keyboard_state, delta_time);
		update_displayed_tile_type(mouse);
		handle_mouseclicks(mouse);
	}
}

//function called from levelmanager to draw the whole level
void level_manager::draw(SDL_Renderer* renderer)
{
	drawing_manager.draw_queue(renderer);
}

//Function updates the camera depending on the camera mode set
void level_manager::update_camera(Mouse* mouse, const Uint8* keyboard_state, int dt)
{
	camera* cam = drawing_manager.get_camera_ptr();
	//if camera mode is free, then player can manipulate it how he wants using the mouse
	if (level1.get_cam_mode() == level::camera_mode::free)
	{
		cam->cam_mode = camera::camera_mode::free;
	}
	else if(level1.get_cam_mode() == level::camera_mode::puppet)
	{
		cam->cam_mode = camera::camera_mode::puppet;
	}
	drawing_manager.get_camera_ptr()->update(mouse, dt);
}

//function takes care of handling mouse clicks
void level_manager::handle_mouseclicks(Mouse* mouse)
{
	if (mouse->lmb_down && mouse->lmb_down != mouse->prev_lmb_down)
	{
		int x,y;
		map_manager::world_tile_ids_at_mouse(&x, &y, mouse->x, mouse->y, drawing_manager.get_camera_ptr()->get_position());
		level1.mouse_clicked_at(x, y, map_manager::get_tile_type_at(x,y));
	}
}

//Function responsible to detect the type of tile mouse is pointing to and update the appropriate UI element
void level_manager::update_displayed_tile_type(Mouse* mouse)
{
	///need to store old type so that it doesn't create texture from text a million times a second
	static constants::tile_type old_type = constants::tile_type::empty;
	constants::tile_type new_type;

	int tile_x = 0, tile_y = 0;
	map_manager::world_tile_ids_at_mouse(&tile_x, &tile_y, mouse->x, mouse->y, drawing_manager.get_camera_ptr()->get_position());
	
	new_type = map_manager::get_tile_type_at(tile_x, tile_y);

	///if the tile has the same type as the one mouse was pointing before, just skip everything else
	if (new_type == old_type)
		return;

	///set the text to appropriate name
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
	///store the old type as new type
	old_type = new_type;
}

//Constructor initialises level, and the UI elements
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
