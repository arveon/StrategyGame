#include "LeePathfinder.h"

constants::pathfinding_tile*** LeePathfinder::map;
int LeePathfinder::width, LeePathfinder::height;
SDL_Point LeePathfinder::origin;
SDL_Point LeePathfinder::destination;
bool LeePathfinder::path_found;
std::vector<SDL_Point> LeePathfinder::path;
std::vector<SDL_Point> LeePathfinder::cur_players;

LeePathfinder::LeePathfinder()
{
	path_found = false;
	origin = {0,0};
}

//this function will loop through the given tile neighbours, mark them with the given number and return the vector containing neighbours of all of the tiles neighbours
std::vector<constants::pathfinding_tile*> LeePathfinder::mark_tile_neighbours(constants::pathfinding_tile* tile, int num)
{
	std::vector<constants::pathfinding_tile*> to_mark_next;
	///will mark all of the given tile's neighbours and if they are not marked, will mark them
	///also will add them to the list of tile whose neighbours will be marked in the next iteration of the mark_field main loop
	for (int i = 0; i < (int)tile->neighbours.size(); i++)
	{
		if (tile->neighbours.at(i)->pathfinding_num == 0 && !tile->neighbours.at(i)->origin && !tile->neighbours.at(i)->blocked)
		{
			tile->neighbours.at(i)->pathfinding_num = num;
			to_mark_next.push_back(tile->neighbours.at(i));
		}
	}

	return to_mark_next;
}

void LeePathfinder::mark_field(constants::pathfinding_tile* start)
{
	//if start position not inside wall, set origin position
	if (map[start->position.y][start->position.x]->pathfinding_num != -1)
		origin = start->position;
	else
	{
		origin = { 0,0 };
	}

	int num = 1;
	//cur_number vector is used to store all of the tiles that will be marked in the current iteration (a current generation of tiles
	std::vector<constants::pathfinding_tile*> cur_generation = mark_tile_neighbours(start, num);
	
	bool cont = true;
	//one iteration of the loop - one generation of tiles (e.g. all of the first neighbours, all of the second neighbours of the tile, all of the third neighbours of the tile etc)
	//method will loop untill path is found or all of the tiles are marked and end is not found
	while (cont)
	{
		num++;
		//iteration points is the list of tiles that will be marked in the next generation
		std::vector<constants::pathfinding_tile*> next_generation;
		//loop through all of the tiles from the current generation and add the returned neighbours to the next generation
		for (int i = 0; i < (int)cur_generation.size(); i++)
		{
			std::vector<constants::pathfinding_tile*> t1 = mark_tile_neighbours(cur_generation.at(i), num);
			for (int j = 0; j < (int)t1.size(); j++)
				next_generation.push_back(t1.at(j));
		}

		//store next generation as current generation
		cur_generation = next_generation;
		//if there is no more tiles in the next generation to be marked, stop looping
		if (next_generation.size() == 0)
		{
			cont = false;
		}
	}
}

//function backtracks from the given end tile to the origin
bool LeePathfinder::calculate_path(constants::pathfinding_tile* end)
{
	constants::pathfinding_tile* cur_point = end;
	bool start_reached = false;
	
	//if looking for path to wall, it can't be found
	if (map[end->position.y][end->position.x]->pathfinding_num == -1)
		return false;

	while (!start_reached)
	{
		constants::pathfinding_tile* next_point = nullptr;

		//find the minimal number that is not -1 among the current tile neighbours and set it as next
		for (int i = 0; i < cur_point->neighbours.size(); i++)
		{
			constants::pathfinding_tile* temp = cur_point->neighbours.at(i);
			if (temp->pathfinding_num < cur_point->pathfinding_num && temp->pathfinding_num != -1)
			{
				if (temp->blocked && !temp->origin)
					continue;
				next_point = temp;
				break;
			}
		}

		if (next_point == nullptr)
			return false;
		else if (next_point->origin)
		{
			start_reached = true;
			continue;
		}
		path.push_back(next_point->position);

		cur_point = next_point;
	}

	if (start_reached)
		return true;
	else
		return false;
}

bool LeePathfinder::find_path(SDL_Point end_coords)
{
	bool success= false;
	path.clear();

	constants::pathfinding_tile* tile = map[end_coords.y][end_coords.x];
	if (map[end_coords.y][end_coords.x]->pathfinding_num == -1 || map[end_coords.y][end_coords.x]->blocked)
		return success;

	path.push_back(map[end_coords.y][end_coords.x]->position);

	success = calculate_path(map[end_coords.y][end_coords.x]);
	if (!success)
		path.clear();

	return success;
}

void LeePathfinder::set_origin(int x, int y)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if(map[i][j]->pathfinding_num != -1)
				map[i][j]->pathfinding_num = 0;

	map[origin.y][origin.x]->origin = false;
	origin.x = x;
	origin.y = y;
	map[origin.y][origin.x]->origin = true;
}

void LeePathfinder::set_destination(int x, int y)
{
	map[destination.y][destination.x]->destination = false;
	destination.x = x;
	destination.y = y;
	map[destination.y][destination.x]->destination = true;
}

void LeePathfinder::set_players(std::vector<SDL_Point> player_positions)
{
	//remove all of the player indications from map
	for (std::vector<SDL_Point>::iterator it = cur_players.begin(); it != cur_players.end(); it++)
	{
		SDL_Point player_pos = *it;
		map[player_pos.y][player_pos.x]->blocked = false;
	}

	//add new player indications
	for (std::vector<SDL_Point>::iterator it = player_positions.begin(); it != player_positions.end(); it++)
	{
		SDL_Point player_pos = *it;
		map[player_pos.y][player_pos.x]->blocked = true;
	}
	cur_players = player_positions;
}

void LeePathfinder::set_objects(std::vector<SDL_Point> object)
{
	//add object indications
	for (std::vector<SDL_Point>::iterator it = object.begin(); it != object.end(); it++)
	{
		SDL_Point player_pos = *it;
		constants::pathfinding_tile* tile = map[player_pos.y][player_pos.x];
		map[player_pos.y][player_pos.x]->blocked = true;
		std::cout << tile->blocked << std::endl;
	}
}

void LeePathfinder::display_field()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			if(!map[i][j]->blocked)
				std::cout << map[i][j]->pathfinding_num << ",";
			else
				std::cout << "-99,";
		std::cout << std::endl;
	}
}

LeePathfinder::~LeePathfinder()
{
}


