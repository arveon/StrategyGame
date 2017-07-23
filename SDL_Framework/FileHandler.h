#pragma once
#include <sys/stat.h>
#include <sys/types.h>
#include <Windows.h>
#include <iostream>

#include <vector>
#include "ListItem.h"
#include "Constants.h"

///Class contains all methods for file handling required in the program
class file_handler
{
private:
	static std::string wchar_to_str(wchar_t* wchar);
	static const wchar_t* str_to_wchar(std::string str);
	

public:
	static std::vector<list_item> get_saved_files();
	file_handler();
	~file_handler();
};

