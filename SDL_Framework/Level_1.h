#pragma once
#include <SDL.h>

#include "Mouse.h"
#include "MapManager.h"

class Level_1
{
private:
	bool is_loaded;
	enum load_states
	{
		loading_map,
		linking_tiles,
		loading_tileset,
		done
	};
	load_states state;
	float load_percent = 0;

public:
	void update(Mouse);

	float get_loaded_percent() { return load_percent; }
	bool level_loaded() { return is_loaded; }
	Level_1();
	~Level_1();
};

