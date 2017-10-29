#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Mouse.h"
///a type of game object that specificly works as a camera
class camera : game_object
{
private:
	int world_width;
	int world_height;

	friend class painter;
	friend class level_manager;
public:
	enum camera_mode
	{
		free,
		puppet
	};
	camera_mode cam_mode;

	game_object* camera_anchor;
	
	void update(Mouse* mouse, int dt);

	void set_world_size(int width, int height) { world_width = width; world_height = height; }

	camera(game_object* camera_anchor);
	camera();
	~camera();
};