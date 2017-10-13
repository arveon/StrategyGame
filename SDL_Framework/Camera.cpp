#include "Camera.h"

//constructor that sets the camera anchor to a certain object and initialises the camera to the objects position
camera::camera(game_object* camera_anchor) : game_object({0,0}, 0,0,true)
{
	this->camera_anchor = camera_anchor;
	this->width = constants::setup::WINDOW_WIDTH;
	this->height = constants::setup::WINDOW_HEIGHT;
	this->world_coords = camera_anchor->get_position();
}
//default constructor that puts the camera at 0:0
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
