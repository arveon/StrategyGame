#include "MapManager.h"

///initialise all of the static variables
int map_manager::tileswide, map_manager::tileshigh = 0;
int  map_manager::t_width, map_manager::t_height = 1;
tile_object*** map_manager::map = nullptr;
bool map_manager::initialised = false;
std::vector<living_entity*> map_manager::map_entities;
std::vector<player*> map_manager::players;
std::vector<item_object*> map_manager::items;
bool map_manager::map_currently_loaded = false;
constants::pathfinding_tile*** map_manager::tile_cost_map;

//Function is used to load a map with a given level id and initialise the manager
void map_manager::load_map(int level)
{
	if (initialised)
	{
		map_currently_loaded = false;
		tileset_manager::set_initialised();
		load_from_file();
		/*list_tex_to_load();
		link_textures_to_tiles();*/
	}
}

///Function used to load the actual map from the file and create all of the required objects
void map_manager::load_from_file()
{
	//TODO::Add checks for file not being in the folder, not having anything in the map etc
	tileswide = tileshigh = 0;
	///load file into a data structure
	rapidxml::file<> file("maps/sample_map.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());

	///get width and height of map from attributes
	tileswide = std::stoi(doc.first_node()->first_attribute("tileswide")->value());
	tileshigh = std::stoi(doc.first_node()->first_attribute("tileshigh")->value());
	t_width = std::stoi(doc.first_node()->first_attribute("tilewidth")->value());
	constants::setup::tile_width = t_width;
	t_height = std::stoi(doc.first_node()->first_attribute("tileheight")->value());
	constants::setup::tile_height = t_height;
	std::cout << "size: " << tileswide << " by " << tileshigh << std::endl;

	///get reference to the first tile node
	rapidxml::xml_node<>* cur_node = doc.first_node("tilemap")->first_node("layer")->first_node("tile");

	//allocate space for map array
	map = new tile_object**[tileshigh];
	for (int i = 0; i < tileshigh; i++)
		map[i] = new tile_object*[tileswide];

	///loop through all nodes getting their coordinates from attributes and saving the tile types into map array
	while (cur_node != NULL)
	{
		int x, y = 0;
		x = std::stoi(cur_node->first_attribute("x")->value());
		y = std::stoi(cur_node->first_attribute("y")->value());

		int t_tex_id = std::stoi(cur_node->first_attribute("tile")->value());
		if (t_tex_id == -1)
		{
			cur_node = cur_node->next_sibling();
			continue;
		}

#pragma region tile_type_switch
		constants::tile_type t_type;
		switch (t_tex_id)
		{
		case 0:
			t_type = constants::tile_type::empty;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
			t_type = constants::tile_type::earth;
			break;
		case 14:
			t_type = constants::tile_type::grass;
			break;
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
			t_type = constants::tile_type::stone;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
			t_type = constants::tile_type::water;
			break;
		default:
			t_type = constants::tile_type::empty;
		}
#pragma endregion

		tile_object* temp_tile = new tile_object({ (int)std::floor(((float)(x * t_width) * constants::tile_scaling)), (int)std::floor(((float)(y * t_height) * constants::tile_scaling)) }, t_width * constants::tile_scaling, t_height * constants::tile_scaling, true, nullptr, 0, (constants::tile_type)t_type, t_tex_id);
		map[y][x] = temp_tile;
		
		cur_node = cur_node->next_sibling();
	}
	cur_node = doc.first_node("tilemap")->first_node("layer");
	cur_node = cur_node->next_sibling()->first_node("tile");

	///loop through all nodes getting their coordinates from attributes and saving the tile types into map array
	while (cur_node != NULL)
	{
		int x, y = 0;
		x = std::stoi(cur_node->first_attribute("x")->value());
		y = std::stoi(cur_node->first_attribute("y")->value());

		int tex_id = std::stoi(cur_node->first_attribute("tile")->value());
		if (tex_id == -1)
		{
			cur_node = cur_node->next_sibling();
			continue;
		}
		
		SDL_Point pos{ (int)std::floor(((float)(x * t_width) * constants::tile_scaling)), (int)std::floor(((float)(y * t_height) * constants::tile_scaling)) };
		game_object* obj1 = nullptr;
		switch (tex_id)
		{
		case 70:
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
		case 76:
		case 77:
		case 78:
		case 79:
		case 80:
		case 81:
			obj1 = new item_object(pos, t_width * constants::tile_scaling, t_height*constants::tile_scaling, nullptr, true, tex_id, constants::item_type::tree, "Tree");
			items.push_back(static_cast<item_object*>(obj1));
			break;
		case 82:
		case 83:
		case 84:
			obj1 = new item_object(pos, t_width * constants::tile_scaling, t_height*constants::tile_scaling, nullptr, true, tex_id, constants::item_type::tree_trunk, "Tree roots");
			items.push_back(static_cast<item_object*>(obj1));
			break;
		}
		if (obj1 != nullptr)
		{
			cur_node = cur_node->next_sibling();
			continue;
		}
		
		player* obj;
		tex_id -= constants::tileset_entity_offset;
		switch (tex_id)
		{
		case 0:
		case 1:
		case 2:
			obj = new player(pos, t_width * constants::tile_scaling, t_height * constants::tile_scaling, nullptr, true, tex_id, tex_id+1);
			players.push_back(obj);
			break;
		}
		
		cur_node = cur_node->next_sibling();
	}
	map_currently_loaded = true;
}

//Function is used to build a vector of required terrain tiles and ask tileset manager to load them
void map_manager::load_required_tex_tiles()
{
	std::vector<int> texture_id_list;
	for (int i = 0; i < tileshigh; i++)
	{
		for (int j = 0; j < tileswide; j++)
		{
			if (!helper_functions::is_int_in_vector(texture_id_list, map[i][j]->texture_id))
				helper_functions::add_to_int_vector_asc(&texture_id_list, map[i][j]->texture_id);
		}
	}
	tileset_manager::load_tiles(texture_id_list, constants::tilesets::map, t_width, t_height);
}

//function is used to build a vector of character tiles and load them from a vector
void map_manager::load_required_tex_players()
{
	std::vector<int> entity_texture_id_list;
	for (std::vector<player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		player* ent = *it;

		if (!helper_functions::is_int_in_vector(entity_texture_id_list, ent->texture_id+constants::tileset_entity_offset))
			helper_functions::add_to_int_vector_asc(&entity_texture_id_list, ent->texture_id);
	}
	tileset_manager::load_tiles(entity_texture_id_list, constants::tilesets::characters, t_width, t_height);
}

//function is used to build a vector of item tiles and load them from a vector
void map_manager::load_required_tex_items()
{
	std::vector<int> items_texture_id_list;
	for (std::vector<item_object*>::iterator it = items.begin(); it != items.end(); ++it)
	{
		item_object* ent = *it;

		if (!helper_functions::is_int_in_vector(items_texture_id_list, ent->texture_id + constants::tileset_entity_offset))
			helper_functions::add_to_int_vector_asc(&items_texture_id_list, ent->texture_id);
	}
	tileset_manager::load_tiles(items_texture_id_list, constants::tilesets::items, t_width, t_height);
}

//function is used to link all of the terrain textures from tileset manager to actual objects
void map_manager::link_textures_to_tiles()
{
	for (int i = 0; i < tileshigh; i++)
		for (int j = 0; j < tileswide; j++)
			map[i][j]->texture = tileset_manager::get_texture_by_id(constants::tilesets::map, map[i][j]->texture_id);
}

//function is used to link the entity textures from tileset manager to actual objects
void map_manager::link_textures_to_players()
{
	for (std::vector<player*>::iterator it = players.begin(); it != players.end(); ++it)
			(*it)->texture = tileset_manager::get_texture_by_id(constants::tilesets::characters, (*it)->texture_id);
}

//function is used to link the entity textures from tileset manager to actual objects
void map_manager::link_textures_to_items()
{
	for (std::vector<item_object*>::iterator it = items.begin(); it != items.end(); ++it)
		(*it)->texture = tileset_manager::get_texture_by_id(constants::tilesets::items, (*it)->texture_id);
}

//function used to unload the whole map
void map_manager::unload_map()
{
	for (int i = 0; i < tileshigh; i++)
	{
		delete map[i];
	}
	delete map;
	tileswide = tileshigh = 0;
}

//function is used to add an appropriate vector (of objects of a certain type) to the painter queues
void map_manager::add_vector_to_painter(painter* drawing_manager, constants::base_object_type type)
{
	switch (type)
	{
	case constants::base_object_type::terrain:
		for (int i = 0; i < tileshigh; i++)
			for (int j = 0; j < tileswide; j++)
				drawing_manager->add_object_to_queue(map[i][j]);
		break;
	case constants::base_object_type::character:
		for (std::vector<player*>::iterator it = players.begin(); it != players.end(); ++it)
			drawing_manager->add_object_to_queue(*it);
		break;
	case constants::base_object_type::item:
		for (std::vector<item_object*>::iterator it = items.begin(); it != items.end(); ++it)
			drawing_manager->add_object_to_queue(*it);
		break;
	}
}

//Function links every tile with all of its neighbouring tiles for the pathfinding algorithm
bool map_manager::link_tiles()
{
	///if map is not loaded there is nothing to link
	if (!map_currently_loaded)
		return false;
	
	///link a tile with all of its neighbouring tiles
	for (int i = 0; i < tileshigh; i++)
	{
		for (int j = 0; j < tileswide; j++)
		{
			if (i > 0)
				map[i][j]->add_neighbour(map[i-1][j]);
			if (j > 0)
				map[i][j]->add_neighbour(map[i][j-1]);
			if (i < tileswide - 1)
				map[i][j]->add_neighbour(map[i + 1][j]);
			if (j < tileshigh - 1)
				map[i][j]->add_neighbour(map[i][j + 1]);
			if (i > 0 && j > 0)
				map[i][j]->add_neighbour(map[i - 1][j - 1]);
			if (i > 0 && j < tileshigh - 1)
				map[i][j]->add_neighbour(map[i - 1][j + 1]);
			if (i < tileswide - 1 && j > 0)
				map[i][j]->add_neighbour(map[i + 1][j - 1]);
			if (i < tileswide - 1 && j < tileshigh - 1)
				map[i][j]->add_neighbour(map[i + 1][j + 1]);
		}
	}
	return true;
}

//Function calculates the x and y id of the tile and stores it in to_save_x and to_save_y
void map_manager::world_tile_ids_at_mouse(int* to_save_x, int* to_save_y, int mouse_x, int mouse_y, SDL_Point camera_position)
{
	//get the world coordinates of where the mouse is pointing to (remove the scaling factor from equasion)
	SDL_Point total_size = map_manager::get_map_dimensions_px();
	total_size.x /= constants::tile_scaling;
	total_size.y /= constants::tile_scaling;
	SDL_Point mouse_world_pos;
	mouse_world_pos.x = (mouse_x + camera_position.x) / constants::tile_scaling;
	mouse_world_pos.y = (mouse_y + camera_position.y) / constants::tile_scaling;
	//calculate the tile number by x and y the mouse is pointing at and get its type
	*(to_save_x) = (int)std::floor((float)mouse_world_pos.x / (float)map_manager::get_tile_size());
	*(to_save_y) = (int)std::floor((float)mouse_world_pos.y / (float)map_manager::get_tile_size());
}

void map_manager::world_tile_ids_at_coords(int * to_save_x, int * to_save_y, int x, int y)
{
	//get the world coordinates of where the mouse is pointing to (remove the scaling factor from equasion)
	SDL_Point total_size = map_manager::get_map_dimensions_px();
	//calculate the tile number by x and y the mouse is pointing at and get its type
	*(to_save_x) = (int)std::floor((float)x / (float)map_manager::get_tile_size());
	*(to_save_y) = (int)std::floor((float)y / (float)map_manager::get_tile_size());
}

void map_manager::init_pathfinding()
{
	if (initialised)
	{
		//TODO: build up a map of static collisions with (0 as passable and 1 as non-passable)
		///initialise the collision map
		tile_cost_map = new constants::pathfinding_tile**[tileshigh];
		for (int i = 0; i < tileshigh; i++)
			tile_cost_map[i] = new constants::pathfinding_tile*[tileswide];

		///loop generates a basic map movement cost map based only on terrain (other objects not included)
		for (int i = 0; i < tileshigh; i++)
		{
			for (int j = 0; j < tileswide; j++)
			{
				tile_object* tile = map[i][j];
				switch (tile->tile_type)
				{
				case constants::tile_type::earth:
				case constants::tile_type::grass:
				case constants::tile_type::mud:
				case constants::tile_type::stone:
					tile->set_travel_cost(1);
					break;
				default:
					tile->set_travel_cost(-1);	
				}

				tile_cost_map[i][j] = new constants::pathfinding_tile();
				tile_cost_map[i][j]->cost = tile->get_travel_cost();
				tile_cost_map[i][j]->blocked = false;
				if (tile_cost_map[i][j]->cost == -1)
					tile_cost_map[i][j]->pathfinding_num = -1;
				else
					tile_cost_map[i][j]->pathfinding_num = 0;
				map_manager::world_tile_ids_at_coords(&tile_cost_map[i][j]->position.x, &tile_cost_map[i][j]->position.y, tile->get_position().x, tile->get_position().y);
				//tile_cost_map[i][j]->position = tile->get_position();
			}
		}

		for (int i = 0; i < tileshigh; i++)
		{
			for (int j = 0; j < tileswide; j++)
			{
				//add neighbours for this tile
				if (i > 0)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i - 1][j]);
				if (j > 0)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i][j - 1]);
				if (i < tileswide - 1)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i + 1][j]);
				if (j < tileshigh - 1)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i][j + 1]);
				if (i < tileswide - 1 && j > 0)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i + 1][j - 1]);
				if (i > 0 && j > 0)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i - 1][j - 1]);
				if (i < tileswide - 1 && j < tileshigh - 1)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i + 1][j + 1]);
				if (i > 0 && j < tileshigh - 1)
					tile_cost_map[i][j]->neighbours.push_back(tile_cost_map[i - 1][j + 1]);
			}
		}

		SDL_Point player_pos = { players.at(0)->get_position().x, players.at(0)->get_position().y };
		
		std::vector<SDL_Point> player_coords;
		int x, y;
		world_tile_ids_at_coords(&x, &y, player_pos.x, player_pos.y);
		for (std::vector<player*>::iterator it = players.begin(); it != players.end(); it++)
		{
			player* pl = *it;
			SDL_Point point = { pl->get_position().x, pl->get_position().y };
			world_tile_ids_at_coords(&x, &y, point.x, point.y);

			player_coords.push_back({x, y});
		}
		LeePathfinder::set_map(tile_cost_map, tileswide, tileshigh);
		LeePathfinder::set_players(player_coords);

