#include "rt_gui.h"

bool		check_click(SDL_Event *event, SDL_Rect button)
{
	if (event->button.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return (click);
	return (false);
}
