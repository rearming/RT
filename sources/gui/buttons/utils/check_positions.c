/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/07/09 17:46:33 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"

bool	is_positions_changed(int tb_id, float curr_value)
{
	if (g_gui.obj[tb_id].param != curr_value)
	{
		free(g_gui.obj[tb_id].field);
		ft_sprintf(&(g_gui.obj[tb_id].field), "%i", (int)(curr_value));
		g_gui.obj[tb_id].param = curr_value;
		return (true);
	}
	return (false);
}
