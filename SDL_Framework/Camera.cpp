#include "Camera.h"

camera::camera(game_object* camera_anchor) : game_object({0,0}, 0,0,true)
{
	this->camera_anchor = camera_anchor;
	this->width = constants::setup::WINDOW_WIDTH;
	this->height = constants::setup::WINDOW_HEIGHT;
	this->world_coords = camera_anchor->get_position();
}
camera::camera() : game_object({ 0,0 }, 0, 0, true)
{
	this->camera_anchor = nullptr;
	this->width = constants::setup::WINDOW_WIDTH;
	this->height = constants::setup::WINDOW_HEIGHT;
	this->world_coords = { 0,0 };
}

camera::~camera()
{
}
