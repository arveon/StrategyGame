#include "DialogWindow.h"
#include "Button.h"

///Class that is a child of the dialog window
///Used to create confirmation dialogs with yes/no buttons
class confirm_dialog : dialog_window
{
public:
	enum dialog_state {
		Waiting,
		Confirmed,
		Cancelled
	};
private:
	SDL_Color text_color;
	dialog_state cur_state;
	Button yes;
	Button no;
public:
	confirm_dialog(SDL_Texture* bg, SDL_Point window_coords, std::string text, int width, int height);
	void draw(SDL_Renderer* rend);
	void update(Mouse* mouse);
	~confirm_dialog();

	bool is_confirmed() { return cur_state == dialog_state::Confirmed; }
	bool is_cancelled() { return cur_state == dialog_state::Cancelled; }
};

