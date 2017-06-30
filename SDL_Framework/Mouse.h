#pragma once
#include <SDL.h>
class Mouse
{
public:
	int x, y;
	bool lmb_down;
	bool rmb_down;
	bool prev_lmb_down;
	bool prev_rmb_down;
	Mouse();
	~Mouse();
};

