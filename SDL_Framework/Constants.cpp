#include "Constants.h"

float constants::setup::scaling_vertical = (float)WINDOW_HEIGHT / 480;
float constants::setup::scaling_horizontal = (float)WINDOW_WIDTH / 640;
int constants::setup::WINDOW_WIDTH = 640;
int constants::setup::WINDOW_HEIGHT = 480;
bool constants::setup::FULLSCREEN = false;
std::string constants::setup::WINDOW_CAPTION = "TempName";

void constants::setup::init_resolution_deps()
{
	scaling_vertical = (float)WINDOW_HEIGHT / 480;
	scaling_horizontal = (float)WINDOW_WIDTH / 640;
}

void constants::setup::init_settings(std::vector<list_item> settings)
{
#pragma warning(disable:4244)
	for (int i = 0; i < (int)settings.size(); i++)
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
		else if (settings.at(i).display_name == "appname")
		{
			constants::setup::WINDOW_CAPTION = settings.at(i).value;


		}
	}
	init_resolution_deps();
}