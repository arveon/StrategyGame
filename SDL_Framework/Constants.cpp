#include "Constants.h"

float constants::setup::scaling_vertical = (float)WINDOW_HEIGHT / 480;
float constants::setup::scaling_horizontal = (float)WINDOW_WIDTH / 640;
int constants::setup::WINDOW_WIDTH = 640;
int constants::setup::WINDOW_HEIGHT = 480;
bool constants::setup::FULLSCREEN = false;
char constants::setup::WINDOW_CAPTION[] = "ASD";

void constants::setup::init_resolution_deps()
{
	scaling_vertical = (float)WINDOW_HEIGHT / 480;
	scaling_horizontal = (float)WINDOW_WIDTH / 640;
}

void constants::setup::init_settings(std::vector<list_item> settings)
{
#pragma warning(disable:4244)
	for (int i = 0; i < settings.size(); i++)
	{
		if (settings.at(i).display_name == "resolution")
		{
			std::string temp = settings.at(i).value;
			std::stringstream buffer(temp);
			std::string x, y;

			getline(buffer, x, ' ');
			getline(buffer, y, ' ');

			constants::setup::WINDOW_WIDTH = stoi(x);
			constants::setup::WINDOW_HEIGHT = stoi(y);
			//std::cout << "set resolution to:" << constants::WINDOW_WIDTH << " : " << constants::WINDOW_HEIGHT << std::endl;
		}
		else if (settings.at(i).display_name == "fullscreen")
		{
			std::string val = settings.at(i).value;
			bool fs;

			if (val == "1")
				fs = true;
			else
				fs = false;

			constants::setup::FULLSCREEN = fs;
		}
	}
	init_resolution_deps();
}