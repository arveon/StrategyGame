#pragma once
#include <vector>

#include "Painter.h"
#include "MapManager.h"
#include "Mouse.h"
#include "Player.h"


///A generic representation of the level
class level
{
public:
	enum camera_mode
	{
		free,
		puppet
	};
protected:
	painter* drawing_manager;
	enum load_states
	{
		loading_map,
		loading_map_textures,
		loading_character_textures,
		attaching_map_textures,
		attaching_character_textures,
		cleaning_up_tilesheet,
		linking_tiles,
		loading_tileset,
		done
	};
	load_states loading_state;

	int current_player;
	int total_players;
	
	camera_mode cam_mode;

	bool is_loaded;
	float load_percent = 0;
public:
	void update_load(Mouse* mouse);

	void init(painter* drawing_manager);
	bool level_loaded() { return is_loaded; }
	float get_loaded_percent() { return load_percent; }

	virtual void mouse_clicked_at(int x, int y, constants::tile_type tile_clicked_at);

	camera_mode get_cam_mode() { return cam_mode; }

	level();
	~level();
};

