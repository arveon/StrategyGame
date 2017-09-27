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

	if(dir_exists(constants::SAVES_PATH.c_str()))
	{
			WIN32_FIND_DATA found_file_data;//structure where data about the found file is stored
			const char* path = constants::SAVES_PATH.c_str();
			char temp[2048];
			//apply a filter, make it search only for .save files
			sprintf_s(temp, "%s\\*.save", path);

			HANDLE h_find = FindFirstFile(temp, &found_file_data);//finds first file

			if (h_find != INVALID_HANDLE_VALUE)//check if anything was found
			{
				std::string name = found_file_data.cFileName;
				name = name.substr(0, name.find(".save"));//remove the back part of the file so that extension is not exposed

				//create item from string and add it to list
				list_item item;
				item.display_name = name;
				item.value = name;

				//cap length to 15 symbols
				if (item.display_name.size() > 15)
				{
					item.display_name = item.display_name.substr(0, 15);
					item.display_name += "...";
				}
				o.push_back(item);

				//loop through all files and add them to list
				while (FindNextFile(h_find, &found_file_data))
				{
					std::string name = found_file_data.cFileName;
					name = name.substr(0, name.find(".save"));//remove the back part of the file so that extension is not exposed

					list_item item;
					item.display_name = name;
					item.value = name;

					//cap length to 15 symbols
					if (item.display_name.size() > 20)
					{
						item.display_name = item.display_name.substr(0, 20);
						item.display_name += "...";
					}
					o.push_back(item);
				}
			}
			FindClose(h_find);
	}
	return o;
}

std::vector<list_item> file_handler::get_launch_config()
{
	std::vector<list_item> result;

	std::ifstream configstream("cfg/launch.cfg");

	if (configstream.good())
	{
		std::string line;
		while (getline(configstream, line))
		{
			list_item item;
			std::stringstream buffer(line);

			if (line.find("resolution ") != std::string::npos)
			{
				getline(buffer, item.display_name, ' ');

				std::string temp;
				getline(buffer, item.value);

			}
			else if (line.find("appname ") != std::string::npos)
			{
				getline(buffer, item.display_name, ' ');
				std::string temp;
				getline(buffer, item.value);
			}
			else
			{
				getline(buffer, item.display_name, ' ');
				getline(buffer, item.value, ' ');
			}
			result.push_back(item);
		}
	}

	return result;
}

void file_handler::save_settings(std::vector<std::string> settings)
{
	std::ofstream filestream("cfg/settings.cfg", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < (int)settings.size(); i++)
	{
		filestream << settings.at(i);
	}
	filestream.close();
}

void file_handler::save_launch(std::string res, bool fs)
{
	if(!file_exists("cfg/launch.cfg"))
		file_handler::create_launch_file();

	//replace resolution and fullscreen entries in launch.cfg 
	std::ifstream launch_ifilestr("cfg/launch.cfg");
	std::string line;
	std::vector<std::string> lines;
	int i = 0;
	int res_id, fs_id = -1;
	//store lines from file in a temp vector and find line numbers for resolution and fullscreen settings
	while (getline(launch_ifilestr, line))
	{
		lines.push_back(line);
		if (line.find("resolution ") != std::string::npos)
			res_id = i;
		else if (line.find("fullscreen ") != std::string::npos)
			fs_id = i;
		i++;
	}
	launch_ifilestr.close();

	//replace resolution line in the vector containing all file lines
	if (res_id == -1)
		return;
	std::stringstream buffer;
	buffer << "resolution " << res;
	/*getline(buffer,*/ lines.at(res_id) = buffer.str();

	//replace fullscreen line in the vector containing all file lines
	if (fs_id == -1)
		return;

	buffer.str(std::string());//empties the buffer
	buffer << "fullscreen " << fs;
	getline(buffer, lines.at(fs_id));

	//replace contents of file with the edited version
	std::ofstream launch_ofilestr("cfg/launch.cfg");
	for (int i = 0; i < (int)lines.size(); i++)
	{
		launch_ofilestr << lines.at(i) << std::endl;
	}
	launch_ofilestr.close();
}

std::vector<list_item> file_handler::load_settings()
{
	std::vector<list_item> settings;

	if (!file_exists("cfg/settings.cfg"))
		file_handler::create_settings_file();
	std::ifstream filestr("cfg/settings.cfg");

	if (filestr.good())//check if file exists
	{
		std::string line;
		//read file line by line and extract required values
		while (getline(filestr, line))
		{
			std::string temp = "";
			std::stringstream str_buffer;
			str_buffer << line;
			getline(str_buffer, temp, ' ');

			list_item temp_item;

			if (temp == "master_volume")
			{
				getline(str_buffer, temp_item.value);
				temp_item.display_name = "master_volume";
				settings.push_back(temp_item);
			}
			else if (temp == "music_volume")
			{
				getline(str_buffer, temp_item.value);
				temp_item.display_name = "music_volume";
				settings.push_back(temp_item);
			}
			else if (temp == "sounds_volume")
			{
				getline(str_buffer, temp_item.value);
				temp_item.display_name = "sounds_volume";
				settings.push_back(temp_item);
			}
			else if (temp == "fullscreen")
			{
				getline(str_buffer, temp_item.value);
				temp_item.display_name = "fullscreen";
				settings.push_back(temp_item);
			}
			else if (temp == "resolution")
			{
				getline(str_buffer, temp_item.value);
				temp_item.display_name = "resolution";
				settings.push_back(temp_item);
			}
		}
	}

	return settings;
}

bool file_handler::create_launch_file()
{
	std::ofstream filestr;

	if (!dir_exists("cfg"))
		CreateDirectory("cfg", NULL);
	
	filestr.open("cfg/launch.cfg");
	if (!filestr.good())
		return false;
	
	filestr << constants::LAUNCH_MIN_TEMPLATE << std::endl;
	filestr.close();
	return true;
}

bool file_handler::create_settings_file()
{
	std::ofstream filestr;

	if (!dir_exists("cfg"))
		CreateDirectory("cfg", NULL);

	filestr.open("cfg/settings.cfg");
	if (!filestr.good())
		return false;

	filestr << constants::SETTINGS_MIN_TEMPLATE << std::endl;
	filestr.close();
	return true;
}

bool file_handler::dir_exists(std::string path)
{
	bool result = false;
	DWORD file_type = GetFileAttributesA(path.c_str());
	if (file_type == INVALID_FILE_ATTRIBUTES)
		result = false;//file doesnt exist
	else if (file_type & FILE_ATTRIBUTE_DIRECTORY)
		result = true;//file exists AND DIRECTORY
	else
		result = false;//file exists but not a directory

	return result;
}

bool file_handler::file_exists(std::string path)
{
	bool res = false;
	DWORD file_type = GetFileAttributes(path.c_str());
	if (file_type == INVALID_FILE_ATTRIBUTES)
		res = false;
	else
		res = true;

	return res;
}