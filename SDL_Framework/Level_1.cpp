#include "Level_1.h"

Level_1::Level_1() : level::level()
{
	map_manager::initialise();
	
	level_state = level_states::loading;
}

void Level_1::update(Mouse* mouse)
{
	switch (level_state)
	{
	case level_states::loading:
		level::update_load(mouse);
		if (level::level_loaded())
			level_state = level_states::gameplay;
	case level_states::gameplay:
		//LOGIC FOR UPDATING THE LEVEL AND ALL ENTITIES WITHIN IT
		//std::cout << "player position: " << map_manager::get_player(current_player)->get_position().x << " " << map_manager::get_player(current_player)->get_position().x;
		break;
	}
}

Level_1::~Level_1()
{
}
