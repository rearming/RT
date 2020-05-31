
#include "rt.h"
#include "rt_gui.h"

void	fix_states(short action)
{
	if (g_gui.obj[action].type == RENDER_BTN)
	{
		if (g_gui.obj[action].action != g_gui.render_algo)
			g_gui.obj[action].state = non_event;
		else
			g_gui.obj[action].state = click;
	}
	if (g_gui.obj[action].type == PANEL)
	{
		if (g_gui.obj[action].action != g_gui.panel)
			g_gui.obj[action].state = non_event;
		else
			g_gui.obj[action].state = click;
	}
	if (g_gui.obj[action].type & TEXT_BOX)
	{
		if (g_gui.obj[action].type & (1 << (g_gui.panel)))
			g_gui.obj[action].state = label;
		else
			g_gui.obj[action].state = hidden;
	}
}
