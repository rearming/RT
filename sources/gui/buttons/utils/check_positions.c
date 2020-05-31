//
// Created by Dyan Great on 5/29/20.
//

#include "rt_gui.h"
#include "rt.h"

bool is_positions_changed(int tb_id, float curr_value)
{
	if (g_gui.obj[tb_id].param != curr_value)
	{
		ft_sprintf(&(g_gui.obj[tb_id].field), "%i", (int)(curr_value));
		g_gui.obj[tb_id].param = curr_value;
		return (true);
	}
	return (false);
}