#pragma once
#include <SDL.h>
#include <vector>

#include "DrawableObject.h"

class painter
{
private:
	std::vector<drawable_object*> render_queue;

public:
	void add_object_to_queue(drawable_object* obj);
	void reset_queue();

	void draw_queue(SDL_Renderer* renderer);

	painter();
	~painter();
};

