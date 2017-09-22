#include "LevelManager.h"

void level_manager::update(Mouse mouse, int delta_time)
{
	level1.update(mouse);
	loaded = level1.get_loaded_percent();
	level_loaded = level1.level_loaded();
	////simulation of percentage changes
	//if (!level_loaded)
	//{
	//	static int passed = 0;
	//	passed += delta_time;
	//	loaded = (float)passed / 2000;

	//	if (loaded >= 1)
	//	{
	//		loaded = 1;
	//		level_loaded = true;
	//		passed = 0;
	//	}
	//	loaded_item = std::to_string(loaded);
	//}
	loaded_item = 1;
}


level_manager::level_manager()
{
	level_loaded = false;
}

level_manager::~level_manager()
{
}
