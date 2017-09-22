#pragma once
#include <SDL.h>

#include "Mouse.h"
#include "MapManager.h"
#include "Painter.h"
#include "Tile.h"

class Level_1
{
private:
	painter* drawing_manager;
	enum load_states
	{
		loading_map,
		linking_tiles,
		loading_tileset,
		done
	};
	load_states loading_state;


	enum level_states
	{
		loading,
		fadein,
		gameplay,
	};
	level_states level_state;

	bool is_loaded;
	float load_percent = 0;


public:
	void update(Mouse*);

	float get_loaded_percent() { return load_percent; }
	bool level_loaded() { return is_loaded; }
	Level_1();
	void init(painter*);
	~Level_1();
};

