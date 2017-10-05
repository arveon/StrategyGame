#include "MapManager.h"

int map_manager::tileswide, map_manager::tileshigh = 0;
int  map_manager::t_width, map_manager::t_height = 1;
tile_object*** map_manager::map = nullptr;
bool map_manager::initialised = false;
void map_manager::load_map(int level)
{
	if (initialised)
	{
		tileset_manager::set_initialised();
		load_from_file();
		/*list_tex_to_load();
		link_textures_to_tiles();*/
	}
}

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
			t_type = constants::tile_type::stone;
			break;
		case 16:
			t_type = constants::tile_type::water;
			break;
		default:
			t_type = constants::tile_type::empty;
		}

		tile_object* temp_tile = new tile_object({ (int)((float)(x * t_width) * constants::tile_scaling), (int)((float)(y * t_height) * constants::tile_scaling) }, t_width * constants::tile_scaling, t_height * constants::tile_scaling, true, nullptr, 0, (constants::tile_type)t_type, t_tex_id);
		map[y][x] = temp_tile;
		
		cur_node = cur_node->next_sibling();
	}

}

void map_manager::load_required_tex()
{
	std::vector<int> texture_id_list;
	for (int i = 0; i < tileshigh; i++)
	{
		for (int j = 0; j < tileswide; j++)
		{
			if (!helper_functions::is_int_in_vector(texture_id_list, map[i][j]->tile_texture_id))
				helper_functions::add_to_int_vector_asc(&texture_id_list, map[i][j]->tile_texture_id);
		}
	}
	tileset_manager::load_tiles(texture_id_list, constants::tilesets::map, t_width, t_height);
}

void map_manager::link_textures_to_tiles()
{
	for (int i = 0; i < tileshigh; i++)
		for (int j = 0; j < tileswide; j++)
			map[i][j]->texture = tileset_manager::get_texture_by_id(constants::tilesets::map, map[i][j]->tile_texture_id);
}

void map_manager::unload_map()
{
	for (int i = 0; i < tileshigh; i++)
	{
		delete map[i];
	}
	delete map;
	tileswide = tileshigh = 0;
}

map_manager::map_manager()
{
}


map_manager::~map_manager()
{
}
