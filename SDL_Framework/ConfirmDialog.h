#include "DialogWindow.h"
#include "Button.h"

class ConfirmDialog: DialogWindow
{
private:
	Button yes;
	Button no;
public:
	ConfirmDialog(SDL_Texture* bg);
	void draw(SDL_Renderer* rend);
	void update();
	~ConfirmDialog();
};

