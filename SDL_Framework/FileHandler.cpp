#include "FileHandler.h"


file_handler::file_handler()
{
}


file_handler::~file_handler()
{
}

std::vector<list_item> file_handler::get_saved_files()
{
	std::vector<list_item> o;

	struct stat info;
	if (stat(constants::SAVES_PATH.c_str(), &info) == 0)
	{
		if (info.st_mode & S_IFDIR)
		{
			WIN32_FIND_DATA found_file_data;//structure where data about the found file is stored
			const char* path = constants::SAVES_PATH.c_str();
			char temp[2048];
			//apply a filter, make it search only for .save files
			sprintf_s(temp, "%s\\*.save", path);

			//std::wcout << folder_name_str << std::endl;
			HANDLE h_find = FindFirstFile(temp, &found_file_data);//finds first file
			
			if (h_find != INVALID_HANDLE_VALUE)//check if anything was found
			{				
				std::string name = found_file_data.cFileName;
				name = name.substr(0,name.find(".save"));//remove the back part of the file so that extension is not exposed

				//create item from string and add it to list
				list_item item;
				item.display_name = name;
				item.value = name;
				o.push_back(item);

				//loop through all files and add them to list
				while (FindNextFile(h_find, &found_file_data))
				{
					std::string name = found_file_data.cFileName;
					name = name.substr(0, name.find(".save"));//remove the back part of the file so that extension is not exposed

					list_item item;
					item.display_name = name;
					item.value = name;
					o.push_back(item);
				}
			}
			else
				std::cout << "No save files found!" << std::endl;
			FindClose(h_find);
		}
	}
	else
		std::cout << "Folder doesn't exist" << std::endl;

	return o;
}