#pragma region set objects in pathfinder
		std::vector<SDL_Point> obj_coords;
		for (std::vector<item_object*>::iterator it = items.begin(); it != items.end(); it++)
		{
			item_object* i = *it;
			//exclusions
			if (i->get_item_type() == constants::item_type::tree)
				continue;

			item_object* pl = *it;
			SDL_Point point = { pl->get_position().x, pl->get_position().y };
			world_tile_ids_at_coords(&x, &y, point.x, point.y);

			obj_coords.push_back({ x, y });
		}
		LeePathfinder::set_objects(obj_coords);
#pragma endregion
		
		LeePathfinder::set_origin(x, y);
		LeePathfinder::mark_field();
		LeePathfinder::display_field();

		//LeePathfinder::display_field();
	}
}

void map_manager::init_pathfinding_for_current_map_state(int cur_player)
{
	if (initialised)
	{
		SDL_Point player_pos = { players.at(cur_player)->get_position().x, players.at(cur_player)->get_position().y };
		int x, y;
		world_tile_ids_at_coords(&x, &y, player_pos.x, player_pos.y);
		LeePathfinder::set_origin(x, y);

#pragma region set players in pathfinder
		std::vector<SDL_Point> player_coords;
		world_tile_ids_at_coords(&x, &y, player_pos.x, player_pos.y);
		for (std::vector<player*>::iterator it = players.begin(); it != players.end(); it++)
		{
			player* pl = *it;
			SDL_Point point = { pl->get_position().x, pl->get_position().y };
			world_tile_ids_at_coords(&x, &y, point.x, point.y);

			player_coords.push_back({ x, y });
		}
		LeePathfinder::set_players(player_coords);
#pragma endregion
		LeePathfinder::mark_field();
	}
}

