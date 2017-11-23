#pragma once
#include <vector>
#include "LivingEntity.h"
#include "Mouse.h"
///A type of living entity that is the main player
class player : public living_entity
{
private:
	std::vector<SDL_Point> path;
	bool moving;

	const int total_tile_move_time = 200;
	int elapsed_tile_move_time = 0;

	SDL_Point prev_tile;
	SDL_Point next_tile;

	int id;
public:
	player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id, int player_id);
	~player();
	
	bool path_tile_done = false;
	bool finished_movement = false;

	void update(Mouse* mouse, int delta_time);
	void set_path(std::vector<SDL_Point> new_path) { path = new_path; };
	bool is_dest_same(SDL_Point dest);
	bool is_moving() { return moving; }
	bool get_remaining_path_size() { return path.size(); }

	void move();
	int get_player_id() { return id; }
};

