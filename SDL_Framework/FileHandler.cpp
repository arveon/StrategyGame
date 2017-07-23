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
	static int i = 0;

	struct stat info;
	if (stat(constants::SAVES_PATH.c_str(), &info) == 0)
	{
		if (info.st_mode & S_IFDIR)
		{
			i++;
			WIN32_FIND_DATAA found_file_data;//structure where data about the found file is stored
			const wchar_t* folder_name = file_handler::str_to_wchar(constants::SAVES_PATH);

			const char* path = constants::SAVES_PATH.c_str();
			char temp[2048];
			sprintf_s(temp, "%s\\*.*", path);

			//std::wcout << folder_name_str << std::endl;
			HANDLE h_find = FindFirstFile(temp, &found_file_data);//finds first file
			
			if (h_find != INVALID_HANDLE_VALUE)//check if anything was found
			{
				//convert unicode string into a normal string
				
				std::string name = found_file_data.cFileName;

				//create item from string and add it to list
				//TODO: add logic to refine the display names and filter out unnecessary files
				list_item item;
				item.display_name = name;
				item.value = name;
				o.push_back(item);

				//loop through all files and add them to list
				while (FindNextFile(h_find, &found_file_data))
				{
					std::string name = found_file_data.cFileName;

					//TODO: add logic to refine the display names and filter out unnecessary files
					list_item item;
					item.display_name = name;
					item.value = name;

					o.push_back(item);
					//std::cout << i << std::endl;
					i++;
				}
				
			}
			else
				std::cout << "Invalid handle value: " << folder_name <<"\n";
			FindClose(h_find);
		}
	}
	else
		std::cout << "Folder doesn't exist" << std::endl;

	return o;
}


const wchar_t* file_handler::str_to_wchar(std::string str)
{
	std::string path = str;
	std::wstring str2(path.length(), L' ');
	std::copy(path.begin(), path.end(), str2.begin());

	return str2.c_str();
}

std::string file_handler::wchar_to_str(wchar_t* wchar)
{
	std::string o = "";
	int i = 0;

	while (wchar[i] != '\0')
	{
		o +=(char) wchar[i++];
	}
	return o;
}
