#pragma once
#include "Constants.h"
#include "Mouse.h"
class level_manager
{
private:
	

public:
	void reset_level();
	void set_level();
	
	void update(Mouse);
	void draw(SDL_Renderer*);
	
	level_manager();
	~level_manager();
};

