#pragma once
#include "GameObject.h"
#include "Constants.h"

class camera : game_object
{
	friend class painter;
public:
	game_object* camera_anchor;

	camera(game_object* camera_anchor);
	camera();
	~camera();
};