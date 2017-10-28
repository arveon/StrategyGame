#pragma once
#include <vector>
#include "LivingEntity.h"
///A type of living entity that is the main player
class player : public living_entity
{
private:
	std::vector<SDL_Point> path;
public:
	player(SDL_Point coords, int width, int height, SDL_Texture* texture, bool is_active, int texture_id);
	~player();

	void set_path(std::vector<SDL_Point> new_path) { path = new_path; };
	bool is_dest_same(SDL_Point dest);

	void move();
};

