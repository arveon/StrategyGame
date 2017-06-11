#include "DialogWindow.h"
#include "Button.h"

class confirm_dialog : dialog_window
{
private:
	Button yes;
	Button no;
public:
	confirm_dialog(SDL_Texture* bg, SDL_Point window_center, std::string text, int width, int height);
	void draw(SDL_Renderer* rend);
	void update(Mouse mouse);
	~confirm_dialog();
};

