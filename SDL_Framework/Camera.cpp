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

void camera::update(Mouse* mouse, int dt)
{
	if (cam_mode == camera_mode::free)
	{
		int dx = 0, dy = 0;

		if (mouse->x <= 40)
			dx = -1;
		else if (mouse->x >= width - 40)
			dx = 1;

		if (mouse->y <= 40)
			dy = -1;
		else if (mouse->y >= height - 40)
			dy = 1;

		world_coords.x += dx*dt;
		world_coords.y += dy*dt;
	}
	else if (cam_mode == camera_mode::puppet)
	{
		if (camera_anchor == nullptr)
			return;

		this->world_coords = camera_anchor->get_position();
		world_coords.x -= width / 2;
		world_coords.y -= height / 2;
	}
	

	///clamp camera to screen size
	if (world_coords.x < 0)
		world_coords.x = 0;
	if (world_coords.y < 0)
		world_coords.y = 0;

	if (world_coords.x + width > world_width)
		world_coords.x = world_width - width;
	if (world_coords.y + height > world_height)
		world_coords.y = world_height - height;
}