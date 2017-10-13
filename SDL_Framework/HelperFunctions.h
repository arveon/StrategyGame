#pragma once
#include <vector>

///Class that contains static general helper functions
class helper_functions
{
public:
	//general methods for vector management
	static bool is_int_in_vector(std::vector<int>, int);
	static void add_to_int_vector_asc(std::vector<int>*, int);

	helper_functions();
	~helper_functions();
};

