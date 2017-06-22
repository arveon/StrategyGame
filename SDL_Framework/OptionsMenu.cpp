#include "OptionsMenu.h"



OptionsMenu::OptionsMenu(SDL_Renderer*)
{
	std::string fontpath = constants::FONTS_PATH;
	fontpath.append(constants::font_inkedout);
	back.init(constants::font_inkedout, "Back");
	back.init(constants::font_inkedout, "Apply");


}

void OptionsMenu::draw(SDL_Renderer* renderer)
{
	//SDL_RenderCopy(renderer, )
}

void OptionsMenu::update(Mouse mouse)
{

}


OptionsMenu::~OptionsMenu()
{
}
