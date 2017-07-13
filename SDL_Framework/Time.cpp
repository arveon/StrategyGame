#include "Time.h"

#include <iostream>
using namespace sdlframework;
/*
	get ticks since program start
*/
void time::init()
{
	run_time = SDL_GetTicks();
}

/*
	update elapsed time
*/
void time::update()
{
	elapsed_time = SDL_GetTicks() - run_time;
	run_time += elapsed_time;

}
