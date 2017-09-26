#include "HelperFunctions.h"



bool helper_functions::is_int_in_vector(std::vector<int> list, int number)
{
	bool result = false;
	for (std::vector<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		int num = *it;

		if (num == number)
		{
			result = true;
			break;
		}
	}

	return result;
}

void helper_functions::add_to_int_vector_asc(std::vector<int>* list, int number)
{
	if (list->size() == 0)
	{
		list->push_back(number);
		return;
	}

	for (std::vector<int>::iterator it = list->begin(); it != list->end(); it++)
	{
		int num = *it;
		if (number < num)
		{
			list->insert(it, number);
			break;
		}
	}
	list->push_back(number);
}

helper_functions::helper_functions()
{
}


helper_functions::~helper_functions()
{
}
