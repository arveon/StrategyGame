#pragma once
#include <SDL.h>
#include <vector>

#include "Constants.h"
#include "DrawableObject.h"
#include "Camera.h"

class painter
{
private:
	camera render_camera;
	std::vector<drawable_object*> rq_terrain;
	std::vector<drawable_object*> rq_characters_items;
	std::vector<drawable_object*> rq_ui;

public:
	void init(game_object* camera_anchor);
	void add_object_to_queue(drawable_object* obj);
	void reset_queue();
	void sort_queues();

	void draw_queue(SDL_Renderer* renderer);

	painter();
	~painter();

};




