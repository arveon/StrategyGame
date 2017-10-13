#pragma once
#include "GameObject.h"
#include "Constants.h"
///a type of game object that specificly works as a camera
class camera : game_object
{
	friend class painter;
	friend class level_manager;
public:
	game_object* camera_anchor;
	
	camera(game_object* camera_anchor);
	camera();
	~camera();
};