#pragma once
#include <SDL.h>
#include <vector>

#include "TextRenderer.h"

#include "Constants.h"
#include "DrawableObject.h"
#include "Camera.h"

///Class that is responsible for rendering everything in-game
class painter
{
private:
	camera render_camera;
	std::vector<drawable_object*> rq_terrain;
	std::vector<drawable_object*> rq_characters_items;
	std::vector<drawable_object*> rq_ui;
	std::vector<TextRenderer*> tq_ui;
	std::vector<drawable_object*> rq_path;

	int path_ignored_before_tile = 0;
public:
	void init_anchor(game_object* camera_anchor);
	void add_object_to_queue(drawable_object* obj);
	void add_text_ui_to_queue(TextRenderer*);
	void reset_queue();
	void sort_queues();
	void remove_old_path();
	camera* get_camera_ptr() { return &render_camera; }

	void remove_traversed_path_tile() { rq_path.at(path_ignored_before_tile)->set_active(false); path_ignored_before_tile++; }

	void draw_queue(SDL_Renderer* renderer);

	painter();
	~painter();

};




