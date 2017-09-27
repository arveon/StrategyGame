#pragma once
#include <SDL.h>

#include "Level.h"

#include "Mouse.h"
#include "MapManager.h"
#include "Painter.h"
#include "Tile.h"

class Level_1 : public level
{
protected:
	enum level_states
	{
		loading,
		gameplay,
	};
	level_states level_state;
	
public:
	void update(Mouse*);
	float get_loaded_percent() { return level::get_loaded_percent(); }
	bool is_level_loaded() { return (level_state == loading); }
	Level_1();
	~Level_1();
};

