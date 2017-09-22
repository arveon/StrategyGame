#pragma once
#include "Constants.h"
#include "Mouse.h"

#include "Level_1.h"

class level_manager
{
private:
	painter drawing_manager;
	Level_1 level1;
	
	enum state
	{
		loading,
		in_level,
		none
	};
	bool level_loaded;
	std::string loaded_item;
	float loaded = 0;
public:
	void reset_level();
	void set_level();
	void unload_level();

	bool is_level_loaded() { return level_loaded; }
	float get_loaded_percent() { return loaded; }
	std::string get_loaded_item() { return loaded_item; }
	
	void update(Mouse*, int delta_time);
	void draw(SDL_Renderer*);
	
	level_manager();
	~level_manager();
};

