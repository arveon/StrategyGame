#include "Map.h"

Map::Map(int width, int height)
{
	

	this->width = width;
	this->height = height;

	field = new SimplePoint*[height];
	for (int i = 0; i < height; i++)
	{
		field[i] = new SimplePoint[width];
	}

}

void Map::populate_map_default()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			field[i][j] = SimplePoint{ i, j, 0 };

	field[1][5].val = -1;
	field[2][5].val = -1;
	field[2][4].val = -1;
	field[3][4].val = -1;
	field[4][4].val = -1;
	field[5][4].val = -1;
	field[5][3].val = -1;
	field[5][2].val = -1;
	field[5][1].val = -1;
	field[5][0].val = -1;
}

void Map::link_tiles()
{
	//set up every tile's neighbours
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i > 0)
				field[i][j].neighbours.push_back(&field[i - 1][j]);
			if (j < width - 1)
				field[i][j].neighbours.push_back(&field[i][j + 1]);
			if (i < height - 1)
				field[i][j].neighbours.push_back(&field[i + 1][j]);
			if (j > 0)
				field[i][j].neighbours.push_back(&field[i][j - 1]);
			if (i > 0 && j > 0)
				field[i][j].neighbours.push_back(&field[i - 1][j - 1]);
			if (i > 0 && j < width - 1)
				field[i][j].neighbours.push_back(&field[i - 1][j + 1]);
			if (i < height - 1 && j > 0)
				field[i][j].neighbours.push_back(&field[i + 1][j - 1]);
			if (i < height - 1 && j < width - 1)
				field[i][j].neighbours.push_back(&field[i + 1][j + 1]);
			//std::cout << field[i][j].neighbours.size();
		}
		//std::cout << std::endl;
	}
}

void Map::display_map()
{
	std::cout << "Field: " << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			std::cout << field[i][j].val << " ";
		std::cout << std::endl;
	}
}
