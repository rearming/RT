/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:44 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:19:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_array(cl_float3 *elem, json_t *value)
{
	json_t	*tmp;
	int		i;

	i = -1;
	if (json_array_size(value) == 3)
	{
		while (++i < 3)
		{
			tmp = json_array_get(value, i);
			if (!json_is_number(tmp))
				printf("error");
			else
				elem->s[i] = json_is_integer(tmp) ? json_integer_value(tmp)
					: json_real_value(tmp);
		}
	}
}
