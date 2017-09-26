#include "Level_1.h"

Level_1::Level_1()
{
	map_manager::initialise();
	loading_state = load_states::loading_map;
	level_state = level_states::loading;
	load_percent = 0;
	is_loaded = false;

	this->drawing_manager = drawing_manager;
}

void Level_1::init(painter* ptr)
{
	drawing_manager = ptr;
}

void Level_1::update(Mouse* mouse)
{
	switch (level_state)
	{
	case level_states::loading:
		//move all following code into generic level parent and replace it with level::update(mouse);
		mouse->is_drawn = false;
		switch (loading_state)
		{
		case loading_map:
			map_manager::load_map(1);
			load_percent = 0.3;
			loading_state = linking_tiles;
			break;
		case linking_tiles:
			//map_manager::link_tiles(); - not implemented yet
			SDL_Delay(1000);
			load_percent = 0.6;
			loading_state = load_states::loading_tileset;
			break;
		case loading_tileset:
			SDL_Delay(1000);
			load_percent = 0.9;
			loading_state = load_states::done;
			break;
		case done:
			SDL_Delay(1000);
			load_percent = 1;
			is_loaded = true;
			mouse->is_drawn = true;
			
			tile_object*** map = map_manager::get_map();
			SDL_Point dimensions = map_manager::get_map_dimensions_t();
			for (int i = 0; i < dimensions.y; i++)
			{
				for (int j = 0; j < dimensions.x; j++)
				{
					drawing_manager->add_object_to_queue((drawable_object*)map[i][j]);
				}
			}
			std::cout << "asd" << std::endl;
			level_state = level_states::gameplay;
			break;
		}
		break;
	case level_states::gameplay:
		//LOGIC FOR UPDATING THE LEVEL AND ALL ENTITIES WITHIN IT

		break;
	}
}

Level_1::~Level_1()
{
}
