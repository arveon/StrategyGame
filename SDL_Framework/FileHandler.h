#pragma once
#include <sys/stat.h>
#include <sys/types.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include "ListItem.h"
#include "Constants.h"

///Class contains all methods for file handling required in the program
class file_handler
{
public:
	file_handler();
	~file_handler();

	//functions specific for the game
	static std::vector<list_item> get_saved_files();
	static std::vector<list_item> get_launch_config();
	static bool create_launch_file();
	static bool create_settings_file();

	static void save_settings(std::vector<std::string> settings);
	static void save_launch(std::string resolution, bool fullscreen);

	//general purpose functions
	static bool dir_exists(std::string path);
	static bool file_exists(std::string path);
	
};

