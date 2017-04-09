#include "Time.h"

#include <iostream>


using namespace sdlframework;
void time::init()
{
	run_time = SDL_GetTicks();
}

void time::update()
{
	elapsed_time = SDL_GetTicks() - run_time;
	run_time += elapsed_time;
	//std::cout << elapsed_time << std::endl;

}
