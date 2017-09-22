#include "Level_1.h"



Level_1::Level_1()
{
	state = load_states::loading_map;
	load_percent = 0;
	is_loaded = false;
}

void Level_1::update(Mouse)
{
	if (!is_loaded)
	{
		switch (state)
		{
		case loading_map:
			map_manager::load_map(1);
			load_percent = 0.3;
			state = linking_tiles;
			break;
		case linking_tiles:
			//map_manager::link_tiles(); - not implemented yet
			SDL_Delay(1000);
			load_percent = 0.6;
			state = load_states::loading_tileset;
			break;
		case loading_tileset:
			SDL_Delay(1000);
			load_percent = 0.9;
			state = load_states::done;
			break;
		case done:
			SDL_Delay(1000);
			load_percent = 1;
			is_loaded = true;
			break;
		}
	}
}

Level_1::~Level_1()
{
}
