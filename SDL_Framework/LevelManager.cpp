#include "LevelManager.h"

void level_manager::update(Mouse* mouse, int delta_time)
{
	level1.update(mouse);
	loaded = level1.get_loaded_percent();
	level_loaded = level1.level_loaded();
	loaded_item = 1;


}

void level_manager::draw(SDL_Renderer* renderer)
{
	drawing_manager.draw_queue(renderer);
}


level_manager::level_manager()
{
	level_loaded = false;
	level1.init(&drawing_manager);
}

level_manager::~level_manager()
{
}