std::vector<SDL_Point> map_manager::get_path_from_to(int from_x, int from_y, int to_x, int to_y)
{
	//TODO: add logic to interact with pathfinding algorithm and return the vector of tile ids to go to to get to endpoint
	if (LeePathfinder::find_path({ to_x, to_y }))
	{
		std::cout << "Path from (" << from_x << " " << from_y << ") to (" << to_x << " " << to_y << ") found" << std::endl;
	}
	else
		std::cout << "Path not found" << std::endl;
	std::vector<SDL_Point> res = LeePathfinder::get_path();
	return res;
}

//function returns the type of the tile at certain x and y and if the tile is not empty, a pointer to an object on it
constants::tile_type map_manager::get_tile_type_at(int x, int y, game_object** object_at_coords)
{
	constants::tile_type t = map[y][x]->tile_type;
	
	//check if there are any entities at the coordinate
	for(std::vector<living_entity*>::iterator it = map_entities.begin(); it != map_entities.end(); it++)
	{
		living_entity* ent = *it;
		int e_x, e_y;
		world_tile_ids_at_coords(&e_x, &e_y, ent->world_coords.x, ent->world_coords.y);
		if (e_x == x && e_y == y)
		{
			*object_at_coords = ent;
			t = constants::tile_type::entity;
			goto end;
		}
	}

	//check if there are any players at the coordinate
	for (std::vector<player*>::iterator it = players.begin(); it != players.end(); it++)
	{
		player* ent = *it;
		int e_x, e_y;
		world_tile_ids_at_coords(&e_x, &e_y, ent->world_coords.x, ent->world_coords.y);
		if (e_x == x && e_y == y)
		{
			*object_at_coords = ent;
			t = constants::tile_type::pl;
			goto end;
		}
	}

	//check if there are any items/other objects at the coordinate
	for (std::vector<item_object*>::iterator it = items.begin(); it != items.end(); it++)
	{
		item_object* ent = *it;
		int e_x, e_y;
		world_tile_ids_at_coords(&e_x, &e_y, ent->world_coords.x, ent->world_coords.y);
		if (e_x == x && e_y == y)
		{
			*object_at_coords = ent;
			t = constants::tile_type::game_obj;
			goto end;
		}
	}

	
end:
	return  t;
}

map_manager::map_manager()
{

}


map_manager::~map_manager()
{
}
