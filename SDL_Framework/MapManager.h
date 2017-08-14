#pragma once
#include <vector>
#include <rapidxml\rapidxml.hpp>

class map_manager
{
private:
	

public:
	void load_map(int level);

	void unload_map();
	map_manager();
	~map_manager();
};

