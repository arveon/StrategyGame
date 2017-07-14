#pragma once
#include <SDL.h>

namespace sdlframework
{
	///Class responsible for updating and managing game running time and elapsed time
	class time
	{
	private:
		Uint32 elapsed_time;
		Uint32 run_time;

	public:
		void init();
		void update();

		Uint32 get_delta_time() { return elapsed_time; }
		Uint32 get_run_time() { return run_time; }
	};
}

