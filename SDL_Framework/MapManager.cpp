#include "MapManager.h"

//initialise all of the static variables
int map_manager::tileswide, map_manager::tileshigh = 0;
int  map_manager::t_width, map_manager::t_height = 1;
tile_object*** map_manager::map = nullptr;
bool map_manager::initialised = false;
std::vector<living_entity*> map_manager::map_entities;
std::vector<item_object*> map_manager::items;
bool map_manager::map_currently_loaded = false;

///Function is used to load a map with a given level id and initialise the manager
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
	//load file into a data structure
	rapidxml::file<> file("maps/sample_map.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());

	//get width and height of map from attributes
	tileswide = std::stoi(doc.first_node()->first_attribute("tileswide")->value());
	tileshigh = std::stoi(doc.first_node()->first_attribute("tileshigh")->value());
	t_width = std::stoi(doc.first_node()->first_attribute("tilewidth")->value());
	t_height = std::stoi(doc.first_node()->first_attribute("tileheight")->value());
	std::cout << "size: " << tileswide << " by " << tileshigh << std::endl;

	//get reference to the first tile node
	rapidxml::xml_node<>* cur_node = doc.first_node("tilemap")->first_node("layer")->first_node("tile");

	//allocate space for map array
	map = new tile_object**[tileshigh];
	for (int i = 0; i < tileshigh; i++)
		map[i] = new tile_object*[tileswide];

	//loop through all nodes getting their coordinates from attributes and saving the tile types into map array
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

	//loop through all nodes getting their coordinates from attributes and saving the tile types into map array
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


		//constants::tile_type t_type;
		game_object* obj1 = nullptr;
		living_entity* obj;
		tex_id -= constants::tileset_entity_offset;
		switch (tex_id)
		{
		case 0:
			obj = new player({ (int)std::floor(((float)(x * t_width) * constants::tile_scaling)), (int)std::floor(((float)(y * t_height) * constants::tile_scaling)) }, t_width * constants::tile_scaling, t_height * constants::tile_scaling, nullptr, true, tex_id);
			map_entities.push_back(obj);
			break;
		case 1:
		case 2:
			constants::entity_type type = constants::enemy_ai_1;
			if (tex_id == 1)
				type = constants::enemy_ai_1;
			else if (tex_id == 2)
				type = constants::enemy_ai_2;

			obj = new enemy({ (int)std::floor(((float)(x * t_width) * constants::tile_scaling)), (int)std::floor(((float)(y * t_height) * constants::tile_scaling)) }, t_width * constants::tile_scaling, t_height * constants::tile_scaling, nullptr, true, tex_id, type);
			map_entities.push_back(obj);
			break;
		}
		
		cur_node = cur_node->next_sibling();
	}
	map_currently_loaded = true;
}

///Function is used to build a vector of required terrain tiles and ask tileset manager to load them
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

///function is used to build a vector of character tiles and load them from a vector
void map_manager::load_required_tex_entities()
{
	std::vector<int> entity_texture_id_list;
	for (std::vector<living_entity*>::iterator it = map_entities.begin(); it != map_entities.end(); ++it)
	{
		living_entity* ent = *it;

		if (!helper_functions::is_int_in_vector(entity_texture_id_list, ent->texture_id+constants::tileset_entity_offset))
			helper_functions::add_to_int_vector_asc(&entity_texture_id_list, ent->texture_id);
	}
	tileset_manager::load_tiles(entity_texture_id_list, constants::tilesets::characters, t_width, t_height);
}

///function is used to link all of the terrain textures from tileset manager to actual objects
void map_manager::link_textures_to_tiles()
{
	for (int i = 0; i < tileshigh; i++)
		for (int j = 0; j < tileswide; j++)
			map[i][j]->texture = tileset_manager::get_texture_by_id(constants::tilesets::map, map[i][j]->texture_id);
}

///function is used to link the entity textures from tileset manager to actual objects
void map_manager::link_textures_to_entities()
{
	for (std::vector<living_entity*>::iterator it = map_entities.begin(); it != map_entities.end(); ++it)
			(*it)->texture = tileset_manager::get_texture_by_id(constants::tilesets::characters, (*it)->texture_id);
}

///function used to unload the whole map
void map_manager::unload_map()
{
	for (int i = 0; i < tileshigh; i++)
	{
		delete map[i];
	}
	delete map;
	tileswide = tileshigh = 0;
}

///function is used to add an appropriate vector (of objects of a certain type) to the painter queues
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
		for (std::vector<living_entity*>::iterator it = map_entities.begin(); it != map_entities.end(); ++it)
			drawing_manager->add_object_to_queue(*it);
		
		break;
	}
}

//Function links every tile with all of its neighbouring tiles for the pathfinding algorithm
bool map_manager::link_tiles()
{
	//if map is not loaded there is nothing to link
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
			std::cout << map[i][j]->neighbours.size();
		}
		std::cout << std::endl;
	}
	return true;
}

///function returns the type of the tile at certain x and y
constants::tile_type map_manager::get_tile_type_at(int x, int y)
{
	//if()
	return map[y][x]->tile_type;
}

map_manager::map_manager()
{

}


map_manager::~map_manager()
{
}
