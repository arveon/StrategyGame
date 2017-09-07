#include "MapManager.h"

int map_manager::w, map_manager::h = 0;
int  map_manager::t_w, map_manager::t_h = 1;
tile_object*** map_manager::map = nullptr;
void map_manager::load_map(int level)
{
	//TODO::Add checks for file not being in the folder, not having anything in the map etc
	w = h = 0;
	//load file into a data structure
	rapidxml::file<> file("maps/sample_map.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());

	//get width and height of map from attributes
	w = std::stoi(doc.first_node()->first_attribute("tileswide")->value());
	h = std::stoi(doc.first_node()->first_attribute("tileshigh")->value());
	t_w = std::stoi(doc.first_node()->first_attribute("tilewidth")->value());
	t_h = std::stoi(doc.first_node()->first_attribute("tileheight")->value());
	std::cout << "size: " << w << " by " << h << std::endl;

	//get reference to the first tile node
	rapidxml::xml_node<>* cur_node = doc.first_node("tilemap")->first_node("layer")->first_node("tile");

	//allocate space for map array
	map = new tile_object**[h];
	for (int i = 0; i < h; i++)
		map[i] = new tile_object*[w];

	//loop through all nodes getting their coordinates from attributes and saving the tile types into map array
	while (cur_node != NULL)
	{
		int x, y = 0;
		x = std::stoi(cur_node->first_attribute("x")->value());
		y = std::stoi(cur_node->first_attribute("y")->value());

		//TODO: Replace temp_tex with proper textures (and figure out the logic it will do it with)
		SDL_Texture* temp_tex;
		int t_type = std::stoi(cur_node->first_attribute("tile")->value());
		if (t_type == 1)
			temp_tex = sdlframework::sdl_manager::create_texture(1, 1, { 255,0,0 });
		else
			temp_tex = sdlframework::sdl_manager::create_texture(1, 1, { 0,0,255 });

		tile_object* temp_tile = new tile_object({ x * t_w, y * t_h }, t_w, t_h, true, temp_tex, 0, (constants::tile_type)t_type);

		map[y][x] = temp_tile;

		cur_node = cur_node->next_sibling();
	}

	//print map array
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			std::cout << map[i][j]->tile_type;
		}
		std::cout << std::endl;
	}

}

void map_manager::unload_map()
{
	for (int i = 0; i < h; i++)
	{
		delete map[i];
	}
	delete map;
	w = h = 0;
}

map_manager::map_manager()
{
}


map_manager::~map_manager()
{
}
